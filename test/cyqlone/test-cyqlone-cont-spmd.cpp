#include <gtest/gtest.h>

#include <cyqlone/barrier.hpp>
#include <cyqlone/cyqlone.hpp>
#include <cyqlone/linalg.hpp>
#include <cyqlone/ocp.hpp>
#include <cyqlone/packing.hpp>
#include <cyqlone/random-ocp.hpp>
#include <cyqlone/tracing.hpp>
#include <cyqlone/tridiagonal-solver.hpp>
#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/triangular.hpp>
#include <batmat/lut.hpp>
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

using cyqlone::index_t;
using cyqlone::real_t;

index_t cyq_get_num_proc();

cyqlone::LinearOCPStorage combine_branches(std::span<const cyqlone::LinearOCPStorage> ocps) {
    BATMAT_ASSERT(!ocps.empty());
    auto fld_max = [](index_t(cyqlone::OCPDim::*m)) {
        return [m](index_t acc, const auto &ocp) { return std::max(acc, ocp.dim.*m); };
    };
    auto fld_sum = [](index_t(cyqlone::OCPDim::*m)) {
        return [m](index_t acc, const auto &ocp) { return acc + ocp.dim.*m; };
    };
    cyqlone::OCPDim dim{
        .N_horiz = std::ranges::fold_left(ocps, index_t{0}, fld_max(&cyqlone::OCPDim::N_horiz)),
        .nx      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::nx)),
        .nu      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::nu)),
        .ny      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::ny)),
        .ny_N    = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::ny_N)),
    }; // TODO: this is a bit redundant, since x(0) and u(0) need to have consistent dimensions
    cyqlone::LinearOCPStorage combined_ocp(dim);

    index_t nx_offset = 0, nu_offset = 0, ny_offset = 0, ny_N_offset = 0;
    { // Take cost of the first stage from the first OCP (there is only one x(0) and one u(0))
        const auto &ocp                        = ocps.front();
        combined_ocp.b(0).top_rows(ocp.dim.nx) = ocp.b(0); // x0
        combined_ocp.Q(0).block(0, 0, ocp.dim.nx, ocp.dim.nx) += ocp.Q(0);
        combined_ocp.R(0).block(0, 0, ocp.dim.nu, ocp.dim.nu) += ocp.R(0);
        combined_ocp.S(0).block(0, 0, ocp.dim.nu, ocp.dim.nx) += ocp.S(0);
        combined_ocp.S_trans(0).block(0, 0, ocp.dim.nx, ocp.dim.nu) += ocp.S_trans(0);
        combined_ocp.q(0).block(0, 0, ocp.dim.nx, 1) += ocp.q(0);
        combined_ocp.r(0).block(0, 0, ocp.dim.nu, 1) += ocp.r(0);
    }
    // Later stages can diverge for the different OCPs, so these all become diagonal matrices,
    // except for the coupling from the first stage
    for (const auto &ocp : ocps) {
        const index_t N = ocp.dim.N_horiz;
        // Copy dynamics
        combined_ocp.A(0).block(nx_offset, 0, ocp.dim.nx, ocp.dim.nx) = ocp.A(0);
        combined_ocp.B(0).block(nx_offset, 0, ocp.dim.nx, ocp.dim.nu) = ocp.B(0);
        for (index_t i = 1; i < N; ++i) {
            combined_ocp.A(i).block(nx_offset, nx_offset, ocp.dim.nx, ocp.dim.nx) = ocp.A(i);
            combined_ocp.B(i).block(nx_offset, nu_offset, ocp.dim.nx, ocp.dim.nu) = ocp.B(i);
            combined_ocp.b(i).block(nx_offset, 0, ocp.dim.nx, 1)                  = ocp.b(i);
        }
        combined_ocp.b(N).block(nx_offset, 0, ocp.dim.nx, 1) = ocp.b(N);
        // Copy constraints
        combined_ocp.C(0).block(ny_offset, 0, ocp.dim.ny, ocp.dim.nx) = ocp.C(0);
        combined_ocp.D(0).block(ny_offset, 0, ocp.dim.ny, ocp.dim.nu) = ocp.D(0);
        combined_ocp.b_min(0).block(ny_offset, 0, ocp.dim.ny, 1)      = ocp.b_min(0);
        combined_ocp.b_max(0).block(ny_offset, 0, ocp.dim.ny, 1)      = ocp.b_max(0);
        for (index_t i = 1; i < N; ++i) {
            combined_ocp.C(i).block(ny_offset, nx_offset, ocp.dim.ny, ocp.dim.nx) = ocp.C(i);
            combined_ocp.D(i).block(ny_offset, nu_offset, ocp.dim.ny, ocp.dim.nu) = ocp.D(i);
            combined_ocp.b_min(i).block(ny_offset, 0, ocp.dim.ny, 1)              = ocp.b_min(i);
            combined_ocp.b_max(i).block(ny_offset, 0, ocp.dim.ny, 1)              = ocp.b_max(i);
        }
        combined_ocp.C(N).block(ny_N_offset, nx_offset, ocp.dim.ny_N, ocp.dim.nx) = ocp.C(N);
        combined_ocp.b_min(N).block(ny_N_offset, 0, ocp.dim.ny_N, 1)              = ocp.b_min(N);
        combined_ocp.b_max(N).block(ny_N_offset, 0, ocp.dim.ny_N, 1)              = ocp.b_max(N);
        // Copy cost
        for (index_t i = 1; i < N; ++i) {
            combined_ocp.Q(i).block(nx_offset, nx_offset, ocp.dim.nx, ocp.dim.nx) = ocp.Q(i);
            combined_ocp.R(i).block(nu_offset, nu_offset, ocp.dim.nu, ocp.dim.nu) = ocp.R(i);
            combined_ocp.S(i).block(nu_offset, nx_offset, ocp.dim.nu, ocp.dim.nx) = ocp.S(i);
            combined_ocp.S_trans(i).block(nx_offset, nu_offset, ocp.dim.nx, ocp.dim.nu) =
                ocp.S_trans(i);
            combined_ocp.q(i).block(nx_offset, 0, ocp.dim.nx, 1) = ocp.q(i);
            combined_ocp.r(i).block(nu_offset, 0, ocp.dim.nu, 1) = ocp.r(i);
        }
        combined_ocp.Q(N).block(nx_offset, nx_offset, ocp.dim.nx, ocp.dim.nx) = ocp.Q(N);
        combined_ocp.q(N).block(nx_offset, 0, ocp.dim.nx, 1)                  = ocp.q(N);

        nx_offset += ocp.dim.nx;
        nu_offset += ocp.dim.nu;
        ny_offset += ocp.dim.ny;
        ny_N_offset += ocp.dim.ny_N;
    }

    const index_t nx_max = std::ranges::fold_left(ocps, index_t{0}, fld_max(&cyqlone::OCPDim::nx)),
                  nu_max = std::ranges::fold_left(ocps, index_t{0}, fld_max(&cyqlone::OCPDim::nu));
    for (index_t i = nx_max; i < combined_ocp.dim.nx; ++i)
        combined_ocp.Q(0)(i, i) = 1; // regularize unused state variables in the cost
    for (index_t i = nu_max; i < combined_ocp.dim.nu; ++i)
        combined_ocp.R(0)(i, i) = 1; // regularize unused control variables in the cost

    return combined_ocp;
}

// Tests the factorization, factorization updates, and solution of the Cyqlone linear solver.
TEST(CyqloneFanFactorTestSPMD, factor) {
    using namespace cyqlone;
    using batmat::matrix::uninitialized;
    namespace la = cyqlone::linalg;
    using la::tril;

    const index_t p  = cyq_get_num_proc();
    using Solver     = CyqloneSolver<4, real_t, StorageOrder::RowMajor>;
    using SolverLast = cyqlone::TridiagonalSolver<real_t>;

    cyqlone::OCPDim dim{.N_horiz = 32, .nx = 7, .nu = 5, .ny = 0, .ny_N = 0};
    const index_t nx = dim.nx, nu = dim.nu;
    const index_t nux = dim.nu + dim.nx;
    index_t fanout    = 2;
    std::mt19937 rng(102030405);
    std::uniform_real_distribution<real_t> uni(-1, 1);
    std::vector<LinearOCPStorage> ocps(fanout);
    // B(0)ᵀ for each branch
    SolverLast::matrix Bs{{.depth = fanout, .rows = nu, .cols = nx}};
    // B(0)ᵀ L(0)⁻ᵀ for each branch
    SolverLast::matrix LBs{{.depth = fanout, .rows = nu, .cols = nx}, uninitialized};
    // Schur complement contributions B(0)ᵀ L(0)⁻ᵀ L(0)⁻¹ B(0) for each branch,
    // R(0) + B(0)ᵀ L(0)⁻ᵀ L(0)⁻¹ B(0) for the first one.
    SolverLast::matrix SBs{{.depth = fanout, .rows = nu, .cols = nu}, uninitialized};
    // Right-hand side contributions B(0)ᵀ L(0)⁻ᵀ λ(0) for each branch,
    // -r(0) - B(0)ᵀ L(0)⁻ᵀ λ(0) for the first one.
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

    const index_t p_fan = std::max<index_t>(p / fanout, 1);
    auto solve_fan      = [&](index_t i, index_t, auto ctx) {
        auto &ocp = ocps[i] = generate_random_ocp(dim, static_cast<uint32_t>(i));
        ocp.b(0)            = x0(0); // same initial state for each branch
        auto cocp           = cyqlone::CyqloneStorage<>::build(ocp);
        // Store B(0)ᵀ for each branch; R(0) and -r(0) for the first branch
        la::copy(cocp.data_F(0).left_cols(nu).transposed(), Bs(i));
        if (i == 0) {
            la::copy(cocp.data_H(0).top_left(nu, nu), SBs(i));
            la::negate(cocp.data_rq(0).top_rows(nu), rs(i));
        }
        // Introduce an unused variable u(0) in each Cyqlone block
        cocp.data_F(0).left_cols(nu).set_constant(0);    // B(0) = 0
        cocp.data_H(0).top_left(nu, nu).set_constant(0); // R(0) = I
        cocp.data_H(0).top_left(nu, nu).set_diagonal(1); //
        cocp.data_rq(0).top_rows(nu).set_constant(0);    // r(0) = 0
        // Cyqlone solver
        auto solver                               = Solver::build(cocp, p_fan);
        auto tricyqle_params                      = solver.get_tricyqle_params();
        tricyqle_params.solve_method              = cyqlone::SolveMethod::None;
        tricyqle_params.cr_max_update_fraction_Y0 = 9999;
        tricyqle_params.pcr_max_update_fraction   = 9999;
        solver.update_tricyqle_params(tricyqle_params);
        auto pctx = solver.create_parallel_context();
        pctx->set_barrier_spin_count(std::numeric_limits<uint32_t>::max());

        // Solver for the final block-tridiagonal system.
        SolverLast solver_last{.block_size = solver.nx, .num_blocks = solver.v};

        GUANAQO_IF_ITT(
            __itt_thread_set_name(std::format("OMP({};{})", ctx.index, i).c_str());
        );
#if GUANAQO_WITH_TRACING
        GUANAQO_TRACE("thread_id", ctx.index + 100 * (i + 1)); 
#endif

        SolverLast::matrix λ_last{{.depth = solver.v, .rows = solver.nx, .cols = 1}};
        Solver::matrix b{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
            λ{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
            rq{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
            ux{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
            Mᵀλ{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
            grad{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
            Mxb{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}};
        // Cost gradient r(j) and q(j)
        solver.initialize_gradient(cocp, rq);
        // Right-hand side of the constraints b(j)
        solver.initialize_rhs(cocp, b);
        // Right-hand side of the KKT system is the negative gradient
        la::negate(rq, ux);
        la::copy(b, λ);

        fan_barrier.arrive_and_wait(static_cast<uint32_t>(i)); // synchronize for tracing

        // Factor and forward solve most of each Cyqlone block
        solver.factor_solve(ctx, 1e100, 0, {}, ux, λ);
        {
            GUANAQO_TRACE_REGION("fan factor forward solve λ0", 0);
            // Factor the final block-tridiagonal Schur complement of each Cyqlone block
            la::unpack(tril(solver.tricyqle.cr_L.batch(0)), tril(solver_last.L));
            la::unpack(solver.tricyqle.cr_Y.batch(0), solver_last.U.transposed());
            solver_last.factor();
            // Compute the contribution to the final Schur complement (system involving only u(0))
            la::trsm(Bs.batch(i), tril(solver_last.L.batch(0)).transposed(), LBs.batch(i));
            i == 0 ? la::syrk_add(LBs.batch(i), tril(SBs.batch(i)))
                   : la::syrk(LBs.batch(i), tril(SBs.batch(i)));
            // Forward solve of the final block-tridiagonal system, to get λ(0) for each Cyqlone block
            la::unpack(λ.batch(0), λ_last);
            solver_last.solve_forward(λ_last);
            i == 0 ? la::gemv_sub(LBs.batch(i), λ_last.batch(0), rs.batch(i))
                   : la::gemv_neg(LBs.batch(i), λ_last.batch(0), rs.batch(i));
        }
        // Solve for u(0) on a single thread
        fan_barrier.wait(fan_barrier.arrive_with_completion(static_cast<uint32_t>(i), [&] {
            GUANAQO_TRACE_REGION("fan solve u0", 0);
            for (index_t i = 1; i < fanout; ++i)
                la::add(SBs.batch(0), SBs.batch(i));
            la::potrf(tril(SBs.batch(0)));
            for (index_t i = 1; i < fanout; ++i)
                la::add(rs.batch(0), rs.batch(i));
            la::trsm(tril(SBs.batch(0)), rs.batch(0));
            la::trsm(tril(SBs.batch(0)).transposed(), rs.batch(0)); // rs(0) now contains u(0)
            u0_sol(0) = rs(0);
        }));
        {
            GUANAQO_TRACE_REGION("fan solve reverse λ0", 0);
            // Compute the contribution of u(0) to λ(0) for each Cyqlone block
            la::gemv_add(LBs.batch(i).transposed(), rs.batch(0), λ_last.batch(0));
            // Reverse solve of the final block-tridiagonal system for each Cyqlone block
            solver_last.solve_reverse(λ_last);
            la::pack(λ_last, λ.batch(0));
            λ0_sol(0).middle_rows(i * nx, nx) = λ_last(0);
        }
        // Solve each Cyqlone block with the updated multipliers λ
        solver.solve_reverse(ctx, ux, λ);
    };
    auto do_solve_fan = [&] {
#if BATMAT_WITH_OPENMP
        omp_set_max_active_levels(2);
        BATMAT_OMP(parallel for num_threads(fanout))
        for (index_t i = 0; i < fanout; ++i)
            contexts[i].run([&](auto &ctx) { solve_fan(i, fanout, ctx); });
#else
        std::cout << "Running fan solve with " << fanout << " threads on a thread pool\n";
        // batmat::thread_pool fan_pool(fanout);
        // fan_pool.sync_run_n(fanout, solve_fan);
#endif
    };

    for (index_t i = 0; i < 50; ++i) // Warmup
        do_solve_fan();
#if GUANAQO_WITH_TRACING
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reset(); });
#endif
    do_solve_fan();

    // Solve the combined problem with a single Cyqlone solve, as a reference solution
    auto combined_ocp    = combine_branches(ocps);
    auto combined_cocp   = cyqlone::CyqloneStorage<>::build(combined_ocp);
    auto combined_solver = Solver::build(combined_cocp, p);
    auto combined_rq     = combined_solver.initialize_gradient(combined_cocp);
    auto combined_b      = combined_solver.initialize_rhs(combined_cocp);
    auto combined_ux     = combined_rq;
    auto combined_λ      = combined_b;
    la::negate(combined_ux);
    auto pctx = combined_solver.create_parallel_context();
    pctx->set_barrier_spin_count(std::numeric_limits<uint32_t>::max());
    pctx->run([&](auto &ctx) {
        combined_solver.factor_solve(ctx, 1e100, 0, {}, combined_ux, combined_λ);
        combined_solver.solve_reverse(ctx, combined_ux, combined_λ);
    });
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

    // Check the error between the two solutions
    constexpr real_t ε = std::numeric_limits<real_t>::epsilon();
    auto u0_err        = u0_sol;
    la::sub(u0_err(0), combined_u0.top_rows(nu));
    EXPECT_LE(la::norm_inf(u0_err), 100 * ε);
    auto λ0_err = λ0_sol;
    la::sub(λ0_err(0), combined_λ0);
    EXPECT_LE(la::norm_inf(λ0_err), 5000 * ε);

#if GUANAQO_WITH_TRACING
    {
        namespace fs     = std::filesystem;
        std::string name = std::format("fan.csv");
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
    }
#endif
}
