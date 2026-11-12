#include <gtest/gtest.h>

#include <cyqlone/riccati-blasfeo.hpp>
#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/triangular.hpp>
#include <batmat/lut.hpp>
#include <fancyqlone/barrier.hpp>
#include <fancyqlone/cyqlone/cyqlone.hpp>
#include <fancyqlone/cyqlone/tridiagonal-solver.hpp>
#include <fancyqlone/linalg.hpp>
#include <fancyqlone/ocp.hpp>
#include <fancyqlone/packing.hpp>
#include <fancyqlone/random-ocp.hpp>
#include <fancyqlone/tracing.hpp>
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

using fancyqlone::index_t;
using fancyqlone::real_t;

index_t cyq_get_num_proc();

fancyqlone::LinearOCPStorage combine_branches(std::span<const fancyqlone::LinearOCPStorage> ocps);
hyhound::ocp::OCPDataRiccati from_linear_ocp(fancyqlone::LinearOCPStorage &ocp) {
    hyhound::ocp::OCPDataRiccati ocp_riccati{};
    ocp_riccati.N  = ocp.dim.N_horiz - 1;
    ocp_riccati.nx = ocp.dim.nx;
    ocp_riccati.nu = ocp.dim.nu;
    ocp_riccati.ny = ocp.dim.ny;

    for (index_t i = 1; i < ocp.dim.N_horiz; ++i) {
        // if(i ==0) {
        //     ocp_riccati.Q(0) = as_eigen(ocp.Q(0));
        //     ocp_riccati.R(0) = hyhound::ocp::mat::Identity(ocp.dim.nu, ocp.dim.nu);
        //     ocp_riccati.S(0) = as_eigen(ocp.S_trans(0));
        //     ocp_riccati.A(0) = as_eigen(ocp.A(0));
        //     ocp_riccati.B(0) = hyhound::ocp::mat::Zero(ocp.dim.nx, ocp.dim.nu);
        //     ocp_riccati.C(0) = as_eigen(ocp.C(0));
        //     ocp_riccati.D(0) = as_eigen(ocp.D(0));
        // } else{
        ocp_riccati.A(i - 1) = as_eigen(ocp.A(i));
        ocp_riccati.B(i - 1) = as_eigen(ocp.B(i));
        ocp_riccati.C(i - 1) = as_eigen(ocp.C(i));
        ocp_riccati.D(i - 1) = as_eigen(ocp.D(i));
        ocp_riccati.Q(i - 1) = as_eigen(ocp.Q(i));
        ocp_riccati.R(i - 1) = as_eigen(ocp.R(i));
        ocp_riccati.S(i - 1) = as_eigen(ocp.S_trans(i));
    }
    ocp_riccati.C(ocp.dim.N_horiz - 1) = as_eigen(ocp.C(ocp.dim.N_horiz));
    ocp_riccati.Q(ocp.dim.N_horiz - 1) = as_eigen(ocp.Q(ocp.dim.N_horiz));
    return ocp_riccati;
}
// Tests the factorization, factorization updates, and solution of the Cyqlone linear solver.
using blasfeo_mat = fancyqlone::blasfeo::blasfeo_owning_xmat<real_t>;
static std::vector<blasfeo_mat> allocate(index_t n, index_t r, index_t c) {
    std::vector<blasfeo_mat> mat(n);
    std::ranges::generate(mat, [&] { return blasfeo_mat(r, c); });
    return mat;
}
TEST(CyqloneFanBlas, blas) {

    using namespace fancyqlone;
    using batmat::matrix::uninitialized;
    namespace la = fancyqlone::linalg;
    using la::tril;

    const index_t p  = cyq_get_num_proc();
    using Solver     = CyqloneSolver<4, real_t, StorageOrder::RowMajor>;
    using SolverLast = fancyqlone::TridiagonalSolver<real_t>;

    fancyqlone::OCPDim dim{.N_horiz = 160, .nx = 30, .nu = 10, .ny = 0, .ny_N = 0};
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
    fancyqlone::TreeBarrier<> fan_barrier(static_cast<uint32_t>(fanout), {});
    fan_barrier.spin_count = std::numeric_limits<uint32_t>::max();

    // Random initial state
    batmat::matrix::Matrix<real_t, index_t> x0{{.rows = nx, .cols = 1}};
    std::ranges::generate(x0, [&] { return uni(rng); });

    // Allocate space for the solution
    batmat::matrix::Matrix<real_t, index_t> u0_sol{{.rows = nu, .cols = 1}};
    batmat::matrix::Matrix<real_t, index_t> λ0_sol{{.rows = fanout * nx, .cols = 1}};
    std::vector<blasfeo_mat> blas_Bs = allocate(fanout, nu, nx);

    std::vector<blasfeo_mat> blas_SBs    = allocate(fanout, nu, nu);
    std::vector<blasfeo_mat> blas_rs     = allocate(fanout, nu, 1);
    std::vector<blasfeo_mat> blas_LBs    = allocate(fanout, nu, nx);
    std::vector<blasfeo_mat> blas_R0_vec = allocate(1, nu, nu);
    std::vector<blasfeo_mat> blas_r0_vec = allocate(1, nu, 1);

    std::vector<blasfeo_mat> blas_S_total_vec = allocate(1, nu, nu);
    std::vector<blasfeo_mat> blas_r_total_vec = allocate(1, nu, 1);
    std::vector<blasfeo_mat> blas_tmp_vec     = allocate(1, nu, 1);
    std::vector<blasfeo_mat> blas_u0_vec      = allocate(1, nu, 1);
    auto &blas_R0                             = blas_R0_vec[0];
    auto &blas_r0                             = blas_r0_vec[0];
    auto &blas_S_total                        = blas_S_total_vec[0];
    auto &blas_r_total                        = blas_r_total_vec[0];
    auto &blas_tmp                            = blas_tmp_vec[0];
    auto &blas_u0                             = blas_u0_vec[0];

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
        auto cocp           = fancyqlone::CyqloneStorage<>::build(ocp);
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
        tricyqle_params.solve_method = fancyqlone::SolveMethod::None;
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

            la::gemv_add(LBs.batch(i).transposed(), rs.batch(0), λ_last.batch(0));
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

    auto solve_fan_blas = [&](index_t i, index_t) {
        auto &ocp                                = ocps[i];
        hyhound::ocp::OCPDataRiccati ocp_riccati = from_linear_ocp(ocp);
        auto ocp_blasfeo = fancyqlone::blasfeo::OCPDataRiccati::from_riccati(ocp_riccati);
        fancyqlone::blasfeo::RiccatiFactor fac{.ocp = ocp_blasfeo};
        hyhound::ocp::mat Σ = hyhound::ocp::mat::Zero(0, ocp.dim.N_horiz + 1);
        clock::time_point t0, t1;
        auto params   = std::format("nx={}-nu={}-ny={}-N={}-thr={}", ocp.dim.nx, ocp.dim.nu,
                                    ocp.dim.ny, ocp.dim.N_horiz, 1);
        auto solve_u0 = [&] {
            GUANAQO_TRACE_REGION("fan solve u0", 0);

            const int nu_i = static_cast<int>(nu);
            const int nx_i = static_cast<int>(nx);

            blasfeo_dtrsm_rltn(nu_i, nx_i, 1.0, fac.L[0], nx_i,
                               nx_i,              // L_i, lower triangular state block
                               &blas_Bs[i], 0, 0, // B_i^T
                               &blas_LBs[i], 0, 0 // output LBs_i
            );

            if (i == 0) {
                blasfeo_dsyrk_ln(nu_i, nx_i, 1.0, &blas_LBs[i], 0, 0, &blas_LBs[i], 0, 0, 1.0,
                                 &blas_R0, 0, 0, &blas_SBs[i], 0, 0);
            } else {
                blasfeo_dsyrk_ln(nu_i, nx_i, 1.0, &blas_LBs[i], 0, 0, &blas_LBs[i], 0, 0, 0.0,
                                 &blas_SBs[i], 0, 0, &blas_SBs[i], 0, 0);
            }

            if (i == 0) {
                blasfeo_dgemm_nn(nu_i, 1, nx_i, -1.0, &blas_LBs[i], 0, 0, &blas_lambda0[i], 0, 0,
                                 1.0, &blas_r0, 0, 0, &blas_rs[i], 0, 0);
            } else {
                blasfeo_dgemm_nn(nu_i, 1, nx_i, -1.0, &blas_LBs[i], 0, 0, &blas_lambda0[i], 0, 0,
                                 0.0, &blas_rs[i], 0, 0, &blas_rs[i], 0, 0);
            }

            blasfeo_dgecp(nu_i, nu_i, &blas_SBs[0], 0, 0, &blas_S_total, 0, 0);

            for (index_t k = 1; k < fanout; ++k) {
                blasfeo_dgead(nu_i, nu_i, 1.0, &blas_SBs[k], 0, 0, &blas_S_total, 0, 0);
            }

            // ------------------------------------------------------------------
            // Factor S_total = L_S L_S^T.
            // ------------------------------------------------------------------

            blasfeo_dpotrf_l(nu_i, &blas_S_total, 0, 0, &blas_S_total, 0, 0);

            // ------------------------------------------------------------------
            // Aggregate r_total = sum_i rs_i.
            // ------------------------------------------------------------------

            blasfeo_dgecp(nu_i, 1, &blas_rs[0], 0, 0, &blas_r_total, 0, 0);

            for (index_t k = 1; k < fanout; ++k) {
                blasfeo_dgead(nu_i, 1, 1.0, &blas_rs[k], 0, 0, &blas_r_total, 0, 0);
            }

            // ------------------------------------------------------------------
            // Solve:
            //
            //     L_S tmp = r_total
            //     L_S^T u0 = tmp
            // ------------------------------------------------------------------

            blasfeo_dtrsm_llnn(nu_i, 1, 1.0, &blas_S_total, 0, 0, &blas_r_total, 0, 0, &blas_tmp, 0,
                               0);

            blasfeo_dtrsm_lltn(nu_i, 1, 1.0, &blas_S_total, 0, 0, &blas_tmp, 0, 0, &blas_u0, 0, 0);
        };
    };
    auto do_solve = [&] {
        // Synchronize for clearer tracing and timing
        fan_barrier.arrive_and_wait_with_completion(static_cast<uint32_t>(i),
                                                    [&] { t0 = clock::now(); });

        factor_solve(fac, Σ);
        fan_barrier.wait(fan_barrier.arrive_with_completion(static_cast<uint32_t>(i), solve_u0));
        reverse_solve(fac);
        fan_barrier.arrive_and_wait_with_completion(static_cast<uint32_t>(i),
                                                    [&] { t1 = clock::now(); });
    };

    for (int iter = 0; iter <= num_warmup; ++iter) {
        GUANAQO_IF_ITT(__itt_thread_set_name(std::format("OMP({};{})", ctx.index, i).c_str()));
#if GUANAQO_WITH_TRACING
        if (iter == num_warmup)
            fan_barrier.wait(fan_barrier.arrive_with_completion(static_cast<uint32_t>(i), [&] {
                guanaqo::for_each_trace_logger([](auto &logger) { logger.reset(); });
            }));
        GUANAQO_TRACE("thread_id", 100 * (i + 1));
#endif
        do_solve();
    }
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
#if BATMAT_WITH_OPENMP
    omp_set_max_active_levels(2);
    BATMAT_OMP(parallel for num_threads(fanout))
    for (index_t i = 0; i < fanout; ++i)
        solve_fan_blas(i, fanout);
#else
batmat::thread_pool blas_fan_pool(fanout);
blas_fan_pool.sync_run_n(fanout, solve_fan_blas);
#endif
    save_traces("fanout-fan.csv");
    // Solve the combined problem with a single Cyqlone solve, as a reference solution
    auto combined_ocp                     = combine_branches(ocps);
    auto combined_cocp                    = fancyqlone::CyqloneStorage<>::build(combined_ocp);
    auto combined_solver                  = Solver::build(combined_cocp, p);
    auto combined_tricyqle_params         = combined_solver.get_tricyqle_params();
    combined_tricyqle_params.solve_method = fancyqlone::SolveMethod::PCR;
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
