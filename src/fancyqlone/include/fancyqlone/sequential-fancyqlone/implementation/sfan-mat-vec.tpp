#include <fancyqlone/cyqlone/cyqlone.hpp>
#include <fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp>

#include <fancyqlone/linalg.hpp>

#include <batmat/assume.hpp>
#include <batmat/linalg/copy.hpp>
#include <batmat/linalg/gemv.hpp>
#include <batmat/linalg/simdify.hpp>
#include <batmat/linalg/symv.hpp>
#include <batmat/linalg/uview.hpp>
#include <batmat/loop.hpp>
#include <iostream>

namespace FANCYQLONE_NS(fancyqlone) {

namespace la = fancyqlone::linalg;
using namespace batmat::linalg;

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::residual_dynamics_constr(Context &ctx,
                                                                          const FanStorage &x,
                                                                          const FanStorage &b,
                                                                          FanStorage &Mxb) const {
    // (Mx + b)(i,j) = A(i,j) x(i,j) + B(i,j) u(i,j) - x(i,j+1) + b(i,j)

    for (index_t c = 0; c < num_branches; ++c) {
        solver_storages[c].cyqlone_solver.residual_dynamics_constr(ctx, x.branches[c],
                                                                   b.branches[c], Mxb.branches[c]);
    }

    ctx.arrive_and_wait(); // wait for branches to finish
    if (ctx.is_master()) {
        index_t nx_offset = 0;
        for(index_t c = 0; c < num_branches; ++c) {
            auto bc = b.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx);
            auto Mxb_row = solver_storages[c].Mxb_row;
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
            nx_offset += solver_storages[c].cyqlone_solver.nx;
    }}
    ctx.arrive_and_wait(); // wait for branches to finish

    // print_grad(ctx, b,"res_b");
    // print_grad(ctx, x,"x");
    // print_grad(ctx, Mxb,"Mxb");
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::transposed_dynamics_constr(Context &ctx,
                                                                            const FanStorage &λ,
                                                                            FanStorage &Mᵀλ,
                                                                            bool accum) const {
    // (Mᵀλ)(i,j) = [ B(i,j)ᵀ ] λ(j) - [ 0 ] λ(i,j-1)
    //            [ A(i,j)ᵀ ]        [ I ]

    for (index_t c = 0; c < num_branches; ++c) {
        solver_storages[c].cyqlone_solver.transposed_dynamics_constr(ctx, λ.branches[c],
                                                                     Mᵀλ.branches[c], accum);
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
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::general_constr(Context &ctx, const FanStorage &ux,
                                                                FanStorage &DCux) const {
    const auto mul_Gx = [](auto Gᵀj, auto uxj, auto DCuxj) { gemv(Gᵀj.transposed(), uxj, DCuxj); };
    for (index_t c = 0; c < num_branches; ++c) {
        solver_storages[c].cyqlone_solver.general_constr(ctx, ux.branches[c],
                                                     DCux.branches[c]);
    }
    if (ctx.is_master())
        mul_Gx(D0(0).transposed(), ux.first.batch(0).top_rows(nu), DCux.first.batch(0));
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::transposed_general_constr(Context &ctx,
                                                                                 const FanStorage &y,
                                                                                 FanStorage &DCᵀy) const {
    const auto mul_Gᵀy = [](auto Gᵀj, auto yj, auto DCᵀyj) { gemv(Gᵀj, yj, DCᵀyj); };
    for (index_t c = 0; c < num_branches; ++c) {
        solver_storages[c].cyqlone_solver.transposed_general_constr(ctx, y.branches[c],
                                                                DCᵀy.branches[c]);
    }
    if (ctx.is_master())
        mul_Gᵀy(D0(0).transposed(), y.first.batch(0), DCᵀy.first.batch(0).top_rows(nu));
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::cost_gradient(Context &ctx, const FanStorage &ux,
                                                               value_type α, const FanStorage &q,
                                                               value_type β,
                                                               FanStorage &grad_f) const {
    const auto mul_Hx = [&](auto qj, auto Hj, auto uxj, auto grad_fj) {
        // GUANAQO_TRACE("cost_gradient", j);
        if (α != 0 || β != 1)
            axpby(α, qj, β, grad_fj);
        symv_add(tril(Hj), uxj, grad_fj);
    };
    for (index_t c = 0; c < num_branches; ++c) {
        solver_storages[c].cyqlone_solver.cost_gradient(ctx, ux.branches[c], α,
                                                        q.branches[c], β, grad_f.branches[c]);
    }
    if (ctx.is_master())
        mul_Hx(q.first.batch(0).top_rows(nu), R0.batch(0), ux.first.batch(0).top_rows(nu),
               grad_f.first.batch(0).top_rows(nu));
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::cost_gradient_regularized(
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
    for (index_t c = 0; c < num_branches; ++c) {
        solver_storages[c].cyqlone_solver.cost_gradient_regularized(
            ctx, γ, ux.branches[c], ux0.branches[c], q.branches[c], grad_f.branches[c]);
    }
    if (ctx.is_master())
        mul_Hx(q.first.batch(0).top_rows(nu), R0.batch(0), ux.first.batch(0).top_rows(nu),
               ux0.first.batch(0).top_rows(nu), grad_f.first.batch(0).top_rows(nu));
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::cost_gradient_remove_regularization(
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

} // namespace FANCYQLONE_NS(fancyqlone)
