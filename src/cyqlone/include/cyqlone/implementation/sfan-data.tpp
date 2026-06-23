#include <cyqlone/serial-fan-cyqlone.hpp>
#include <cyqlone/linalg.hpp>
#include "cyqlone/cyqlone.hpp"

#include <batmat/assume.hpp>
#include <batmat/linalg/copy.hpp>
#include <batmat/linalg/simdify.hpp>
#include <batmat/linalg/structure.hpp>
#include <guanaqo/blas/hl-blas-interface.hpp>
#include <algorithm>
#include <iostream>
#include <limits>
#include <span>
#include <vector>
#if !BATMAT_WITH_OPENMP
#include <batmat/thread-pool.hpp>
#endif

namespace CYQLONE_NS(cyqlone) {

using batmat::linalg::simdify;
namespace la = cyqlone::linalg;
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
SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>
SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::build(const FanCyqloneStorage<value_type> &ocp,
                                                  index_t p,
                                                  CyqloneParams<value_type> params) {
    BATMAT_ASSERT(p > 0);
    SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx> res{
        .num_branches = ocp.num_branches,
        .nu           = ocp.nu,
        .ny_0         = ocp.ny_0,
        .solver_storages = {}, // initialized in update_data
        .p          = p,

    };
    res.update_data(ocp);
    res.update_params(params);
    return res;
}


template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_data(
    const FanCyqloneStorage<value_type> &ocp) {
    using cyqlone::detail::copy;
    using cyqlone::detail::scale;
    namespace la = cyqlone::linalg;
    solver_storages.clear();
    solver_storages.reserve(num_branches);

    for (index_t c = 0; c < num_branches; ++c) {
        const auto &branch_ocp = ocp.branches[c];
        SolverLast tridiagonal_solver{.block_size = branch_ocp.nx, .num_blocks = v};
        auto solver_storage    = SolverStorage<VL, value_type, DefaultOrder>{
            .cyqlone_solver =
                CyqloneSolver<VL, value_type, DefaultOrder>::build(branch_ocp, p),
            .tridiagonal_solver = tridiagonal_solver,
    
        };
        la::copy(ocp.Bs[c], solver_storage.B0);
        // la::copy(ocp.LBs[c], solver_storage.LB);
        solver_storages.emplace_back(std::move(solver_storage));
        
        /// @todo Check correctness
        if (c == 0) {
            la::copy(ocp.R0(0), R0(0));
            la::negate(ocp.r0(0), r0(0));
            la::copy(ocp.D0(0), D0(0));
        }
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_rhs(
    const FanCyqloneStorage<value_type> &ocp, FanStorage &rhs) const {
    BATMAT_ASSERT(static_cast<index_t>(rhs.branches.size()) == num_branches);
    index_t nx_offset=0;
    for (index_t c = 0; c < num_branches; ++c) {
        BATMAT_ASSERT(rhs.branches[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(rhs.branches[c].rows() == solver_storages[c].cyqlone_solver.nx);
        BATMAT_ASSERT(rhs.branches[c].cols() == 1);
        solver_storages[c].cyqlone_solver.initialize_rhs(ocp.branches[c], rhs.branches[c]);
        rhs.first.batch(0).middle_rows(nx_offset, solver_storages[c].cyqlone_solver.nx)(0) = rhs.branches[c].batch(0)(0);
        nx_offset += solver_storages[c].cyqlone_solver.nx;
    };
    // std::cout << "FANRHS initialized: " << std::endl;
    // print_grad(rhs,"fan_rhs");

}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_gradient(
    const FanCyqloneStorage<value_type> &ocp, FanStorage &grad) const {
    namespace la = cyqlone::linalg;

    BATMAT_ASSERT(static_cast<index_t>(grad.branches.size()) == num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        BATMAT_ASSERT(grad.branches[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(grad.branches[c].rows() == nu + solver_storages[c].cyqlone_solver.nx);
        BATMAT_ASSERT(grad.branches[c].cols() == 1);
        solver_storages[c].cyqlone_solver.initialize_gradient(ocp.branches[c], grad.branches[c]);
    }
    la::copy(ocp.r0(0), grad.first.top_rows(nu)(0));
}
// or whatever element-copy utility batmat/guanaqo exposes}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_bounds(
    const FanCyqloneStorage<value_type> &ocp, FanStorage &b_min, FanStorage &b_max) const {
    BATMAT_ASSERT(static_cast<index_t>(b_min.branches.size()) == num_branches);
    BATMAT_ASSERT(static_cast<index_t>(b_max.branches.size()) == num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        const index_t nyM = std::max(solver_storages[c].cyqlone_solver.ny,
                                      solver_storages[c].cyqlone_solver.ny_N);
        BATMAT_ASSERT(b_min.branches[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(b_min.branches[c].rows() == nyM);
        BATMAT_ASSERT(b_min.branches[c].cols() == 1);
        BATMAT_ASSERT(b_max.branches[c].depth() == solver_storages[c].cyqlone_solver.ceil_N());
        BATMAT_ASSERT(b_max.branches[c].rows() == nyM);
        BATMAT_ASSERT(b_max.branches[c].cols() == 1);
        solver_storages[c].cyqlone_solver.initialize_bounds(ocp.branches[c], b_min.branches[c], b_max.branches[c]);
    }
    
    la::copy(ocp.b_min_0(0), b_min.first.batch(0));
    la::copy(ocp.b_max_0(0), b_max.first.batch(0));
    // std::cout << "Bounds initialized: " << std::endl;
    // print_grad(b_min,"b_min");
    // print_grad(b_max,"b_max");
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_variables(std::span<const value_type> ux_lin,
                                                                FanStorage &ux) const {
    index_t offset = 0; //put u0_sol
    // copy the rest of the variables from ux_lin into each branch but leave out the dummy u0
    for (index_t c = 0; c < num_branches; ++c) {
        index_t nux    = nu + solver_storages[c].cyqlone_solver.nx;
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();

        BATMAT_ASSERT(ux.branches[c].depth() == ceil_N);
        BATMAT_ASSERT(ux.branches[c].rows() == nux);
        BATMAT_ASSERT(ux.branches[c].cols() == 1);
        // std::span<const value_type> ux_lin_c = copy(ux_lin.subspan(offset - nu, nux * ceil_N));

        // std::fill(ux_lin_c.first(nu).begin(), ux_lin_c.first(nu).end(), value_type{0});

        solver_storages[c].cyqlone_solver.pack_variables(ux_lin.subspan(offset, nux * N_horiz), ux.branches[c]);
        offset += nux * N_horiz;
    }
    using crview                        = guanaqo::MatrixView<const value_type, index_t>;
    la::copy(crview::as_column(ux_lin.first(nu)), ux.first.batch(0)); // copy u0_sol into the first element of ux_lin
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_variables(
    const FanStorage &ux, std::span<value_type> ux_lin) const {
    BATMAT_ASSERT(static_cast<index_t>(ux.branches.size()) == num_branches);

    index_t offset = static_cast<index_t>(ux_lin.size()); //put u0_sol at the end of ux_lin

    // Copy u0_sol into ux_lin
    using rview                        = guanaqo::MatrixView<value_type, index_t>;

    // copy the rest of the variables from each branch into ux_lin but leave out the dummy u0
    for (index_t c = num_branches - 1; c >= 0; --c) {
        index_t nux    = nu + solver_storages[c].cyqlone_solver.nx;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;

        BATMAT_ASSERT(ux.branches[c].depth() == ceil_N);
        BATMAT_ASSERT(ux.branches[c].rows() == nux);
        BATMAT_ASSERT(ux.branches[c].cols() == 1);
        solver_storages[c].cyqlone_solver.unpack_variables(ux.branches[c], ux_lin.subspan(offset-nux * N_horiz, nux * N_horiz));
        offset -= nux * N_horiz-nu;
    }
    la::copy(ux.first.batch(0).top_rows(nu), rview::as_column(ux_lin.first(nu))); // copy u0_sol from the first element of ux into the first nu elements of ux_lin
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_dynamics(std::span<const value_type> λ_lin,
                                                               FanStorage &λ) const {
    BATMAT_ASSERT(static_cast<index_t>(λ.branches.size()) == num_branches);
    index_t offset = 0;
    for (index_t c = 0; c < num_branches; ++c) {
        index_t nλ     = solver_storages[c].cyqlone_solver.nx;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;

        BATMAT_ASSERT(λ.branches[c].depth() == ceil_N);
        BATMAT_ASSERT(λ.branches[c].rows() == nλ);
        BATMAT_ASSERT(λ.branches[c].cols() == 1);
        using crview                                 = guanaqo::MatrixView<const value_type, index_t>;
        la::copy(crview::as_column(λ_lin.subspan(offset, nλ)), λ.first.batch(0).middle_rows(c * nλ,  nλ)); // copy the first nλ elements of λ_lin into the first element of λ
        solver_storages[c].cyqlone_solver.pack_dynamics(λ_lin.subspan(offset, nλ * N_horiz), λ.branches[c]);
        offset += nλ * N_horiz;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_dynamics(
    const FanStorage &λ, std::span<value_type> λ_lin) const {
    BATMAT_ASSERT(static_cast<index_t>(λ.branches.size()) == num_branches);
    index_t offset = 0;
    for (index_t c = 0; c < num_branches; ++c) {
        index_t nλ     = solver_storages[c].cyqlone_solver.nx;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;
        BATMAT_ASSERT(λ.branches[c].depth() == ceil_N);
        BATMAT_ASSERT(λ.branches[c].rows() == nλ);
        BATMAT_ASSERT(λ.branches[c].cols() == 1);
        solver_storages[c].cyqlone_solver.unpack_dynamics(λ.branches[c], λ_lin.subspan(offset, nλ * N_horiz));
        using rview                                 = guanaqo::MatrixView< value_type, index_t>;
        la::copy(λ.first.batch(0).middle_rows(c * nλ,  nλ), rview::as_column(λ_lin.subspan(offset, nλ)));
        offset += nλ * N_horiz;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_constraints(std::span<const value_type> y_lin,
                                                                  FanStorage &y,
                                                                  value_type fill) const {
   
    BATMAT_ASSERT(static_cast<index_t>(y.branches.size()) == num_branches);
    index_t offset = ny_0;
    using crview    = guanaqo::MatrixView<const value_type, index_t>;
    la::copy(crview::as_column(y_lin.first(ny_0)), y.first.batch(0)(0).top_rows(nu));
    for (index_t c = 0; c < num_branches; ++c) {
        index_t ny     = solver_storages[c].cyqlone_solver.ny;
        index_t ny_N   = solver_storages[c].cyqlone_solver.ny_N;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        index_t nyM    = std::max(ny, ny_N);
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;
        BATMAT_ASSERT(y.branches[c].depth() == ceil_N);
        BATMAT_ASSERT(y.branches[c].rows() == nyM);
        BATMAT_ASSERT(y.branches[c].cols() == 1);
        solver_storages[c].cyqlone_solver.pack_constraints(y_lin.subspan(offset, ny * (N_horiz-1) + ny_N), y.branches[c], fill);
        offset += ny * (N_horiz-1) + ny_N;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_constraints(
    const FanStorage &y, std::span<value_type> y_lin) const {
    BATMAT_ASSERT(static_cast<index_t>(y.branches.size()) == num_branches);
    index_t offset = ny_0;
    using rview    = guanaqo::MatrixView<value_type, index_t>;
    la::copy(y.first.batch(0)(0).top_rows(ny_0), rview::as_column(y_lin.first(ny_0)));
    for (index_t c = 0; c < num_branches; ++c) {
        index_t ny     = solver_storages[c].cyqlone_solver.ny;
        index_t ny_N   = solver_storages[c].cyqlone_solver.ny_N;
        index_t ceil_N = solver_storages[c].cyqlone_solver.ceil_N();
        index_t nyM    = std::max(ny, ny_N);
        index_t N_horiz = solver_storages[c].cyqlone_solver.N_horiz;
        BATMAT_ASSERT(y.branches[c].depth() == ceil_N);
        BATMAT_ASSERT(y.branches[c].rows() == nyM);
        BATMAT_ASSERT(y.branches[c].cols() == 1);
        solver_storages[c].cyqlone_solver.unpack_constraints(y.branches[c], y_lin.subspan(offset, ny * (N_horiz-1) + ny_N));
        offset += ny * (N_horiz-1) + ny_N;
    }
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_rhs(
    const FanCyqloneStorage<value_type> &ocp) const -> FanStorage {
    FanStorage rhs = initialize_dynamics_constraints();
    initialize_rhs(ocp, rhs);
    return rhs;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_gradient(
    const FanCyqloneStorage<value_type> &ocp) const -> FanStorage {
    FanStorage grad = initialize_variables();
    initialize_gradient(ocp, grad);
    return grad;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_bounds(
    const FanCyqloneStorage<value_type> &ocp) const -> std::pair<FanStorage, FanStorage> {
    
    std::pair<FanStorage, FanStorage> b{initialize_general_constraints(), initialize_general_constraints()};
    initialize_bounds(ocp, b.first, b.second);

    return b;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_variables(
    std::span< const value_type> ux_lin) const -> FanStorage {
    FanStorage ux = initialize_variables();
    pack_variables(ux_lin, ux);
    return ux;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_variables(const FanStorage &ux) const
    -> std::vector<value_type> {
    std::vector<value_type> ux_lin(num_variables());
    unpack_variables(ux, ux_lin);
    return ux_lin;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_dynamics(
    std::span< const value_type> λ_lin) const -> FanStorage {
    FanStorage λ = initialize_dynamics_constraints();
    pack_dynamics(λ_lin, λ);
    return λ;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_dynamics(const FanStorage &λ) const
    -> std::vector<value_type> {
    std::vector<value_type> λ_lin(num_dynamics_constraints());
    unpack_dynamics(λ, λ_lin);
    return λ_lin;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::pack_constraints(std::span< const value_type> y_lin,
                                                                  value_type fill) const
    -> FanStorage {
    FanStorage y = initialize_general_constraints();
    pack_constraints(y_lin, y, fill);
    return y;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::unpack_constraints(const FanStorage &y) const
    -> std::vector<value_type> {
    std::vector<value_type> y_lin(num_general_constraints());
    unpack_constraints(y, y_lin);
    return y_lin;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_variables() const -> FanStorage {
    auto variables = FanStorage();
    variables.branches.resize(num_branches);
    index_t nx_tot = 0;

    for (index_t c = 0; c < num_branches; ++c) {
        variables.branches[c]=solver_storages[c].cyqlone_solver.initialize_variables();
        nx_tot += solver_storages[c].cyqlone_solver.nx;
    }
    typename SolverLast::matrix f{{.rows = nu+nx_tot, .cols = 1}}; // initialize the first element of variables to hold u0_sol
    variables.first = f;
    return variables;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_dynamics_constraints() const
    -> FanStorage {
    auto dynamics_constraints = FanStorage();
    dynamics_constraints.branches.resize(num_branches);
    index_t nx_tot = 0;
    for (index_t c = 0; c < num_branches; ++c) {
        dynamics_constraints.branches[c]=solver_storages[c].cyqlone_solver.initialize_dynamics_constraints();
        nx_tot += solver_storages[c].cyqlone_solver.nx;
    }
    typename SolverLast::matrix f{{.rows = nx_tot, .cols = 1}}; // initialize the first element of dynamics_constraints to hold r0
    dynamics_constraints.first = f;
    return dynamics_constraints;
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::initialize_general_constraints() const
    -> FanStorage {
    auto general_constraints = FanStorage();
    general_constraints.branches.resize(num_branches);
    for (index_t c = 0; c < num_branches; ++c) {
        general_constraints.branches[c]=solver_storages[c].cyqlone_solver.initialize_general_constraints();
    }

    typename SolverLast::matrix f{{.rows = ny_0, .cols = 1}}; // initialize the first element of general_constraints to hold r0
    general_constraints.first = f;
    return general_constraints;
}

} // namespace CYQLONE_NS(cyqlone)
