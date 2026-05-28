#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/reduce.hpp>
#include <batmat/linalg/triangular.hpp>
#include <batmat/lut.hpp>
#include <gtest/gtest.h>

#include <cyqlone/barrier.hpp>
#include <cyqlone/cyqlone.hpp>
#include <cyqlone/linalg.hpp>
#include <cyqlone/packing.hpp>
#include <cyqlone/random-ocp.hpp>
#include <cyqlone/tracing.hpp>
#include <cyqlone/tridiagonal-solver.hpp>
#include <batmat/linalg/simdify.hpp>
#include <guanaqo/print.hpp>
#include <guanaqo/trace.hpp>
#include <cyqlone-version.h>
#include <bit>
#include <cstdlib>
#if CYQLONE_WITH_MATIO
#include <cyqlone/matio.hpp>
#endif

#if GUANAQO_WITH_TRACING
#include <filesystem>
#include <fstream>
#endif
#include <iostream>
#include <limits>

using cyqlone::index_t;
using cyqlone::real_t;

index_t cyq_get_num_proc() {
    int p = 8;
#if BATMAT_WITH_OPENMP
    p = omp_get_num_procs();
#endif
    if (const char *env_p = std::getenv("CI_JOB_CPU_LIMIT"))
        p = std::min(p, std::atoi(env_p));
    // floor to the nearest power of two
    return static_cast<index_t>(std::bit_floor(static_cast<unsigned>(std::max(1, p))));
}

// Tests the factorization, factorization updates, and solution of the Cyqlone linear solver.
TEST(CyqloneFanFactorTest, factor) {
    using namespace cyqlone;
    using batmat::matrix::uninitialized;
    namespace la = cyqlone::linalg;
    using la::tril;

    const index_t p  = cyq_get_num_proc();
    using Solver     = CyqloneSolver<4, real_t, StorageOrder::RowMajor>;
    using SolverLast = cyqlone::TridiagonalSolver<real_t>;
    int N=30;
    char filename[256];
    sprintf(filename, "python/cmpc/ocp_data%d_0.mat", N);
    auto matfp       = cyqlone::open_mat(filename);
    cyqlone::LinearOCPStorage ocp;
    cyqlone::read_from_mat(matfp.get(), "ocp", ocp);
    auto dim   = ocp.dim;
    index_t nx = dim.nx, nu = dim.nu;
    index_t fanout    = 2;
    const index_t nux = dim.nu + dim.nx;
    std::mt19937 rng(102030405);
    std::uniform_real_distribution<real_t> uni(-1, 1);
    std::bernoulli_distribution bern(0.01);
    std::vector<cyqlone::parallel::SharedContext> contexts;
    std::vector<Solver> cyqlones;
    std::vector<SolverLast> last_solvers;
    // B(0)ᵀ for each branch
    // TODO: initialize
    SolverLast::matrix Bs{{.depth = fanout, .rows = nu, .cols = nx}};
    SolverLast::matrix uxs{{.depth = fanout, .rows = nux, .cols = 1}, uninitialized};
    SolverLast::matrix λs{{.depth = fanout, .rows = nx, .cols = 1}, uninitialized};
    // B(0)ᵀ L(0)⁻ᵀ for each branch
    SolverLast::matrix LBs{{.depth = fanout, .rows = nu, .cols = nx}, uninitialized};
    // Schur complement contributions B(0)ᵀ L(0)⁻ᵀ L(0)⁻¹ B(0) for each branch,
    // R(0) + B(0)ᵀ L(0)⁻ᵀ L(0)⁻¹ B(0) for the first one.
    SolverLast::matrix SBs{{.depth = fanout, .rows = nu, .cols = nu}, uninitialized};
    // Right-hand side contributions B(0)ᵀ L(0)⁻ᵀ λ(0) for each branch,
    // -r(0) + B(0)ᵀ L(0)⁻ᵀ λ(0) for the first one.
    SolverLast::matrix rs{{.depth = fanout, .rows = nu, .cols = 1}, uninitialized};
    // Synchronization between the fanout branches
    cyqlone::TreeBarrier<> fan_barrier(static_cast<uint32_t>(fanout), {});

    // TODO: initialize rs(0) to -r(0), i.e. the negative gradient w.r.t. u(0).
    rs(0).set_constant(0);
    // TODO: initialize SBs(0) to R(0), i.e. the Hessian w.r.t. u(0).
    SBs(0).set_constant(0);
    SBs(0).set_diagonal(1);

    contexts.reserve(fanout);
    cyqlones.reserve(fanout);
    last_solvers.reserve(fanout);
    index_t p_fan = p / fanout;

    for (index_t i = 0; i < fanout; ++i) {
        char filename[256];
        sprintf(filename, "python/cmpc/ocp_data%d_%d.mat", N, i);
        auto matfp       = cyqlone::open_mat(filename);
        cyqlone::LinearOCPStorage ocp;
        cyqlone::read_from_mat(matfp.get(), "ocp", ocp);
        // printf("%d\n", );
        std::cout << "||b||_2 = " << bla::norm_2(ocp.b()) << ":\n";

        auto cocp = cyqlone::CyqloneStorage<real_t>::build(ocp);
        // Introduce an unused variable u(0) in each Cyqlone block
        std::cout << "||F||_2 = " << bla::norm_2(cocp.data_F) << "\n";
        cocp.data_F(0).left_cols(nu).set_constant(0);    // B(0) = 0
        cocp.data_H(0).top_left(nu, nu).set_constant(0); // R(0) = I
        cocp.data_H(0).top_left(nu, nu).set_diagonal(1); //
        cocp.data_rq(0).top_rows(nu).set_constant(0);    // r(0) = 0
        auto &solver                 = cyqlones.emplace_back(Solver::build(cocp, p_fan));
        auto tricyqle_params         = solver.get_tricyqle_params();
        tricyqle_params.solve_method = cyqlone::SolveMethod::None;
        tricyqle_params.cr_max_update_fraction_Y0 = 9999;
        tricyqle_params.pcr_max_update_fraction   = 9999;
        solver.update_tricyqle_params(tricyqle_params);
        auto pctx     = solver.create_parallel_context();
        auto &context = contexts.emplace_back(std::move(*pctx));
        // Spin a bit longer to get more deterministic timings
        context.set_barrier_spin_count(std::numeric_limits<uint32_t>::max());

        GUANAQO_IF_ITT(context.run([i](auto &ctx) {
            __itt_thread_set_name(std::format("OMP({};{})", ctx.index, i).c_str());
        }));

        // Solver for the final block-tridiagonal system.
        last_solvers.emplace_back(SolverLast{.block_size = solver.nx, .num_blocks = solver.v});
    }
    BATMAT_OMP_IF(omp_set_max_active_levels(2));
    BATMAT_OMP(parallel for num_threads(fanout))
    for (index_t i = 0; i < fanout; ++i) {
        auto &solver      = cyqlones[i];
        auto &solver_last = last_solvers[i];
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
        // Factor and forward solve most of each Cyqlone block
        contexts[i].run([&](auto ctx) { solver.factor_solve(ctx, 1e100, 0, {}, ux, λ); });
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
        i == 0 ? la::gemv_add(LBs.batch(i), λ_last.batch(0), rs.batch(i))
               : la::gemv(LBs.batch(i), λ_last.batch(0), rs.batch(i));
        // Solve for u(0) on a single thread
        fan_barrier.wait(fan_barrier.arrive_with_completion(static_cast<uint32_t>(i), [&] {
            for (index_t i = 1; i < fanout; ++i)
                la::add(SBs.batch(0), SBs.batch(i));
            la::potrf(tril(SBs.batch(0)));
            for (index_t i = 1; i < fanout; ++i)
                la::add(rs.batch(0), rs.batch(i));
            la::trsm(tril(SBs.batch(0)), rs.batch(0));
            la::trsm(tril(SBs.batch(0)).transposed(), rs.batch(0)); // rs(0) now contains u(0)
        }));
        // Compute the contribution of u(0) to λ(0) for each Cyqlone block
        la::gemv_add(LBs.batch(i).transposed(), rs.batch(0), λ_last.batch(0));
        // Reverse solve of the final block-tridiagonal system for each Cyqlone block
        solver_last.solve_reverse(λ_last);
        la::pack(λ_last, λ.batch(0));
        // Solve each Cyqlone block with the updated multipliers λ
        contexts[i].run([&](auto ctx) { solver.solve_reverse(ctx, ux, λ); });
        uxs.batch(i) = ux.batch(0);
        λs.batch(i) = λ.batch(0);
        std::cout << bla::norm_2(ux) << "\n";
        std::cout << bla::norm_2(λ) << "\n";
    }

    // Solve the System as a whole:
    sprintf(filename, "python/cmpc/ocp_data%d_combined.mat", N);
    auto matfp_full       = cyqlone::open_mat(filename);
    cyqlone::LinearOCPStorage ocp_full;
    cyqlone::read_from_mat(matfp_full.get(), "ocp", ocp_full);
    dim   = ocp_full.dim;
    nx = dim.nx, nu = dim.nu;
    const index_t nux_full = dim.nu + dim.nx;
    auto cocp = cyqlone::CyqloneStorage<real_t>::build(ocp_full);
    Solver solver = Solver::build(cocp, p);
    auto tricyqle_params = solver.get_tricyqle_params();
    tricyqle_params.solve_method = cyqlone::SolveMethod::PCR;
    tricyqle_params.cr_max_update_fraction_Y0 = 9999;
    tricyqle_params.pcr_max_update_fraction   = 9999;
    solver.update_tricyqle_params(tricyqle_params);
    auto pctx = solver.create_parallel_context();
        // Spin a bit longer to get more deterministic timings
    pctx->set_barrier_spin_count(std::numeric_limits<uint32_t>::max());
    GUANAQO_IF_ITT(pctx->run(
        [](auto &ctx) { __itt_thread_set_name(std::format("OMP({})", ctx.index).c_str()); }));
    Solver::matrix b{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
            λ_full{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
            rq{{.depth = solver.ceil_N(), .rows = nux_full, .cols = 1}},
            ux_full{{.depth = solver.ceil_N(), .rows = nux_full, .cols = 1}},
            Mᵀλ{{.depth = solver.ceil_N(), .rows = nux_full, .cols = 1}},
            grad{{.depth = solver.ceil_N(), .rows = nux_full, .cols = 1}},
            Mxb{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}};
    pctx->run([&](auto &ctx) { 
        solver.factor_solve(ctx, 1e100, 0, {}, ux_full, λ_full);
        solver.solve_reverse(ctx, ux_full, λ_full); 
    });
    std::cout << bla::norm_2(ux_full) << "\n";
    std::cout << bla::norm_2(uxs.batch(0)) << "\n";
    std::cout << bla::norm_2(uxs.batch(1)) << "\n";



}
