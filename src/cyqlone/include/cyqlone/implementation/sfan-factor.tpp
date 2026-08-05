#include <cyqlone/cyqlone.hpp>
#include <cyqlone/serial-fan-cyqlone.hpp>
#include <cyqlone/linalg.hpp>
#include <cyqlone/packing.hpp>
#include <batmat/linalg/gemm-diag.hpp>
#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/triangular.hpp>
#include <batmat/lut.hpp>
#include <batmat/openmp.h>
#include <guanaqo/print.hpp>
#include <iostream>
#include <syncstream>

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
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve_λ0(index_t branch, FanStorage &λ,
                                                                 const FanStorage &ux,
                                                                 const FanStorage &Σ) {
    GUANAQO_TRACE_REGION("fan solve λ0", 0);
    if constexpr (Factor) {
        // Factor the final block-tridiagonal Schur complement of each Cyqlone block
        la::unpack(tril(solver_storages[branch].cyqlone_solver.tricyqle.cr_L.batch(0)),
                   tril(solver_storages[branch].tridiagonal_solver.L));
        la::unpack(solver_storages[branch].cyqlone_solver.tricyqle.cr_Y.batch(0),
                   solver_storages[branch].tridiagonal_solver.U.transposed());
        solver_storages[branch].tridiagonal_solver.factor();
        // Compute the contribution to the final Schur complement (system involving only u(0))
        la::trsm(solver_storages[branch].B0.transposed(),
                 tril(solver_storages[branch].tridiagonal_solver.L.batch(0)).transposed(),
                 solver_storages[branch].LB);
        if (branch == 0) {
            auto temp = solver_storages[branch].temp;
            la::syrk_diag_add(D0.batch(0).transposed(), tril(R0.batch(0)), tril(temp.batch(0)),
                              batmat::linalg::simdify(Σ.first.batch(0)));

            // la::copy(R0.batch(0), temp.batch(0));
            la::syrk_add(solver_storages[branch].LB, tril(temp.batch(0)), tril(SBs.batch(branch)));
        } else {
            la::syrk(solver_storages[branch].LB, tril(SBs.batch(branch)));
        }
    }
    std::osyncstream out(std::cout);
    if constexpr (Solve) {
        index_t nx  = solver_storages[branch].cyqlone_solver.nx;
        auto λ_last = solver_storages[branch].λ_last;
        // Forward solve of the final block-tridiagonal system, to get λ(0) for each Cyqlone block
        // guanaqo::print_python(out << branch <<"[fanout]   λ(0) = ",λ.branches[branch].batch(0)(0), "\n");

        la::unpack(λ.branches[branch].batch(0), λ_last);
        // guanaqo::print_python(out << branch << "[fanout]   λ(0) = ", λ_last.batch(0)(0), "\n");

        solver_storages[branch].tridiagonal_solver.solve_forward(λ_last);
        // guanaqo::print_python(out << branch << "[fanout]   λ(0) = ", λ_last.batch(0)(0), "\n");

        branch == 0 ? la::gemv_sub(solver_storages[branch].LB, λ_last.batch(0),
                                   ux.first.batch(0).top_rows(nu), rs.batch(branch))
                    : la::gemv_neg(solver_storages[branch].LB, λ_last.batch(0), rs.batch(branch));
        // if (branch == 0) {
        //     r0.set_constant(0); //todo dirty fix rs
        // }
        la::pack(λ_last, λ.branches[branch].batch(0));

        la::copy(λ_last.batch(0), λ.first.batch(0).middle_rows(branch * nx, nx));
    }
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
template <bool Factor, bool Solve>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve_u0(FanStorage &ux, value_type γ) {
    GUANAQO_TRACE_REGION("fan solve u0", 0);
    if constexpr (Factor) {
        for (index_t b = 1; b < num_branches; ++b)
            la::add(SBs.batch(0), SBs.batch(b));
        la::potrf(tril(SBs.batch(0)), 1 / γ);
        // guanaqo::print_python(std::cout << "[fanout factor]   SBs(0) = ", SBs.batch(0)(0), "\n");

    }
    if constexpr (Solve) {

        for (index_t b = 1; b < num_branches; ++b) {
            la::add(rs.batch(0), rs.batch(b));
        }
        // guanaqo::print_python(out << "[forward]   rs(0) = ", rs.batch(0)(0), "\n");

        la::trsm(tril(SBs.batch(0)), rs.batch(0), ux.first.batch(0).top_rows(nu));

        // rs.batch(0)(0) = ux.first.batch(0).top_rows(nu)(0);
    }
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse_u0(FanStorage &ux) const {
    GUANAQO_TRACE_REGION("fan reverse solve u0", 0);
    la::trsm(tril(SBs.batch(0)).transposed(),
             ux.first.batch(0).top_rows(nu)); // ux.first now contains u(0)
    // rs.batch(0)(0) = ux.first.batch(0).top_rows(nu)(0);
}
// Reverse solve for λ(0) on each branch, after solving for u(0)
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse_λ0(index_t branch, FanStorage &ux,
                                                                  FanStorage &λ) const {
    GUANAQO_TRACE_REGION("fan solve reverse λ0", 0);
    // Compute the contribution of u(0) to λ(0) for each Cyqlone block
    index_t nx  = solver_storages[branch].cyqlone_solver.nx;
    auto λ_last = solver_storages[branch].λ_last;
    la::unpack(λ.branches[branch].batch(0), λ_last);
    la::gemv_add(solver_storages[branch].LB.batch(0).transposed(), ux.first.batch(0).top_rows(nu),
                 λ_last.batch(0));
    // Reverse solve of the final block-tridiagonal system for each Cyqlone block
    solver_storages[branch].tridiagonal_solver.solve_reverse(λ_last);
    la::pack(λ_last, λ.branches[branch].batch(0));
    la::copy(λ_last.batch(0), λ.first.batch(0).middle_rows(branch * nx, nx));
};
//! [Cyqlone factorization and fused forward solve]
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
template <bool Factor, bool Solve>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve_impl(Context &ctx, value_type γ,
                                                                   real_t ρ_inv,
                                                                   const FanStorage &Σ,
                                                                   FanStorage &ux, FanStorage &λ) {
    // print_grad(ctx, Σ, "Σ");

    if constexpr (Factor && Solve) {
        for (index_t b = 0; b < num_branches; ++b) {
            solver_storages[b].cyqlone_solver.factor_solve(ctx, γ, ρ_inv, Σ.branches[b],
                                                           ux.branches[b], λ.branches[b]);
        }
    } else if constexpr (Factor) {
        for (index_t b = 0; b < num_branches; ++b) {
            solver_storages[b].cyqlone_solver.factor(ctx, γ, ρ_inv, Σ.branches[b]);
        }
    } else if constexpr (Solve) {
        for (index_t b = 0; b < num_branches; ++b) {
            solver_storages[b].cyqlone_solver.solve_forward(ctx, ux.branches[b], λ.branches[b]);
        }
    }
    ctx.arrive_and_wait(); // wait for λ(0) to be ready on each branch
    if (ctx.is_master()) {
        for (index_t b = 0; b < num_branches; ++b) {
            factor_solve_λ0<Factor, Solve>(b, λ, ux, Σ);
        }
        factor_solve_u0<Factor, Solve>(ux, γ);
    }
    ctx.arrive_and_wait(); // wait for λ(0) to be ready on each branch

    // print_grad(ctx, Σ, "Σ");
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor_solve(Context &ctx, value_type γ,
                                                                    real_t ρ_inv, const FanStorage &Σ,
                                                                    FanStorage &ux, FanStorage &λ) {
    factor_solve_impl<true, true>(ctx, γ, ρ_inv, Σ, ux, λ);
    // std::osyncstream tout(std::cout);
    // guanaqo::print_python(tout << "[forward]   λ(0) = ", λ.first.batch(0)(0), "\n");
    // guanaqo::print_python(tout << "[forward]   u(0) = ", ux.first.batch(0)(0), "\n");
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::factor(Context &ctx, value_type γ, real_t ρ_inv,
                                                        const FanStorage &Σ) {
    FanStorage ux, λ;
    factor_solve_impl<true, false>(ctx, γ, ρ_inv, Σ, ux, λ);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_forward(Context &ctx, FanStorage &ux,
                                                                      FanStorage &λ) {
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
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse(Context &ctx, FanStorage &ux,
                                                                      FanStorage &λ) {
    GUANAQO_TRACE_REGION("fan solve reverse", 0);

    if (ctx.is_master()) {
        solve_reverse_u0(ux);
        for (index_t b = 0; b < num_branches; ++b) {
            solve_reverse_λ0(b, ux, λ);
        }
    }
    ctx.arrive_and_wait(); // wait λ()(0) to be ready
    for (index_t b = 0; b < num_branches; ++b) {
        solver_storages[b].cyqlone_solver.solve_reverse(ctx, ux.branches[b], λ.branches[b]);
    }
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::solve_reverse_mul(Context &ctx, FanStorage &ux,
                                                                   FanStorage &λ, FanStorage &Mᵀλ) {
    if (ctx.is_master()) {
        solve_reverse_u0(ux);
        for (index_t b = 0; b < num_branches; ++b) {
            solve_reverse_λ0(b, ux, λ);
        }
    }
    ctx.arrive_and_wait(); // wait λ()(0) to be ready
    for (index_t b = 0; b < num_branches; ++b) {
        solver_storages[b].cyqlone_solver.solve_reverse_mul(ctx, ux.branches[b], λ.branches[b],
                                                            Mᵀλ.branches[b]);
    }
    if (ctx.is_master()) {
        index_t nx_offset = 0; //
        for (index_t b = 0; b < num_branches; ++b) {
            if (b == 0) {
                la::gemv(solver_storages[b].B0.batch(0).transposed(),
                        λ.first.batch(0).middle_rows(nx_offset, solver_storages[b].cyqlone_solver.nx),
                        Mᵀλ.first.batch(0).top_rows(nu));}
            else {
                la::gemv_add(solver_storages[b].B0.batch(0).transposed(),
                        λ.first.batch(0).middle_rows(nx_offset, solver_storages[b].cyqlone_solver.nx),
                        Mᵀλ.first.batch(0).top_rows(nu));}
            nx_offset += solver_storages[b].cyqlone_solver.nx;


        }
    }
}

//![Cyqlone solve CR serial]

} // namespace CYQLONE_NS(cyqlone)
