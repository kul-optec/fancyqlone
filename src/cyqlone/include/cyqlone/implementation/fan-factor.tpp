#include <cyqlone/cyqlone.hpp>
#include <cyqlone/fan-cyqlone.hpp>
#include <cyqlone/linalg.hpp>
#include <cyqlone/packing.hpp>
#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/triangular.hpp>
#include <batmat/lut.hpp>
#include <batmat/openmp.h>

namespace CYQLONE_NS(cyqlone) {
namespace la = cyqlone::linalg;

using la::tril;
using la::unpack;
// Algorithm 2 “Cyqlone factorization”
// §4 “Cyqlone: Parallel factorization and solution of KKT systems with optimal control structure”
//
// Optionally fused factorization and forward solve of the KKT system.
// Factor the first level corresponidng to u0 and λ0 sequentially
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
template <bool Factor, bool Solve>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve_λ0(index_t branch, FanStorage λ) {
    if constexpr (Factor) {
        // Factor the final block-tridiagonal Schur complement of each Cyqlone block
        la::unpack(tril(solver_storages[branch].cyqlone_solver.tricyqle.cr_L.batch(0)),
                   tril(solver_storages[branch].tridiagonal_solver.L));
        la::unpack(solver_storages[branch].cyqlone_solver.tricyqle.cr_Y.batch(0),
                   solver_storages[branch].tridiagonal_solver.U.transposed());
        solver_storages[branch].tridiagonal_solver.factor();
        // Compute the contribution to the final Schur complement (system involving only u(0))
        la::trsm(solver_storages[branch].B0,
                 tril(solver_storages[branch].tridiagonal_solver.L.batch(0)).transposed(),
                 solver_storages[branch].LB);
        branch == 0 ? la::syrk_add(solver_storages[branch].LB, tril(R0.batch(branch)),
                                   tril(SBs.batch(branch)))
                    : la::syrk(solver_storages[branch].LB, tril(SBs.batch(branch)));
    }
    if constexpr (Solve) {
        index_t nx = solver_storages[branch].cyqlone_solver.nx;
        typename SolverLast::matrix λ_last{{.depth = v, .rows = nx, .cols = 1}, batmat::matrix::uninitialized}; 
        // Forward solve of the final block-tridiagonal system, to get λ(0) for each Cyqlone block
        la::unpack(λ.branches[branch].batch(0), λ_last);
        solver_storages[branch].tridiagonal_solver.solve_forward(λ_last);
        branch == 0
            ? la::gemv_sub(solver_storages[branch].LB, λ_last.batch(0),
                           r0.batch(branch), rs.batch(branch))
            : la::gemv_neg(solver_storages[branch].LB, λ_last.batch(0),
                           rs.batch(branch));
        λ.first.batch(0).middle_rows(branch * nx, nx) = λ_last.batch(0);
    }
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
template <bool Factor, bool Solve>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve_u0(FanStorage ux) {
    if constexpr (Factor) {
        for (index_t b = 0; b < num_branches; ++b)
            la::add(SBs.batch(0), SBs.batch(b));
        la::potrf(tril(SBs.batch(0)));
    }
    if constexpr (Solve) {
        for (index_t b = 0; b < num_branches; ++b)
            la::add(rs.batch(0), rs.batch(b));
        la::trsm(tril(SBs.batch(0)), rs.batch(0), ux.first.batch(0));
    }
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse_u0(FanStorage ux) const {
    la::trsm(tril(SBs.batch(0)).transposed(),
             ux.first.batch(0)); // ux.first now contains u(0)
}
// Reverse solve for λ(0) on each branch, after solving for u(0)
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>

void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse_λ0(index_t branch,
                                                                  FanStorage λ) const {
    GUANAQO_TRACE_REGION("fan solve reverse λ0", 0);
    // Compute the contribution of u(0) to λ(0) for each Cyqlone block
    index_t nx = solver_storages[branch].cyqlone_solver.nx;

    typename SolverLast::matrix λ_last{{.depth = v, .rows = nx, .cols = 1}, batmat::matrix::uninitialized}; 
    la::unpack(λ.first.batch(0).middle_rows(branch * nx, nx), λ_last);
    la::gemv_add(solver_storages[branch].LB.batch(branch).transposed(), rs.batch(0),
                   λ_last.batch(0));
    // Reverse solve of the final block-tridiagonal system for each Cyqlone block
    solver_storages[branch].tridiagonal_solver.solve_reverse(λ_last);
    la::pack(λ_last, λ.branches[branch].batch(0));
    λ.first.batch(0).middle_rows(branch * nx, nx) = λ_last.batch(0);
};
//! [Cyqlone factorization and fused forward solve]
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
template <bool Factor, bool Solve>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve_impl(Context &ctx, value_type γ,
                                                                   real_t ρ_inv, FanStorage Σ,
                                                                   FanStorage ux, FanStorage λ) {
    index_t c = ctx.total_ctx.index;
    if constexpr (Factor&&Solve) 
        solver_storages[c].cyqlone_solver.factor_solve(ctx.branch_ctx, γ, ρ_inv, Σ.branches[c], ux.branches[c], λ.branches[c]);
    else if constexpr (Factor)
        solver_storages[c].cyqlone_solver.factor(ctx.branch_ctx, γ, ρ_inv, Σ.branches[c]);
    else if constexpr (Solve)
        solver_storages[c].cyqlone_solver.solve_forward(ctx.branch_ctx, ux.branches[c], λ.branches[c]);
    // ctx.arrive_and_wait(); // wait for off-diagonal block
    if (ctx.branch_ctx.is_master()) {
        factor_solve_λ0<Factor, Solve>(c, λ);
        ctx.total_ctx.run_single_sync([&, this] { factor_solve_u0<Factor, Solve>(ux); });
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve(Context &ctx, value_type γ,
                                                              real_t ρ_inv, FanStorage Σ,
                                                              FanStorage ux, FanStorage λ) {
    factor_solve_impl<true, true>(ctx, γ, ρ_inv, Σ, ux, λ);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor(Context &ctx, value_type γ, real_t ρ_inv,
                                                        FanStorage Σ) {
    factor_solve_impl<true, false>(ctx, γ, ρ_inv, Σ, {}, {});
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_forward(Context &ctx, FanStorage ux,
                                                               FanStorage λ) {
    factor_solve_impl<false, true>(ctx, 0, 0, {}, ux, λ);
}

// Algorithm 5 “Solution of a symmetric block-tridiagonal system using cyclic reduction (CR)”
// §3.2 Cyclic reduction of block-tridiagonal linear systems
//
// The reverse solve routines below closely follow the structure of the corresponding factorization
// and forward solve routines, but in reverse order. An iterative approach is used instead of
// recursion. Note that the evaluation of λ(0) is performed during the forward solve step.
// Depending on the problem size, either a parallel or serial version of the CR solve is used.

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse(
    Context &ctx, FanStorage ux, FanStorage λ) {
    const index_t c = ctx.total_ctx.index;
    if (ctx.branch_ctx.is_master()) {
        ctx.total_ctx.run_single_sync([&] { solve_reverse_u0(ux); });

        solve_reverse_λ0(c, λ);
    }
    solver_storages[c].cyqlone_solver.solve_reverse(ctx.branch_ctx, ux.branches[c],
                                                    λ.branches[c]);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse_mul(Context &ctx, FanStorage ux,
                                                                FanStorage λ, FanStorage Mᵀλ) {
    const index_t c = ctx.total_ctx.index;
    if (ctx.branch_ctx.is_master()) {
        ctx.total_ctx.run_single_sync([&] { solve_reverse_u0(ux); });

        solve_reverse_λ0(c, λ);
    }
    solver_storages[c].cyqlone_solver.solve_reverse_mul(ctx.branch_ctx, ux.branches[c],
                                                    λ.branches[c], Mᵀλ.branches[c]);}

//![Cyqlone solve CR serial]

} // namespace CYQLONE_NS(cyqlone)
