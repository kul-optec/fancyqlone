#include <cyqlone/fan-cyqlone.hpp>
#include <cyqlone/linalg.hpp>

#include <batmat/assume.hpp>
#include <batmat/linalg/simdify.hpp>
#include <guanaqo/blas/hl-blas-interface.hpp>
#include <limits>
#if !BATMAT_WITH_OPENMP
#include <batmat/thread-pool.hpp>
#endif

namespace CYQLONE_NS(cyqlone) {

using batmat::linalg::simdify;

namespace detail {
/// Simple (inefficient) matrix copy that supports slices with non-unit strides.
template <class T1, class I1, class S1, guanaqo::StorageOrder O1, class T2, class I2, class S2,
          guanaqo::StorageOrder O2>
void copy(guanaqo::MatrixView<T1, I1, S1, O1> src, guanaqo::MatrixView<T2, I2, S2, O2> dst) {
    assert(src.rows == dst.rows);
    assert(src.cols == dst.cols);
    for (index_t r = 0; r < src.rows; ++r) // TODO: optimize
        for (index_t c = 0; c < src.cols; ++c)
            dst(r, c) = src(r, c);
}
template <class T0, class T1, class I1, class S1, guanaqo::StorageOrder O1, class T2, class I2,
          class S2, guanaqo::StorageOrder O2>
/// Simple (inefficient) scaled matrix copy that supports slices with non-unit strides.
void scale(T0 scalar, guanaqo::MatrixView<T1, I1, S1, O1> src,
           guanaqo::MatrixView<T2, I2, S2, O2> dst) {
    assert(src.rows == dst.rows);
    assert(src.cols == dst.cols);
    for (index_t r = 0; r < src.rows; ++r) // TODO: optimize
        for (index_t c = 0; c < src.cols; ++c)
            dst(r, c) = scalar * src(r, c);
}
} // namespace detail

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
FanCyqloneSolver<VL, T, DefaultOrder, Ctx>
FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::build(const FanCyqloneStorage<value_type> &ocp,
                                                  std::vector<index_t> p,
                                                  CyqloneParams<value_type> params) {
    BATMAT_ASSERT(!p.empty());
    for (index_t p_fan : p)
        BATMAT_ASSERT(v == 1 || is_pow_2(p_fan));
    FanCyqloneSolver<VL, T, DefaultOrder, Ctx> res{
        .num_branches = ocp.num_branches,
        .nu           = ocp.nu,
        .ny_0         = ocp.ny_0,
    };
    res.update_data(ocp, p);
    res.update_params(params);
    return res;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_data(
    const FanCyqloneStorage<value_type> &ocp, const std::vector<index_t> &p) {
    using cyqlone::detail::copy;
    using cyqlone::detail::scale;
    namespace la = cyqlone::linalg;
    solver_storages.clear();
    solver_storages.reserve(num_branches);

    for (index_t c = 0; c < num_branches; ++c) {
        const auto &branch_ocp = ocp.branches[c];
        auto solver_storage    = SolverStorage<VL, value_type, DefaultOrder>{
            .cyqlone_solver =
                CyqloneSolver<VL, value_type, DefaultOrder, Ctx>::build(branch_ocp, p[c]),
            .tridiagonal_solver =
                TridiagonalSolver<value_type, DefaultOrder>{.block_size = branch_ocp.nx,
                                                            .num_blocks = v},
            .B0 = ocp.Bs[0],
        };
        solver_storages[c] = std::move(solver_storage);
        if (c == 0) {
            la::copy(ocp.R0, SBs(0));
            la::negate(ocp.r0, rs(0));
        }
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_rhs(
    const FanCyqloneStorage<value_type> &ocp, mut_view<> rhs) const {
    BATMAT_ASSERT(rhs.size() == num_branches);

    for (index_t c = 0; c < num_branches; ++c) {
        BATMAT_ASSERT(rhs[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(rhs[c].rows() == nu);
        BATMAT_ASSERT(rhs[c].cols() == 1);
        solver_storages[c].cyqlone_solver.initialize_rhs(ocp.branches[c], rhs[c]);
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_gradient(
    const FanCyqloneStorage<value_type> &ocp, mut_view<> grad) const {
    BATMAT_ASSERT(grad.size() == num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        BATMAT_ASSERT(grad[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(grad[c].rows() == nu + solver_storages[c].cyqlone_solver.nx);
        BATMAT_ASSERT(grad[c].cols() == 1);
        solver_storages[c].cyqlone_solver.initialize_gradient(ocp.branches[c], grad[c]);
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_bounds(
    const FanCyqloneStorage<value_type> &ocp, mut_view<> b_min, mut_view<> b_max) const {
    BATMAT_ASSERT(b_min.size() == num_branches);
    BATMAT_ASSERT(b_max.size() == num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        const index_t nyM = std::max(solver_storages[c].cyqlone_solver.ny,
                                     ny_0 + solver_storages[c].cyqlone_solver.ny_N);
        BATMAT_ASSERT(b_min[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(b_min[c].rows() == nyM);
        BATMAT_ASSERT(b_min[c].cols() == 1);
        BATMAT_ASSERT(b_max[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(b_max[c].rows() == nyM);
        BATMAT_ASSERT(b_max[c].cols() == 1);
        solver_storages[c].cyqlone_solver.initialize_bounds(ocp.branches[c], b_min[c], b_max[c]);
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_variables(std::span<const value_type> ux_lin,
                                                                mut_view<> ux) const {

    BATMAT_ASSERT(ux.size() == num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        BATMAT_ASSERT(ux[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(ux[c].rows() == nu + solver_storages[c].cyqlone_solver.nx);
        BATMAT_ASSERT(ux[c].cols() == 1);
        solver_storages[c].cyqlone_solver.pack_variables(ux[c]);
    }
}
///@todo implment for Fan cyqlone think about how to store ux_lin for fan cyqlone
// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_variables(
//     view<> ux, std::span<value_type> ux_lin) const {
//     const index_t nux = nu + nx;
//     BATMAT_ASSERT(static_cast<index_t>(ux_lin.size()) == nux * N_horiz);
//     BATMAT_ASSERT(ux.depth() == ceil_N());
//     BATMAT_ASSERT(ux.rows() == nux);
//     BATMAT_ASSERT(ux.cols() == 1);
//     for (index_t c = 0; c < p; ++c) {
//         const index_t di0 = c * n;
//         for (index_t i = 0; i < n; ++i) {
//             index_t di = di0 + i;
//             for (index_t vi = 0; vi < v; ++vi) {
//                 auto j      = stage_index(c, i, vi);
//                 using rview = guanaqo::MatrixView<value_type, index_t>;
//                 if (j == 0) {
//                     rview::as_column(ux_lin.first(nu)) = ux.batch(di)(vi).top_rows(nu);
//                     if (ceil_N() == N_horiz)
//                         rview::as_column(ux_lin.subspan(nu + (N_horiz - 1) * nux, nx)) =
//                             ux.batch(di)(vi).bottom_rows(nx);
//                 } else if (j < N_horiz) {
//                     rview::as_column(ux_lin.subspan(j * nux, nu)) = ux.batch(di)(vi).top_rows(nu);
//                     rview::as_column(ux_lin.subspan(nu + (j - 1) * nux, nx)) =
//                         ux.batch(di)(vi).bottom_rows(nx);
//                 } else if (j == N_horiz) {
//                     // only unpack the last state if we have padding stages
//                     rview::as_column(ux_lin.subspan(nu + (N_horiz - 1) * nux, nx)) =
//                         ux.batch(di)(vi).bottom_rows(nx);
//                 }
//             }
//         }
//     }
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_dynamics(std::span<const value_type> λ_lin,
//                                                                mut_view<> λ) const {
//     const index_t nλ = nx;
//     BATMAT_ASSERT(static_cast<index_t>(λ_lin.size()) == nλ * N_horiz);
//     BATMAT_ASSERT(λ.depth() == ceil_N());
//     BATMAT_ASSERT(λ.rows() == nλ);
//     BATMAT_ASSERT(λ.cols() == 1);
//     for (index_t c = 0; c < p; ++c) {
//         const index_t di0 = c * n;
//         for (index_t i = 0; i < n; ++i) {
//             index_t di = di0 + i;
//             for (index_t vi = 0; vi < v; ++vi) {
//                 auto j       = stage_index(c, i, vi);
//                 using crview = guanaqo::MatrixView<const value_type, index_t>;
//                 if (j < N_horiz) {
//                     λ.batch(di)(vi) = crview::as_column(λ_lin.subspan(j * nλ, nλ));
//                 } else {
//                     λ.batch(di)(vi).set_constant(0);
//                 }
//             }
//         }
//     }
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_dynamics(
//     view<> λ, std::span<value_type> λ_lin) const {
//     const index_t nλ = nx;
//     BATMAT_ASSERT(static_cast<index_t>(λ_lin.size()) == nλ * N_horiz);
//     BATMAT_ASSERT(λ.depth() == ceil_N());
//     BATMAT_ASSERT(λ.rows() == nλ);
//     BATMAT_ASSERT(λ.cols() == 1);
//     for (index_t c = 0; c < p; ++c) {
//         const index_t di0 = c * n;
//         for (index_t i = 0; i < n; ++i) {
//             index_t di = di0 + i;
//             for (index_t vi = 0; vi < v; ++vi) {
//                 auto j      = stage_index(c, i, vi);
//                 using rview = guanaqo::MatrixView<value_type, index_t>;
//                 if (j < N_horiz) {
//                     rview::as_column(λ_lin.subspan(j * nλ, nλ)) = λ.batch(di)(vi);
//                 }
//             }
//         }
//     }
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_constraints(std::span<const value_type> y_lin,
//                                                                   mut_view<> y,
//                                                                   value_type fill) const {
//     BATMAT_ASSERT(static_cast<index_t>(y_lin.size()) == ny * (N_horiz - 1) + ny_0 + ny_N);
//     BATMAT_ASSERT(y.depth() == ceil_N());
//     BATMAT_ASSERT(y.rows() == std::max(ny, ny_0 + ny_N));
//     BATMAT_ASSERT(y.cols() == 1);
//     for (index_t c = 0; c < p; ++c) {
//         const index_t di0 = c * n;
//         for (index_t i = 0; i < n; ++i) {
//             index_t di = di0 + i;
//             for (index_t vi = 0; vi < v; ++vi) {
//                 auto j       = stage_index(c, i, vi);
//                 using crview = guanaqo::MatrixView<const value_type, index_t>;
//                 if (j == 0) {
//                     index_t ny_pad                 = std::max(ny, ny_0 + ny_N) - (ny_0 + ny_N);
//                     y.batch(di)(vi).top_rows(ny_0) = crview::as_column(y_lin.first(ny_0));
//                     y.batch(di)(vi).bottom_rows(ny_N) =
//                         crview::as_column(y_lin.subspan(ny_0 + (N_horiz - 1) * ny, ny_N));
//                     y.batch(di)(vi).bottom_rows(ny_pad).set_constant(fill);
//                 } else if (j < N_horiz) {
//                     index_t ny_pad = std::max(ny, ny_0 + ny_N) - ny;
//                     y.batch(di)(vi).top_rows(ny) =
//                         crview::as_column(y_lin.subspan(ny_0 + (j - 1) * ny, ny));
//                     y.batch(di)(vi).bottom_rows(ny_pad).set_constant(fill);
//                 } else {
//                     y.batch(di)(vi).set_constant(0);
//                 }
//             }
//         }
//     }
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_constraints(
//     view<> y, std::span<value_type> y_lin) const {
//     BATMAT_ASSERT(static_cast<index_t>(y_lin.size()) == ny * (N_horiz - 1) + ny_0 + ny_N);
//     BATMAT_ASSERT(y.depth() == ceil_N());
//     BATMAT_ASSERT(y.rows() == std::max(ny, ny_0 + ny_N));
//     BATMAT_ASSERT(y.cols() == 1);
//     for (index_t c = 0; c < p; ++c) {
//         const index_t di0 = c * n;
//         for (index_t i = 0; i < n; ++i) {
//             index_t di = di0 + i;
//             for (index_t vi = 0; vi < v; ++vi) {
//                 auto j      = stage_index(c, i, vi);
//                 using rview = guanaqo::MatrixView<value_type, index_t>;
//                 if (j == 0) {
//                     rview::as_column(y_lin.first(ny_0)) = y.batch(di)(vi).top_rows(ny_0);
//                     rview::as_column(y_lin.subspan(ny_0 + (N_horiz - 1) * ny, ny_N)) =
//                         y.batch(di)(vi).bottom_rows(ny_N);
//                 } else if (j < N_horiz) {
//                     rview::as_column(y_lin.subspan(ny_0 + (j - 1) * ny, ny)) =
//                         y.batch(di)(vi).top_rows(ny);
//                 }
//             }
//         }
//     }
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_rhs(
//     const FanCyqloneStorage<value_type> &ocp) const -> matrix<> {
//     matrix<> rhs = initialize_dynamics_constraints();
//     initialize_rhs(ocp, rhs);
//     return rhs;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_gradient(
//     const FanCyqloneStorage<value_type> &ocp) const -> matrix<> {
//     matrix<> grad = initialize_variables();
//     initialize_gradient(ocp, grad);
//     return grad;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_bounds(
//     const FanCyqloneStorage<value_type> &ocp) const -> std::pair<matrix<>, matrix<>> {
//     std::pair b{initialize_general_constraints(), initialize_general_constraints()};
//     initialize_bounds(ocp, b.first, b.second);
//     return b;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_variables(
//     std::span<const value_type> ux_lin) const -> matrix<> {
//     matrix<> ux = initialize_variables();
//     pack_variables(ux_lin, ux);
//     return ux;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_variables(view<> ux) const
//     -> std::vector<value_type> {
//     std::vector<value_type> ux_lin(num_variables());
//     unpack_variables(ux, ux_lin);
//     return ux_lin;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_dynamics(
//     std::span<const value_type> λ_lin) const -> matrix<> {
//     matrix<> λ = initialize_dynamics_constraints();
//     pack_dynamics(λ_lin, λ);
//     return λ;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_dynamics(view<> λ) const
//     -> std::vector<value_type> {
//     std::vector<value_type> λ_lin(num_dynamics_constraints());
//     unpack_dynamics(λ, λ_lin);
//     return λ_lin;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_constraints(std::span<const value_type> y_lin,
//                                                                   value_type fill) const
//     -> matrix<> {
//     matrix<> y = initialize_general_constraints();
//     pack_constraints(y_lin, y, fill);
//     return y;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_constraints(view<> y) const
//     -> std::vector<value_type> {
//     std::vector<value_type> y_lin(num_general_constraints());
//     unpack_constraints(y, y_lin);
//     return y_lin;
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_variables() const -> matrix<> {
//     return matrix<>{{.depth = ceil_N(), .rows = nu + nx, .cols = 1}};
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_dynamics_constraints() const
//     -> matrix<> {
//     return matrix<>{{.depth = ceil_N(), .rows = nx, .cols = 1}};
// }

// template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
// auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_general_constraints() const
//     -> matrix<> {
//     return matrix<>{{.depth = ceil_N(), .rows = std::max(ny, ny_0 + ny_N), .cols = 1}};
// }

} // namespace CYQLONE_NS(cyqlone)
