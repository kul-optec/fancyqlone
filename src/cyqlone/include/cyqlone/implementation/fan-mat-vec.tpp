#include <cyqlone/cyqlone.hpp>
#include <cyqlone/fan-cyqlone.hpp>

#include <cyqlone/linalg.hpp>

#include <batmat/assume.hpp>
#include <batmat/linalg/copy.hpp>
#include <batmat/linalg/gemv.hpp>
#include <batmat/linalg/simdify.hpp>
#include <batmat/linalg/symv.hpp>
#include <batmat/linalg/uview.hpp>
#include <batmat/loop.hpp>
#include <iostream>

namespace CYQLONE_NS(cyqlone) {

namespace la = cyqlone::linalg;
using namespace batmat::linalg;

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::residual_dynamics_constr(Context &ctx,
                                                                          const FanStorage &x,
                                                                          const FanStorage &b,
                                                                          FanStorage &Mxb) const {
    // (Mx + b)(i,j) = A(i,j) x(i,j) + B(i,j) u(i,j) - x(i,j+1) + b(i,j)

    const index_t c = ctx.total_ctx.index;
    // ctx.arrive_and_wait(); // wait for x to be ready from the forward solve of the first level
    solver_storages[c].cyqlone_solver.residual_dynamics_constr(ctx.branch_ctx, x.branches[c],
                                                               b.branches[c], Mxb.branches[c]);
    // ctx.arrive_and_wait(); // wait for x to be ready from the forward solve of the first level

    std::osyncstream out(std::cout);
    ctx.branch_ctx.arrive_and_wait();

    if (ctx.branch_ctx.is_master()) {

        index_t nx_offset = 0;
        for (index_t i = 0; i < c; ++i)
            nx_offset += solver_storages[i].cyqlone_solver.nx;
        auto bc = b.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx);
        typename SolverLast::matrix Mxb_row{
            {.rows = solver_storages[c].cyqlone_solver.nx, .cols = 1}};
        auto indices = solver_storages[c].cyqlone_solver.inverse_stage_index(1);
        Mxb_row.batch(0)(0) =
            x.branches[c]
                .batch(indices.c * solver_storages[c].cyqlone_solver.n + indices.i)(indices.l)
                .bottom_rows(solver_storages[c].cyqlone_solver.nx);
        gemv_add(solver_storages[c].B0.batch(0), x.first.batch(0).top_rows(nu), bc,
                 Mxb.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx));
        sub(Mxb.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx),
            Mxb_row.batch(0));
        Mxb.branches[c].batch(0)(0) =
            Mxb.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx)(0);
    }
    ctx.arrive_and_wait();
    // print_grad(ctx, b,"res_b");
    // print_grad(ctx, x,"x");
    // print_grad(ctx, Mxb,"Mxb");

}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::transposed_dynamics_constr(Context &ctx,
                                                                            const FanStorage &λ,
                                                                            FanStorage &Mᵀλ,
                                                                            bool accum) const {
    // (Mᵀλ)(i,j) = [ B(i,j)ᵀ ] λ(j) - [ 0 ] λ(i,j-1)
    //            [ A(i,j)ᵀ ]        [ I ]

    const index_t c = ctx.total_ctx.index;
    // index_t nx_offset = 0; //
    // if (ctx.branch_ctx.is_master()) {
    //     for (index_t i = 0; i < c; ++i)
    //         nx_offset += solver_storages[i].cyqlone_solver.nx;
    //     auto indices = solver_storages[c].cyqlone_solver.inverse_stage_index(0);
    //     // decltype(λ.first.batch(0)) Mᵀλ_row =
    //     //     Mᵀλ.first;
    //     // Mᵀλ_row.batch(0)(0)= ;
    //     // λ.branches[c].batch(indices.c * solver_storages[c].cyqlone_solver.n +
    //     //                     indices.i)(indices.l) =
    //     //     λ.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx)(0);
    // }
    solver_storages[c].cyqlone_solver.transposed_dynamics_constr(ctx.branch_ctx, λ.branches[c],
                                                                 Mᵀλ.branches[c], accum);
    if (ctx.branch_ctx.is_master()) {
        index_t nx_offset = 0; //
        for (index_t i = 0; i < c; ++i)
            nx_offset += solver_storages[i].cyqlone_solver.nx;
        typename SolverLast::matrix Mᵀλ_row{{.rows = nu, .cols = 1}};
        la::gemv(solver_storages[c].B0.batch(0).transposed(),
                 λ.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx),
                 Mᵀλ_row.batch(0));
        auto reduced = ctx.total_ctx.reduce(std::move(Mᵀλ_row.batch(0)), [](auto a, auto b) {
            la::add(a.batch(0), b.batch(0));
            return a;
        });
        if (ctx.is_master()) {
            Mᵀλ.first.batch(0).top_rows(nu) = reduced;
        }
        ctx.total_ctx.arrive_and_wait();
    }
    ctx.arrive_and_wait();

}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::general_constr(Context &ctx, const FanStorage &ux,
                                                                FanStorage &DCux) const {
    const auto mul_Gx = [](auto Gᵀj, auto uxj, auto DCuxj) { gemv(Gᵀj.transposed(), uxj, DCuxj); };
    const index_t c   = ctx.total_ctx.index;
    solver_storages[c].cyqlone_solver.general_constr(ctx.branch_ctx, ux.branches[c],
                                                     DCux.branches[c]);
    if (ctx.is_master())
        mul_Gx(D0(0).transposed(), ux.first.batch(0).top_rows(nu), DCux.first.batch(0));
    ctx.arrive_and_wait();
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::transposed_general_constr(Context &ctx,
                                                                           const FanStorage &y,
                                                                           FanStorage &DCᵀy) const {
    const auto mul_Gᵀy = [](auto Gᵀj, auto yj, auto DCᵀyj) { gemv(Gᵀj, yj, DCᵀyj); };
    const index_t c    = ctx.total_ctx.index;
    solver_storages[c].cyqlone_solver.transposed_general_constr(ctx.branch_ctx, y.branches[c],
                                                                DCᵀy.branches[c]);
    if (ctx.is_master())
        mul_Gᵀy(D0(0).transposed(), y.first.batch(0), DCᵀy.first.batch(0).top_rows(nu));
    ctx.arrive_and_wait();
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::cost_gradient(Context &ctx, const FanStorage &ux,
                                                               value_type α, const FanStorage &q,
                                                               value_type β,
                                                               FanStorage &grad_f) const {
    const auto mul_Hx = [&](auto qj, auto Hj, auto uxj, auto grad_fj) {
        // GUANAQO_TRACE("cost_gradient", j);
        if (α != 0 || β != 1)
            axpby(α, qj, β, grad_fj);
        symv_add(tril(Hj), uxj, grad_fj);
    };
    const index_t c = ctx.total_ctx.index;
    solver_storages[c].cyqlone_solver.cost_gradient(ctx.branch_ctx, ux.branches[c], α,
                                                    q.branches[c], β, grad_f.branches[c]);
    if (ctx.is_master())
        mul_Hx(q.first.batch(0).top_rows(nu), R0.batch(0), ux.first.batch(0).top_rows(nu),
               grad_f.first.batch(0).top_rows(nu));

    ctx.arrive_and_wait();
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::cost_gradient_regularized(
    Context &ctx, value_type γ, const FanStorage &ux, const FanStorage &ux0, const FanStorage &q,
    FanStorage &grad_f) const {
    auto inv_γ{1 / γ};
    const auto reg_simd = [inv_γ](auto qji, auto xji, auto x0ji) {
        return inv_γ * (xji - x0ji) + qji;
    };
    const auto mul_Hx = [&](auto qj, auto Hj, auto uxj, auto ux0j, auto grad_fj) {
        linalg::transform_elementwise(reg_simd, grad_fj, qj, uxj, ux0j);
        symv_add(tril(Hj), uxj, grad_fj);
    };
    const index_t c = ctx.total_ctx.index;
    solver_storages[c].cyqlone_solver.cost_gradient_regularized(
        ctx.branch_ctx, γ, ux.branches[c], ux0.branches[c], q.branches[c], grad_f.branches[c]);
    if (ctx.is_master())
        mul_Hx(q.first.batch(0).top_rows(nu), R0.batch(0), ux.first.batch(0).top_rows(nu),
               ux0.first.batch(0).top_rows(nu), grad_f.first.batch(0).top_rows(nu));
    ctx.arrive_and_wait();
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::cost_gradient_remove_regularization(
    Context &ctx, value_type γ, const FanStorage &ux, const FanStorage &ux0,
    FanStorage &grad_f) const {
    auto inv_γ{1 / γ};
    const auto sub_reg_simd = [inv_γ](auto grad_fji, auto xji, auto x0ji) {
        return grad_fji + inv_γ * (x0ji - xji);
    };
    const auto sub_reg = [&]([[maybe_unused]] auto uxj, auto ux0j, auto grad_fj) {
        linalg::transform_elementwise(sub_reg_simd, grad_fj, grad_fj, uxj, ux0j);
    };
    foreach_batch(ctx, sub_reg, ux, ux0, grad_f);
}

} // namespace CYQLONE_NS(cyqlone)
