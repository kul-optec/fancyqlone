#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/triangular.hpp>
#include <batmat/lut.hpp>
#include <gtest/gtest.h>

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
using SolverLast = cyqlone::TridiagonalSolver<real_t>;
using vl_t       = std::integral_constant<index_t, 1>;

#define NO_PENALTY 0
#define WITH_UPDATES 1

index_t cyq_get_num_proc();

// Tests the factorization, factorization updates, and solution of the Cyqlone linear solver.
TEST(CyqloneFanFactorTest, factor) {
    using namespace cyqlone;
    using batmat::matrix::uninitialized;
    namespace la = cyqlone::linalg;
    using la::tril;

    const index_t p = cyq_get_num_proc();
    using Solver    = CyqloneSolver<4, real_t, StorageOrder::RowMajor>;
    auto matfp      = cyqlone::open_mat("python/cmpc/ocp_data1024.mat");
    cyqlone::LinearOCPStorage ocp;
    auto dim  = ocp.dim;
    index_t N = dim.N_horiz, nx = dim.nx, nu = dim.nu;
    index_t ny   = 0;
    index_t ny_0 = 0, ny_N = 0, nyM = 0;
    index_t fanout    = 2;
    const index_t nux = dim.nu + dim.nx;
    std::mt19937 rng(102030405);
    std::uniform_real_distribution<real_t> uni(-1, 1);
    std::bernoulli_distribution bern(0.01);
    cyqlone::read_from_mat(matfp.get(), "ocp", ocp);
    std::vector<cyqlone::parallel::SharedContext> contexts;
    std::vector<Solver> cyqlones;
    std::vector<SolverLast> last_solvers;
    SolverLast::matrix Bs{{.depth = fanout, .rows = nu, .cols = nx}, uninitialized};
    SolverLast::matrix LBs{{.depth = fanout, .rows = nu, .cols = nx}, uninitialized};
    SolverLast::matrix SBs{{.depth = fanout, .rows = nu, .cols = nu}, uninitialized};

    contexts.reserve(fanout);
    cyqlones.reserve(fanout);
    last_solvers.reserve(fanout);
    index_t p_fan = p / fanout;
    BATMAT_OMP(parallel for num_threads(fanout))
    for (index_t i = 0; i < fanout; ++i) {
        auto cocp                    = cyqlone::CyqloneStorage<>::build(ocp);
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
    BATMAT_OMP(parallel for num_threads(fanout))
    for (index_t i = 0; i < fanout; ++i) {
        contexts[i].run([&, i](auto ctx) {
            auto &solver      = cyqlones[i];
            auto &solver_last = last_solvers[i];
            SolverLast::matrix λ_last{{.depth = solver.v, .rows = solver.nx, .cols = 1}};
            std::vector<real_t> Σ_lin((N - 1) * ny + ny_0 + ny_N);
            Solver::matrix b{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
                λ{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
                rq{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
                ux{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
                Mᵀλ{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
                DCux{{.depth = solver.ceil_N(), .rows = nyM, .cols = 1}},
                DCᵀΣDCux{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
                grad{{.depth = solver.ceil_N(), .rows = nux, .cols = 1}},
                Mxb{{.depth = solver.ceil_N(), .rows = dim.nx, .cols = 1}},
                Σ{{.depth = solver.ceil_N(), .rows = nyM, .cols = 1}},
                Σ2{{.depth = solver.ceil_N(), .rows = nyM, .cols = 1}},
                ΔΣ{{.depth = solver.ceil_N(), .rows = nyM, .cols = 1}};

            // Initialize penalties (two different ones, to test the updates)
            std::ranges::generate(Σ_lin, [&] { return std::exp2(uni(rng)); });
            std::vector<real_t> Σ_lin2 = Σ_lin;
#if NO_PENALTY
            std::ranges::fill(Σ_lin2, 0);
#elif WITH_UPDATES
            for (auto &Σ2i : Σ_lin2)
                if (bern(rng))
                    Σ2i = std::exp2(uni(rng));
#endif
            solver.pack_constraints(Σ_lin, Σ);
            solver.pack_constraints(Σ_lin2, Σ2);
            std::ranges::transform(Σ2, Σ, std::ranges::begin(ΔΣ), std::minus<>{});

            const auto factor_last = [&](auto &ctx) {
                ctx.run_single_sync([&] {
                    la::unpack(tril(solver.tricyqle.cr_L.batch(0)), tril(solver_last.L));
                    la::unpack(solver.tricyqle.cr_Y.batch(0), solver_last.U.transposed());
                    solver_last.factor();
                });
            };
            const auto forward_solve_last = [&](auto &ctx) {
                ctx.run_single_sync([&] {
                    la::unpack(λ.batch(0), λ_last);
                    solver_last.solve_forward(λ_last);
                    la::pack(λ_last, λ.batch(0));
                });
            };
            solver.factor(ctx, 1e100, 0, Σ);
            solver.solve_forward(ctx, ux, λ);
            factor_last(ctx);
            forward_solve_last(ctx);
            bla::trsm(Bs.batch(i).transposed(), tril(solver_last.L.batch(0)).transposed(),
                      LBs.batch(i).transposed());
            bla::syrk(LBs.batch(i), tril(SBs.batch(i)));
        });
    }
    for (index_t i = 1; i < fanout; ++i)
        bla::add(SBs.batch(0), SBs.batch(i));
    bla::potrf(tril(SBs.batch(0)));
}
