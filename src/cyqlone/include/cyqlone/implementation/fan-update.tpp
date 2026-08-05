// #include <cyqlone/cyqlone.hpp>
// #include <cyqlone/fan-cyqlone.hpp>

// #include <cyqlone/linalg.hpp>
// #include <cyqlone/packing.hpp>
// #include <batmat/assume.hpp>
// #include <batmat/linalg/copy.hpp>
// #include <batmat/linalg/gemm.hpp>
// #include <batmat/linalg/gemv.hpp>
// #include <batmat/linalg/potrf.hpp>
// #include <batmat/linalg/simdify.hpp>
// #include <batmat/linalg/symv.hpp>
// #include <batmat/linalg/uview.hpp>
// #include <batmat/loop.hpp>
// #include <fstream>
// #include <iostream>
// namespace CYQLONE_NS(cyqlone) {
// namespace la = cyqlone::linalg;

// using la::tril;

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// template <bool Solve>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve_λ0(index_t branch, FanStorage &λ,
//                                                                  const FanStorage &ux) {
//     GUANAQO_TRACE_REGION("fan solve λ0", 0);
//     // Factor the final block-tridiagonal Schur complement of each Cyqlone block
//     la::unpack(tril(solver_storages[branch].cyqlone_solver.tricyqle.cr_L.batch(0)),
//                tril(solver_storages[branch].tridiagonal_solver.L));
//     // guanaqo::print_python(std::cout << branch << "[fanout]   L = ", solver_storages[branch].tridiagonal_solver.L.batch(0)(0), "\n");

//     la::unpack(solver_storages[branch].cyqlone_solver.tricyqle.cr_Y.batch(0),
//                solver_storages[branch].tridiagonal_solver.U.transposed());
//     // for (index_t i = 0; i <= solver_storages[branch].tridiagonal_solver.num_blocks - 1; ++i) {
//     //     guanaqo::print_python(std::cout << branch << "[fanout]   U(" << i << ") = ", solver_storages[branch].tridiagonal_solver.U.batch(i)(0), "\n");
//     //     guanaqo::print_python(std::cout << branch << "[fanout]   L(" << i << ") = ", solver_storages[branch].tridiagonal_solver.L.batch(i)(0), "\n");

//     // }
//     solver_storages[branch].tridiagonal_solver.factor();
//     // for (index_t i = 0; i <= solver_storages[branch].tridiagonal_solver.num_blocks - 1; ++i) {
//     //     guanaqo::print_python(std::cout << branch << "[fanout]   L(" << i << ") = ", solver_storages[branch].tridiagonal_solver.L.batch(i)(0), "\n");

//     // }
//     la::syrk(solver_storages[branch].LB,tril(ΔSBs.batch(branch)));
//     // Compute the contribution to the final Schur complement (system involving only u(0))
//     la::trsm(solver_storages[branch].B0.transposed(),
//              tril(solver_storages[branch].tridiagonal_solver.L.batch(0)).transposed(),
//              solver_storages[branch].LB);
//     // if (branch == 0) {
//     //     auto temp = solver_storages[branch].temp;
//     //     la::syrk_diag_add(D0.batch(0).transposed(), tril(R0.batch(0)), tril(temp.batch(0)),
//     //                       batmat::linalg::simdify(Σ.first.batch(0)));

//     //     // la::copy(R0.batch(0), temp.batch(0));
//     //     la::syrk_add(solver_storages[branch].LB, tril(temp.batch(0)), tril(SBs.batch(branch)));
//     // } else {
//     la::syrk_sub(solver_storages[branch].LB, tril(ΔSBs.batch(branch)));

//     // }
//     if constexpr (Solve) {
//         index_t nx  = solver_storages[branch].cyqlone_solver.nx;
//         auto λ_last = solver_storages[branch].λ_last;
//         // Forward solve of the final block-tridiagonal system, to get λ(0) for each Cyqlone block
//         // guanaqo::print_python(out << branch <<"[fanout]   λ(0) = ",λ.branches[branch].batch(0)(0), "\n");

//         la::unpack(λ.branches[branch].batch(0), λ_last);
//         // guanaqo::print_python(out << branch << "[fanout]   λ(0) = ", λ_last.batch(0)(0), "\n");

//         solver_storages[branch].tridiagonal_solver.solve_forward(λ_last);
//         // guanaqo::print_python(out << branch << "[fanout]   λ(0) = ", λ_last.batch(0)(0), "\n");

//         branch == 0 ? la::gemv_sub(solver_storages[branch].LB, λ_last.batch(0),
//                                    ux.first.batch(0).top_rows(nu), rs.batch(branch))
//                     : la::gemv_neg(solver_storages[branch].LB, λ_last.batch(0), rs.batch(branch));
//         // if (branch == 0) {
//         //     r0.set_constant(0); //todo dirty fix rs
//         // }
//         la::pack(λ_last, λ.branches[branch].batch(0));

//         la::copy(λ_last.batch(0), λ.first.batch(0).middle_rows(branch * nx, nx));
//     }
// }
// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// template <bool Solve>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve_u0(FanStorage &ux,
//                                                                  const FanStorage &ΔΣ) {
//     GUANAQO_TRACE_REGION("fan solve u0", 0);
//     la::syrk(tril(SBs.batch(0)));
//     for (index_t b = 0; b < num_branches; ++b) {
//             la::add(SBs.batch(0), ΔSBs.batch(b));
//     }
//     // guanaqo::print_python(std::cout << "[fanout update]   SBs(0) = ", SBs.batch(0)(0), "\n");

//     la::syrk_diag_add_potrf(D0.batch(0).transposed(), tril(SBs.batch(0)),
//                             batmat::linalg::simdify(ΔΣ.first.batch(0)));
//     // guanaqo::print_python(std::cout << "[fanout update]   SBs(0) = ", SBs.batch(0)(0), "\n");
//     if constexpr (Solve) {

//         for (index_t b = 1; b < num_branches; ++b) {
//             la::add(rs.batch(0), rs.batch(b));
//         }
//         // guanaqo::print_python(out << "[forward]   rs(0) = ", rs.batch(0)(0), "\n");

//         la::trsm(tril(SBs.batch(0)), rs.batch(0), ux.first.batch(0).top_rows(nu));

//         // rs.batch(0)(0) = ux.first.batch(0).top_rows(nu)(0);
//     }
// }
// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve(Context &ctx, const FanStorage &ΔΣ,
//                                                               FanStorage &ux, FanStorage &λ) {
//     index_t c = ctx.total_ctx.index;
//     solver_storages[c].cyqlone_solver.update_solve(ctx.branch_ctx, ΔΣ.branches[c], ux.branches[c],
//                                                    λ.branches[c]);
//     // Update the first stage of the fan problem
//     ctx.branch_ctx.arrive_and_wait(); // wait for the branch to be ready
//     if (ctx.branch_ctx.is_master()) {
//         update_solve_λ0<true>(c, λ, ux);
//         ctx.total_ctx.run_single_sync([&, this] { update_solve_u0<true>(ux, ΔΣ); });
//     }
//     ctx.branch_ctx.arrive_and_wait(); // wait for λ(0) to be ready on each branch
// }
// } // namespace CYQLONE_NS(cyqlone)
#include <cyqlone/cyqlone.hpp>
#include <cyqlone/fan-cyqlone.hpp>

#include <cyqlone/linalg.hpp>
#include <cyqlone/packing.hpp>
#include <batmat/assume.hpp>
#include <batmat/linalg/copy.hpp>
#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/gemv.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/simdify.hpp>
#include <batmat/linalg/symv.hpp>
#include <batmat/linalg/uview.hpp>
#include <batmat/loop.hpp>
#include <fstream>
#include <iostream>
namespace CYQLONE_NS(cyqlone) {
namespace la = cyqlone::linalg;

using la::tril;

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
template <bool Solve>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve_λ0(index_t branch, FanStorage &λ,
                                                                 const FanStorage &ux) {
    GUANAQO_TRACE_REGION("fan solve λ0", 0);
    // Factor the final block-tridiagonal Schur complement of each Cyqlone block
    la::unpack(tril(solver_storages[branch].cyqlone_solver.tricyqle.cr_L.batch(0)),
               tril(solver_storages[branch].tridiagonal_solver.L));
    // guanaqo::print_python(std::cout << branch << "[fanout]   L = ", solver_storages[branch].tridiagonal_solver.L.batch(0)(0), "\n");

    la::unpack(solver_storages[branch].cyqlone_solver.tricyqle.cr_Y.batch(0),
               solver_storages[branch].tridiagonal_solver.U.transposed());
    // for (index_t i = 0; i <= solver_storages[branch].tridiagonal_solver.num_blocks - 1; ++i) {
    //     guanaqo::print_python(std::cout << branch << "[fanout]   U(" << i << ") = ", solver_storages[branch].tridiagonal_solver.U.batch(i)(0), "\n");
    //     guanaqo::print_python(std::cout << branch << "[fanout]   L(" << i << ") = ", solver_storages[branch].tridiagonal_solver.L.batch(i)(0), "\n");

    // }
    solver_storages[branch].tridiagonal_solver.factor();
    // for (index_t i = 0; i <= solver_storages[branch].tridiagonal_solver.num_blocks - 1; ++i) {
    //     guanaqo::print_python(std::cout << branch << "[fanout]   L(" << i << ") = ", solver_storages[branch].tridiagonal_solver.L.batch(i)(0), "\n");

    // }
    la::syrk(solver_storages[branch].LB,tril(ΔSBs.batch(branch)));
    // Compute the contribution to the final Schur complement (system involving only u(0))
    la::trsm(solver_storages[branch].B0.transposed(),
             tril(solver_storages[branch].tridiagonal_solver.L.batch(0)).transposed(),
             solver_storages[branch].LB);
    // if (branch == 0) {
    //     auto temp = solver_storages[branch].temp;
    //     la::syrk_diag_add(D0.batch(0).transposed(), tril(R0.batch(0)), tril(temp.batch(0)),
    //                       batmat::linalg::simdify(Σ.first.batch(0)));

    //     // la::copy(R0.batch(0), temp.batch(0));
    //     la::syrk_add(solver_storages[branch].LB, tril(temp.batch(0)), tril(SBs.batch(branch)));
    // } else {
    la::syrk_sub(solver_storages[branch].LB, tril(ΔSBs.batch(branch)));

    // }
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
template <bool Solve>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve_u0(FanStorage &ux,
                                                                 const FanStorage &ΔΣ) {
    GUANAQO_TRACE_REGION("fan solve u0", 0);
    la::syrk(tril(SBs.batch(0)));
    for (index_t b = 0; b < num_branches; ++b) {
            la::add(SBs.batch(0), ΔSBs.batch(b));
    }
    // guanaqo::print_python(std::cout << "[fanout update]   SBs(0) = ", SBs.batch(0)(0), "\n");

    la::syrk_diag_add_potrf(D0.batch(0).transposed(), tril(SBs.batch(0)),
                            batmat::linalg::simdify(ΔΣ.first.batch(0)));
    // guanaqo::print_python(std::cout << "[fanout update]   SBs(0) = ", SBs.batch(0)(0), "\n");
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
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve(Context &ctx, const FanStorage &ΔΣ,
                                                              FanStorage &ux, FanStorage &λ) {
    index_t c = ctx.total_ctx.index;
    solver_storages[c].cyqlone_solver.update_solve(ctx.branch_ctx, ΔΣ.branches[c], ux.branches[c],
                                                   λ.branches[c]);
    // Update the first stage of the fan problem
    ctx.branch_ctx.arrive_and_wait(); // wait for the branch to be ready
    if (ctx.branch_ctx.is_master()) {
        update_solve_λ0<true>(c, λ, ux);
        ctx.total_ctx.run_single_sync([&, this] { update_solve_u0<true>(ux, ΔΣ); });
    }
    ctx.branch_ctx.arrive_and_wait(); // wait for λ(0) to be ready on each branch
}
} // namespace CYQLONE_NS(cyqlone)