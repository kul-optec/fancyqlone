#include <cyqlone/fan-cyqlone.hpp>
#include <cyqlone/linalg.hpp>

#include <batmat/assume.hpp>
#include <batmat/linalg/simdify.hpp>
#include <guanaqo/blas/hl-blas-interface.hpp>
#include <algorithm>
#include <limits>
#include <span>
#include <vector>
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
    index_t offset = nu; //put u0_sol
    using rview    = guanaqo::MatrixView<value_type, index_t>;
    u0_sol         = rview::as_column(ux_lin.first(nu));
    // copy the rest of the variables from ux_lin into each branch but leave out the dummy u0
    for (index_t c = 0; c < num_branches; ++c) {
        index_t nux    = nu + solver_storages[c].cyqlone_solver.nx;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();

        BATMAT_ASSERT(ux[c].depth() == ceil_N);
        BATMAT_ASSERT(ux[c].rows() == nux);
        BATMAT_ASSERT(ux[c].cols() == 1);
        std::span<const value_type> ux_lin_c = copy(ux_lin.subspan(offset - nu, nux * ceil_N));

        std::fill(ux_lin_c.first(nu).begin(), ux_lin_c.first(nu).end(), value_type{0});

        solver_storages[c].cyqlone_solver.pack_variables(ux_lin_c, ux[c]);
    }
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_variables(
    view<> ux, std::span<value_type> ux_lin) const {
    BATMAT_ASSERT(ux.size() == num_branches);

    index_t offset = nu;

    // Copy u0_sol into ux_lin
    using rview                        = guanaqo::MatrixView<value_type, index_t>;
    rview::as_column(ux_lin.first(nu)) = u0_sol;

    // copy the rest of the variables from each branch into ux_lin but leave out the dummy u0
    for (index_t c = 0; c < num_branches; ++c) {
        index_t nux    = nu + solver_storages[c].cyqlone_solver.nx;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();

        BATMAT_ASSERT(ux[c].depth() == ceil_N);
        BATMAT_ASSERT(ux[c].rows() == nux);
        BATMAT_ASSERT(ux[c].cols() == 1);

        std::vector<value_type> buffer(nux * ceil_N);
        std::span<value_type> ux_lin_c(buffer);

        solver_storages[c].cyqlone_solver.unpack_variables(ux[c], ux_lin_c);

        auto src = ux_lin_c.subspan(nu);
        auto dst = ux_lin.subspan(offset, src.size());

        std::copy(src.begin(), src.end(), dst.begin());
        offset += src.size();
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_dynamics(std::span<const value_type> λ_lin,
                                                               mut_view<> λ) const {
    BATMAT_ASSERT(λ.size() == num_branches);
    index_t offset = 0;
    for (index_t c = 0; c < num_branches; ++c) {
        index_t nλ     = solver_storages[c].cyqlone_solver.nx;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        BATMAT_ASSERT(λ[c].depth() == ceil_N);
        BATMAT_ASSERT(λ[c].rows() == nλ);
        BATMAT_ASSERT(λ[c].cols() == 1);
        using rview                                 = guanaqo::MatrixView<value_type, index_t>;
        λ0_sol.middle_columns(c * nλ, (c + 1) * nλ) = rview::as_row(λ_lin.first(nλ));
        std::span<const value_type> λ_lin_c         = copy(λ_lin.subspan(offset, nλ * ceil_N));
        solver_storages[c].cyqlone_solver.pack_dynamics(λ_lin_c, λ[c]);
        offset += nλ * ceil_N;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_dynamics(
    view<> λ, std::span<value_type> λ_lin) const {
    BATMAT_ASSERT(λ.size() == num_branches);
    index_t offset = 0;
    for (index_t c = 0; c < num_branches; ++c) {
        index_t nλ     = solver_storages[c].cyqlone_solver.nx;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        BATMAT_ASSERT(λ[c].depth() == ceil_N);
        BATMAT_ASSERT(λ[c].rows() == nλ);
        BATMAT_ASSERT(λ[c].cols() == 1);
        using rview                                 = guanaqo::MatrixView<value_type, index_t>;
        rview::as_row(λ_lin.first(nλ)) = rview::as_row(λ[c].middle_columns(0, nλ));
        std::span<const value_type> λ_lin_c = copy(λ_lin.subspan(offset, nλ * ceil_N));
        solver_storages[c].cyqlone_solver.unpack_dynamics(λ[c], λ_lin_c);
        offset += nλ * ceil_N;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_constraints(std::span<const value_type> y_lin,
                                                                  mut_view<> y,
                                                                  value_type fill) const {
   
    BATMAT_ASSERT(y.size() == num_branches);
    index_t offset = ny_0;
    using rview    = guanaqo::MatrixView<value_type, index_t>;
    y0 = rview::as_column(y_lin.first(ny_0));
    for (index_t c = 0; c < num_branches; ++c) {
        index_t ny     = solver_storages[c].cyqlone_solver.ny;
        index_t ny_N   = solver_storages[c].cyqlone_solver.ny_N;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        index_t nyM    = std::max(ny, ny_N);
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;
        BATMAT_ASSERT(y[c].depth() == ceil_N);
        BATMAT_ASSERT(y[c].rows() == nyM);
        BATMAT_ASSERT(y[c].cols() == 1);
        std::span<const value_type> y_lin_c = copy(y_lin.subspan(offset, ny * (N_horiz-1) + ny_N));
        solver_storages[c].cyqlone_solver.pack_constraints(y_lin_c, y[c], fill);
        offset += ny * (N_horiz-1) + ny_N;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_constraints(
    view<> y, std::span<value_type> y_lin) const {
    BATMAT_ASSERT(y.size() == num_branches);
    index_t offset = ny_0;
    using rview    = guanaqo::MatrixView<value_type, index_t>;
    rview::as_column(y_lin.first(ny_0)) = y0;
    for (index_t c = 0; c < num_branches; ++c) {
        index_t ny     = solver_storages[c].cyqlone_solver.ny;
        index_t ny_N   = solver_storages[c].cyqlone_solver.ny_N;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        index_t nyM    = std::max(ny, ny_N);
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;
        BATMAT_ASSERT(y[c].depth() == ceil_N);
        BATMAT_ASSERT(y[c].rows() == nyM);
        BATMAT_ASSERT(y[c].cols() == 1);
        std::span<const value_type> y_lin_c = copy(y_lin.subspan(offset, ny * (N_horiz-1) + ny_N));
        solver_storages[c].cyqlone_solver.unpack_constraints(y[c], y_lin_c);
        offset += ny * (N_horiz-1) + ny_N;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_rhs(
    const FanCyqloneStorage<value_type> &ocp) const -> std::vector<matrix<>> {
    std::vector<matrix<>> rhs = initialize_dynamics_constraints();
    initialize_rhs(ocp, rhs);
    return rhs;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_gradient(
    const FanCyqloneStorage<value_type> &ocp) const -> std::vector<matrix<>> {
    std::vector<matrix<>> grad = initialize_variables();
    initialize_gradient(ocp, grad);
    return grad;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_bounds(
    const FanCyqloneStorage<value_type> &ocp) const -> std::pair<std::vector<matrix<>>, std::vector<matrix<>>> {
    std::pair<std::vector<matrix<>>, std::vector<matrix<>>> bounds(num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        bounds[c] = {initialize_general_constraints(), initialize_general_constraints()};
        initialize_bounds(ocp, bounds[c].first, bounds[c].second);
    }
    return bounds;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_variables(
    std::span<const value_type> ux_lin) const -> std::vector<matrix<>> {
    std::vector<matrix<>> ux = initialize_variables();
    pack_variables(ux_lin, ux);
    return ux;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_variables(view<> ux) const
    -> std::vector<value_type> {
    std::vector<value_type> ux_lin(num_variables());
    unpack_variables(ux, ux_lin);
    return ux_lin;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_dynamics(
    std::span<const value_type> λ_lin) const -> std::vector<matrix<>> {
    std::vector<matrix<>> λ = initialize_dynamics_constraints();
    pack_dynamics(λ_lin, λ);
    return λ;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_dynamics(view<> λ) const
    -> std::vector<value_type> {
    std::vector<value_type> λ_lin(num_dynamics_constraints());
    unpack_dynamics(λ, λ_lin);
    return λ_lin;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_constraints(std::span<const value_type> y_lin,
                                                                  value_type fill) const
    -> std::vector<matrix<>> {
    std::vector<matrix<>> y = initialize_general_constraints();
    pack_constraints(y_lin, y, fill);
    return y;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_constraints(view<> y) const
    -> std::vector<value_type> {
    std::vector<value_type> y_lin(num_general_constraints());
    unpack_constraints(y, y_lin);
    return y_lin;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_variables() const -> std::vector<matrix<>> {
    auto variables = std::vector<matrix<>>();
    variables.reserve(num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        variables[c]=solver_storages[c].cyqlone_solver.initialize_variables();
    }
    return variables;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_dynamics_constraints() const
    -> std::vector<matrix<>> {
    auto dynamics_constraints = std::vector<matrix<>>();
    dynamics_constraints.reserve(num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        dynamics_constraints[c]=solver_storages[c].cyqlone_solver.initialize_dynamics_constraints();
    }
    return dynamics_constraints;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_general_constraints() const
    -> std::vector<matrix<>> {
    auto general_constraints = std::vector<matrix<>>();
    general_constraints.reserve(num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        general_constraints[c]=solver_storages[c].cyqlone_solver.initialize_general_constraints();
    }
    return general_constraints;
}

} // namespace CYQLONE_NS(cyqlone)
