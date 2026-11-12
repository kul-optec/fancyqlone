#include <gtest/gtest.h>

#include <fancyqlone/barrier.hpp>
#include <fancyqlone/cyqlone/cyqlone.hpp>
#include <fancyqlone/linalg.hpp>
#include <fancyqlone/ocp.hpp>
#include <fancyqlone/packing.hpp>
#include <fancyqlone/random-ocp.hpp>
#include <fancyqlone/tracing.hpp>
#include <fancyqlone/cyqlone/tridiagonal-solver.hpp>
#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/triangular.hpp>
#include <batmat/lut.hpp>
#include <batmat/openmp.h>
#include <guanaqo/print.hpp>
#include <guanaqo/trace.hpp>
#include <cyqlone-version.h>

#if !BATMAT_WITH_OPENMP
#include <batmat/thread-pool.hpp>
#endif
#if GUANAQO_WITH_TRACING
#include <filesystem>
#include <fstream>
#endif
#include <algorithm>
#include <iostream>
#include <limits>
#include <print>

using cyqlone::index_t;
using cyqlone::real_t;

index_t cyq_get_num_proc();

cyqlone::LinearOCPStorage combine_branches(std::span<const cyqlone::LinearOCPStorage> ocps);

// Tests the factorization, factorization updates, and solution of the Cyqlone linear solver.
TEST(CyqloneFanFactorTest, factorSPMD) {
    using namespace cyqlone;
    using batmat::matrix::uninitialized;
    namespace la = cyqlone::linalg;
    using la::tril;

    const index_t p  = cyq_get_num_proc();
    using Solver     = CyqloneSolver<4, real_t, StorageOrder::RowMajor>;
    using SolverLast = cyqlone::TridiagonalSolver<real_t>;

    cyqlone::OCPDim dim{.N_horiz = 160, .nx = 30, .nu = 10, .ny = 0, .ny_N = 0};
    const index_t N = dim.N_horiz, nx = dim.nx, nu = dim.nu;
    const index_t nux = dim.nu + dim.nx;
    index_t fanout    = 2;
    std::mt19937 rng(102030405);
    std::uniform_real_distribution<real_t> uni(-1, 1);
    std::vector<LinearOCPStorage> ocps(fanout);
    // B(0)ᵀ for each branch
    SolverLast::matrix Bs{{.depth = fanout, .rows = nu, .cols = nx}, uninitialized};
    // B(0)ᵀ L(0)⁻ᵀ for each branch
    SolverLast::matrix LBs{{.depth = fanout, .rows = nu, .cols = nx}, uninitialized};
    // Schur complement contributions B(0)ᵀ L(0)⁻ᵀ L(0)⁻¹ B(0) for each branch,
    // R(0) + B(0)ᵀ L(0)⁻ᵀ L(0)⁻¹ B(0) for the first one.
    SolverLast::matrix R0{{.depth = 1, .rows = nu, .cols = nu}, uninitialized};
    SolverLast::matrix SBs{{.depth = fanout, .rows = nu, .cols = nu}, uninitialized};
    // Right-hand side contributions B(0)ᵀ L(0)⁻ᵀ λ(0) for each branch,
    // -r(0) - B(0)ᵀ L(0)⁻ᵀ λ(0) for the first one.
    SolverLast::matrix r0{{.depth = 1, .rows = nu, .cols = 1}, uninitialized};
    SolverLast::matrix rs{{.depth = fanout, .rows = nu, .cols = 1}, uninitialized};
    // Synchronization between the fanout branches
    cyqlone::TreeBarrier<> fan_barrier(static_cast<uint32_t>(fanout), {});
    fan_barrier.spin_count = std::numeric_limits<uint32_t>::max();

    // Random initial state
    batmat::matrix::Matrix<real_t, index_t> x0{{.rows = nx, .cols = 1}};
    std::ranges::generate(x0, [&] { return uni(rng); });

    // Allocate space for the solution
    batmat::matrix::Matrix<real_t, index_t> u0_sol{{.rows = nu, .cols = 1}};
    batmat::matrix::Matrix<real_t, index_t> λ0_sol{{.rows = fanout * nx, .cols = 1}};

#if GUANAQO_WITH_TRACING
    guanaqo::trace_logger_set_default_size(1'048'576);
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reserve(1'048'576); });

    auto save_traces = [&](const std::string &name) {
        namespace fs = std::filesystem;
        fs::path out_dir{"traces"};
        out_dir /= *cyqlone_commit_hash ? cyqlone_commit_hash : "unknown";
        fs::create_directories(out_dir);
        std::ofstream csv{out_dir / name};
        guanaqo::TraceLogger::write_column_headings(csv) << '\n';
        std::vector<std::span<const guanaqo::TraceLogger::Log>> all_logs;
        guanaqo::for_each_trace_logger([&](auto &logger) {
            std::span logs = logger.get_logs();
            all_logs.push_back(logs);
            for (const auto &log : logs)
                csv << log << '\n';
        });
        std::cout << fs::absolute(out_dir / name) << std::endl;
        write_chrome_trace((out_dir / name).replace_extension("json.gz"), all_logs);
        std::cout << fs::absolute((out_dir / name).replace_extension("json.gz")) << std::endl;
    };
#else
    auto save_traces = [](const std::string &) {};
#endif

    using clock = std::chrono::high_resolution_clock;
    clock::time_point t0, t1;
    const int num_warmup = 5;

    const index_t p_fan = std::max<index_t>(p / fanout, 1);
    auto solve_fan      = [&](index_t i, index_t) {
        auto &ocp = ocps[i] = generate_random_ocp(dim, static_cast<uint32_t>(i));
        ocp.b(0)            = x0(0); // same initial state for each branch
        auto cocp           = cyqlone::CyqloneStorage<>::build(ocp);
        // Store B(0)ᵀ for each branch; R(0) and -r(0) for the first branch
        la::copy(cocp.data_F(0).left_cols(nu).transposed(), Bs(i));
        if (i == 0) {
            la::copy(cocp.data_H(0).top_left(nu, nu), R0(0));
            la::negate(cocp.data_rq(0).top_rows(nu), r0(0));
        }
        // Introduce an unused variable u(0) in each Cyqlone block
        cocp.data_F(0).left_cols(nu).set_constant(0);    // B(0) = 0
        cocp.data_H(0).top_left(nu, nu).set_constant(0); // R(0) = I
        cocp.data_H(0).top_left(nu, nu).set_diagonal(1); //
        cocp.data_rq(0).top_rows(nu).set_constant(0);    // r(0) = 0
        // Cyqlone solver
        auto solver                  = Solver::build(cocp, p_fan);
        auto tricyqle_params         = solver.get_tricyqle_params();
        tricyqle_params.solve_method = cyqlone::SolveMethod::None;
        solver.update_tricyqle_params(tricyqle_params);
        auto pctx = solver.create_parallel_context();
        pctx->set_barrier_spin_count(std::numeric_limits<uint32_t>::max());

        // Solver for the final block-tridiagonal system.
        SolverLast solver_last{.block_size = solver.nx, .num_blocks = solver.v};
        SolverLast::matrix λ_last{{.depth = solver.v, .rows = solver.nx, .cols = 1}};

        // Right-hand sides and solutions
        Solver::matrix //
            b{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
            λ{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
            rq{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
            ux{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}};
        // Cost gradient r(j) and q(j)
        solver.initialize_gradient(cocp, rq);
        // Right-hand side of the constraints b(j)
        solver.initialize_rhs(cocp, b);

        // Forward solve on each branch to compute λ(0), and then updating the Schur complement
        auto solve_forward_λ0 = [&] {
            GUANAQO_TRACE_REGION("fan factor forward solve λ0", 0);
            // Factor the final block-tridiagonal Schur complement of each Cyqlone block
            la::unpack(tril(solver.tricyqle.cr_L.batch(0)), tril(solver_last.L));
            la::unpack(solver.tricyqle.cr_Y.batch(0), solver_last.U.transposed());
            solver_last.factor();
            // Compute the contribution to the final Schur complement (system involving only u(0))
            la::trsm(Bs.batch(i), tril(solver_last.L.batch(0)).transposed(), LBs.batch(i));
            i == 0 ? la::syrk_add(LBs.batch(i), tril(R0.batch(i)), tril(SBs.batch(i)))
                   : la::syrk(LBs.batch(i), tril(SBs.batch(i)));
            // Forward solve of the final block-tridiagonal system, to get λ(0) for each Cyqlone block
            la::unpack(λ.batch(0), λ_last);
            solver_last.solve_forward(λ_last);
            i == 0 ? la::gemv_sub(LBs.batch(i), λ_last.batch(0), r0.batch(0), rs.batch(i))
                   : la::gemv_neg(LBs.batch(i), λ_last.batch(0), rs.batch(i));
            for(index_t k= 0; k<solver.v; ++k)
                guanaqo::print_python(std::cout << "[forward]   λ(0) block " << k << " = ", λ_last.batch(k)(0), "\n");
            

                    

        };
        // Solve for u(0) (meant to be called on a single thread)
        auto solve_u0 = [&] {
            GUANAQO_TRACE_REGION("fan solve u0", 0);
            for (index_t i = 1; i < fanout; ++i)
                la::add(SBs.batch(0), SBs.batch(i));
            la::potrf(tril(SBs.batch(0)));
            for (index_t i = 1; i < fanout; ++i)
                la::add(rs.batch(0), rs.batch(i));
            la::trsm(tril(SBs.batch(0)), rs.batch(0));
            la::trsm(tril(SBs.batch(0)).transposed(),
                     rs.batch(0)); // rs(0) now contains u(0)
                
            u0_sol(0) = rs(0);

        };
        // Reverse solve for λ(0) on each branch, after solving for u(0)
        auto solve_reverse_λ0 = [&] {
            GUANAQO_TRACE_REGION("fan solve reverse λ0", 0);
            // Compute the contribution of u(0) to λ(0) for each Cyqlone block
            std::osyncstream out(std::cout);
            guanaqo::print_python(out << "[reverse]   λ(0)"<<i<<" before reverse solve = ", λ_last.batch(0)(0), "\n");

            la::gemv_add(LBs.batch(i).transposed(), rs.batch(0), λ_last.batch(0));
            guanaqo::print_python(out << "[reverse]   λ(0)" << i << " after gemv = ", λ_last.batch(0)(0), "\n");
            // Reverse solve of the final block-tridiagonal system for each Cyqlone block
            solver_last.solve_reverse(λ_last);
            la::pack(λ_last, λ.batch(0));
            λ0_sol(0).middle_rows(i * nx, nx) = λ_last(0);
        };

        auto do_solve = [&](auto &ctx) {
            // Select the thread within each branch that performed the final elimination in
            // Cyqlone, to avoid unnecessary synchronization between threads
            const bool master_thread_fan =
                solver.ν2p(ctx.index + 1) + 1 == solver.lp() || solver.p == 1;
            // Synchronize for clearer tracing and timing
            ctx.run_single_sync([&] {
                fan_barrier.arrive_and_wait_with_completion(static_cast<uint32_t>(i),
                                                            [&] { t0 = clock::now(); });
            });

            // Right-hand side of the KKT system is the negative gradient
            solver.foreach_stage(
                ctx, [](auto, auto, auto rqj, auto uxj) { la::negate(rqj, uxj); }, rq, ux);
            solver.foreach_stage(ctx, [](auto, auto, auto bj, auto λj) { la::copy(bj, λj); }, b, λ);

            // Factor and forward solve most of each Cyqlone block
            solver.factor_solve(ctx, 1e100, 0, {}, ux, λ);
            // Compute shared u(0) and the branch-specific multipliers λ(0)
            if (master_thread_fan) {
                solve_forward_λ0();
                fan_barrier.wait(
                    fan_barrier.arrive_with_completion(static_cast<uint32_t>(i), solve_u0));
                solve_reverse_λ0();
            }
            // Solve each Cyqlone block with the updated multipliers λ
            solver.solve_reverse(ctx, ux, λ);

            ctx.run_single_sync([&] {
                fan_barrier.arrive_and_wait_with_completion(static_cast<uint32_t>(i),
                                                            [&] { t1 = clock::now(); });
            });
        };

        pctx->run([&](auto &ctx) {
            for (int iter = 0; iter <= num_warmup; ++iter) {
                GUANAQO_IF_ITT(
                    __itt_thread_set_name(std::format("OMP({};{})", ctx.index, i).c_str()));
#if GUANAQO_WITH_TRACING
                if (iter == num_warmup)
                    ctx.run_single_sync([&] {
                        fan_barrier.wait(
                            fan_barrier.arrive_with_completion(static_cast<uint32_t>(i), [&] {
                                guanaqo::for_each_trace_logger(
                                    [](auto &logger) { logger.reset(); });
                            }));
                    });
                GUANAQO_TRACE("thread_id", ctx.index + 100 * (i + 1));
#endif
                do_solve(ctx);
            }
        });
    };
#if BATMAT_WITH_OPENMP
    omp_set_max_active_levels(2);
    BATMAT_OMP(parallel for num_threads(fanout))
    for (index_t i = 0; i < fanout; ++i)
        solve_fan(i, fanout);
#else
    batmat::thread_pool fan_pool(fanout);
    fan_pool.sync_run_n(fanout, solve_fan);
#endif
    save_traces("fanout-fan.csv");

    // Solve the combined problem with a single Cyqlone solve, as a reference solution
    auto combined_ocp                     = combine_branches(ocps);
    auto combined_cocp                    = cyqlone::CyqloneStorage<>::build(combined_ocp);
    auto combined_solver                  = Solver::build(combined_cocp, p);
    auto combined_tricyqle_params         = combined_solver.get_tricyqle_params();
    combined_tricyqle_params.solve_method = cyqlone::SolveMethod::PCR;
    combined_solver.update_tricyqle_params(combined_tricyqle_params);
    auto combined_rq = combined_solver.initialize_gradient(combined_cocp);
    auto combined_b  = combined_solver.initialize_rhs(combined_cocp);
    auto combined_ux = combined_rq;
    auto combined_λ  = combined_b;
    la::negate(combined_ux);
    auto pctx = combined_solver.create_parallel_context();
    pctx->set_barrier_spin_count(std::numeric_limits<uint32_t>::max());
    clock::time_point combined_t0, combined_t1;
    pctx->run([&](auto &ctx) {
        for (index_t iter = 0; iter <= num_warmup; ++iter) {
#if GUANAQO_WITH_TRACING
            if (iter == num_warmup) {
                ctx.run_single_sync(
                    [&] { guanaqo::for_each_trace_logger([](auto &logger) { logger.reset(); }); });
                GUANAQO_TRACE("thread_id", ctx.index);
            }
#endif
            auto init_ux = [](auto, auto, auto rqj, auto uxj) { la::negate(rqj, uxj); };
            combined_solver.foreach_stage(ctx, init_ux, combined_rq, combined_ux);
            auto init_λ = [](auto, auto, auto bj, auto λj) { la::copy(bj, λj); };
            combined_solver.foreach_stage(ctx, init_λ, combined_b, combined_λ);

            ctx.run_single_sync([&] { combined_t0 = clock::now(); });
            combined_solver.factor_solve(ctx, 1e100, 0, {}, combined_ux, combined_λ);
            combined_solver.solve_reverse(ctx, combined_ux, combined_λ);
            ctx.run_single_sync([&] { combined_t1 = clock::now(); });
        }
    });
    save_traces("fanout-combined.csv");

    auto combined_ux_lin = combined_solver.unpack_variables(combined_ux);
    auto combined_λ_lin  = combined_solver.unpack_dynamics(combined_λ);
    guanaqo::MatrixView<real_t, index_t> combined_u0{
        {.data = combined_ux_lin.data(), .rows = combined_ocp.dim.nu, .cols = 1}};
    guanaqo::MatrixView<real_t, index_t> combined_λ0{
        {.data = combined_λ_lin.data(), .rows = combined_ocp.dim.nx, .cols = 1}};
    guanaqo::print_python(std::cout << "[fanout]   u(0) = ", u0_sol(0), "\n");
    guanaqo::print_python(std::cout << "[combined] u(0) = ", combined_u0, "\n");
    guanaqo::print_python(std::cout << "[fanout]   λ(0) = ", λ0_sol(0), "\n");
    guanaqo::print_python(std::cout << "[combined] λ(0) = ", combined_λ0, "\n");
    using ms = std::chrono::duration<double, std::milli>;
    std::println("[fanout]   {:>8.3f} ms", duration_cast<ms>(t1 - t0).count());
    std::println("[combined] {:>8.3f} ms", duration_cast<ms>(combined_t1 - combined_t0).count());

    // Check the error between the two solutions
    constexpr real_t ε = std::numeric_limits<real_t>::epsilon();
    auto u0_norm       = la::norm_inf(u0_sol);
    auto u0_err        = u0_sol;
    la::sub(u0_err(0), combined_u0.top_rows(nu));
    EXPECT_LE(la::norm_inf(u0_err), 10 * u0_norm * static_cast<real_t>(N * (nx + nu)) * ε);
    auto λ0_norm = la::norm_inf(λ0_sol);
    auto λ0_err  = λ0_sol;
    la::sub(λ0_err(0), combined_λ0);
    EXPECT_LE(la::norm_inf(λ0_err), 10 * λ0_norm * static_cast<real_t>(N * (nx + nu)) * ε);
}
