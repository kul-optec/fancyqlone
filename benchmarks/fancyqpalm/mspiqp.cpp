#include "mspiqp.hpp"
#include "root-elimination.hpp"

#include <batmat/assume.hpp>
#include <guanaqo/mat-view.hpp>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <limits>
#include <ranges>
#include <stdexcept>
#include <utility>
#include <vector>

using PIQPTriplet = Eigen::Triplet<real_t, int>;

namespace {

void validate_piqp_fan(const fancyqlone::FanOCPStorage &fan) {
    if (fan.ocps.empty())
        throw std::invalid_argument("FanOCPStorage must contain at least one branch");

    const auto &first = fan.ocps.front();

    if (first.dim.N_horiz <= 0)
        throw std::invalid_argument("FanOCPStorage horizon must be positive");

    for (const auto &ocp : fan.ocps) {
        if (ocp.dim.N_horiz != first.dim.N_horiz)
            throw std::invalid_argument("All branches must have the same horizon");

        if (ocp.dim.nx != first.dim.nx || ocp.dim.nu != first.dim.nu)
            throw std::invalid_argument("All branches must have equal nx and nu");
    }
}

template <class T, class I, class S, guanaqo::StorageOrder Order>
void add_block(std::vector<PIQPTriplet> &triplets, int row_offset, int column_offset,
               guanaqo::MatrixView<T, I, S, Order> matrix, real_t scale = real_t{1}) {
    for (I column = 0; column < matrix.cols; ++column) {
        for (I row = 0; row < matrix.rows; ++row) {
            const real_t value = scale * static_cast<real_t>(matrix(row, column));

            if (value != real_t{0}) {
                triplets.emplace_back(row_offset + static_cast<int>(row),
                                      column_offset + static_cast<int>(column), value);
            }
        }
    }
}

template <class T, class I, class S, guanaqo::StorageOrder Order>
void add_transposed_block(std::vector<PIQPTriplet> &triplets, int row_offset, int column_offset,
                          guanaqo::MatrixView<T, I, S, Order> matrix, real_t scale = real_t{1}) {
    for (I column = 0; column < matrix.cols; ++column) {
        for (I row = 0; row < matrix.rows; ++row) {
            const real_t value = scale * static_cast<real_t>(matrix(row, column));

            if (value != real_t{0}) {
                triplets.emplace_back(row_offset + static_cast<int>(column),
                                      column_offset + static_cast<int>(row), value);
            }
        }
    }
}

template <class T, class I, class S, guanaqo::StorageOrder Order>
void add_upper_triangular_block(std::vector<PIQPTriplet> &triplets, int offset,
                                guanaqo::MatrixView<T, I, S, Order> matrix,
                                real_t scale = real_t{1}) {
    BATMAT_ASSERT(matrix.rows == matrix.cols);

    for (I column = 0; column < matrix.cols; ++column) {
        for (I row = 0; row <= column; ++row) {
            const real_t value = scale * static_cast<real_t>(matrix(row, column));

            if (value != real_t{0}) {
                triplets.emplace_back(offset + static_cast<int>(row),
                                      offset + static_cast<int>(column), value);
            }
        }
    }
}

template <class T, class I, class S, guanaqo::StorageOrder Order>
void copy_vector(PIQPVector &destination, int offset, guanaqo::MatrixView<T, I, S, Order> source,
                 real_t scale = real_t{1}) {
    BATMAT_ASSERT(source.cols == 1);

    for (I row = 0; row < source.rows; ++row) {
        destination[offset + static_cast<int>(row)] = scale * static_cast<real_t>(source(row, 0));
    }
}

template <class T, class I, class S, guanaqo::StorageOrder Order>
void add_vector(PIQPVector &destination, int offset, guanaqo::MatrixView<T, I, S, Order> source,
                real_t scale = real_t{1}) {
    BATMAT_ASSERT(source.cols == 1);

    for (I row = 0; row < source.rows; ++row) {
        destination[offset + static_cast<int>(row)] += scale * static_cast<real_t>(source(row, 0));
    }
}

void add_identity_block(std::vector<PIQPTriplet> &triplets, int row_offset, int column_offset,
                        int size, real_t scale = real_t{1}) {
    for (int i = 0; i < size; ++i) {
        triplets.emplace_back(row_offset + i, column_offset + i, scale);
    }
}

void set_constraints(PIQPFanQPData &data, int node, int x, int u,
                     std::vector<PIQPTriplet> &triplets) {
    const auto &constraints = data.constraints[node];
    for (int i : constraints.state_indices) {
        data.z_lower[x + i] = constraints.xmin[i];
        data.z_upper[x + i] = constraints.xmax[i];
    }
    for (int i : constraints.input_indices) {
        data.z_lower[u + i] = constraints.umin[i];
        data.z_upper[u + i] = constraints.umax[i];
    }
    const int ng     = static_cast<int>(constraints.lower.size());
    const int offset = data.general_offsets[node];
    for (int row = 0; row < ng; ++row) {
        data.h_lower[offset + row] = constraints.lower[row];
        data.h_upper[offset + row] = constraints.upper[row];
        for (int col = 0; col < static_cast<int>(constraints.xmin.size()); ++col)
            if (const double value = constraints.C[row + col * ng]; value != 0)
                triplets.emplace_back(offset + row, x + col, value);
        for (int col = 0; col < static_cast<int>(constraints.umin.size()); ++col)
            if (const double value = constraints.D[row + col * ng]; value != 0)
                triplets.emplace_back(offset + row, u + col, value);
    }
}

} // namespace
std::shared_ptr<PIQPFanQPData> build_piqp_fan_qp(const fancyqlone::FanOCPStorage &fan,
                                                 bool native_bounds, bool eliminate_x0) {
    validate_piqp_fan(fan);

    auto data           = std::make_shared<PIQPFanQPData>();
    data->native_bounds = native_bounds;
    data->initial_state = fanqp::initial_state(fan);

    data->num_branches = static_cast<int>(fan.num_branches());

    data->horizon = static_cast<int>(fan.ocps.front().dim.N_horiz);

    data->nx = static_cast<int>(fan.ocps.front().dim.nx);

    data->nu = static_cast<int>(fan.ocps.front().dim.nu);

    const int B  = data->num_branches;
    const int N  = data->horizon;
    const int nx = data->nx;
    const int nu = data->nu;

    data->branches.resize(static_cast<std::size_t>(B));

    /*
     * PIQP multistage ordering:
     *
     * z = [
     *     branch0: x1,u1,...,xN,
     *     branch1: x1,u1,...,xN,
     *     ...
     *     global:  u0 (preceded by x0 only when elimination is disabled)
     * ]
     */

    int number_of_variables = 0;

    for (int branch = 0; branch < B; ++branch) {
        auto &layout = data->branches[static_cast<std::size_t>(branch)];

        layout.stages.resize(static_cast<std::size_t>(N + 1));

        layout.dynamics_rows.assign(static_cast<std::size_t>(N + 1), -1);

        for (int stage = 1; stage <= N; ++stage) {
            const int stage_nu = stage < N ? nu : 0;

            layout.stages[static_cast<std::size_t>(stage)] = {
                .x  = number_of_variables,
                .u  = stage_nu > 0 ? number_of_variables + nx : -1,
                .nx = nx,
                .nu = stage_nu,
            };

            number_of_variables += nx + stage_nu;
        }
    }

    if (!eliminate_x0) {
        data->root_x_offset = number_of_variables;
        number_of_variables += nx;
    }

    data->root_u_offset = number_of_variables;
    number_of_variables += nu;

    const int number_of_equalities = B * N * nx;

    data->constraints.resize(1 + B * N);
    fanqp::ReducedRoot reduced_root;
    if (eliminate_x0) {
        reduced_root         = fanqp::eliminate_root_state(fan, data->initial_state, native_bounds);
        data->constraints[0] = std::move(reduced_root.constraints);
        data->objective_offset = reduced_root.objective_offset;
    } else {
        data->constraints[0] = fanqp::analyze_constraints(fan.ocps, 0, native_bounds, false);
    }
    for (int branch = 0; branch < B; ++branch)
        for (int stage = 1; stage <= N; ++stage)
            data->constraints[fanqp::constraint_node(B, branch, stage)] =
                fanqp::analyze_constraints({&fan.ocps[branch], 1}, stage, native_bounds);
    int number_of_inequalities = 0;
    for (const auto &constraints : data->constraints) {
        data->general_offsets.push_back(number_of_inequalities);
        number_of_inequalities += static_cast<int>(constraints.lower.size());
    }

    const real_t infinity = std::numeric_limits<real_t>::infinity();

    data->c = PIQPVector::Zero(number_of_variables);

    data->b = PIQPVector::Zero(number_of_equalities);

    data->h_lower = PIQPVector::Zero(number_of_inequalities);

    data->h_upper = PIQPVector::Zero(number_of_inequalities);

    data->z_lower = PIQPVector::Constant(number_of_variables, -infinity);

    data->z_upper = PIQPVector::Constant(number_of_variables, infinity);

    std::vector<PIQPTriplet> P_triplets;
    std::vector<PIQPTriplet> A_triplets;
    std::vector<PIQPTriplet> G_triplets;

    // Sum the root costs. After elimination only R0 and r0 + S0*x0 remain.

    for (int branch = 0; branch < B; ++branch) {
        const auto &ocp = fan.ocps[static_cast<std::size_t>(branch)];

        add_upper_triangular_block(P_triplets, data->root_u_offset, ocp.R(0));

        if (!eliminate_x0) {
            add_upper_triangular_block(P_triplets, data->root_x_offset, ocp.Q(0));
            // S is nu-by-nx; PIQP's ordering is [x;u].
            add_transposed_block(P_triplets, data->root_x_offset, data->root_u_offset, ocp.S(0));
            add_vector(data->c, data->root_x_offset, ocp.q(0));
            add_vector(data->c, data->root_u_offset, ocp.r(0));
        }
    }

    if (eliminate_x0) {
        std::copy(reduced_root.r.begin(), reduced_root.r.end(),
                  data->c.data() + data->root_u_offset);
    } else {
        for (int i = 0; i < nx; ++i) {
            data->z_lower[data->root_x_offset + i] = data->initial_state[i];
            data->z_upper[data->root_x_offset + i] = data->initial_state[i];
        }
    }

    int equality_row = 0;
    set_constraints(*data, 0, data->root_x_offset, data->root_u_offset, G_triplets);

    for (int branch = 0; branch < B; ++branch) {
        const auto &ocp = fan.ocps[static_cast<std::size_t>(branch)];

        auto &layout = data->branches[static_cast<std::size_t>(branch)];

        for (int stage = 1; stage <= N; ++stage) {
            const auto &current = layout.stages[static_cast<std::size_t>(stage)];

            /*
             * Stage objective.
             */

            add_upper_triangular_block(P_triplets, current.x, ocp.Q(stage));

            copy_vector(data->c, current.x, ocp.q(stage));

            if (stage < N) {
                add_upper_triangular_block(P_triplets, current.u, ocp.R(stage));

                add_transposed_block(P_triplets, current.x, current.u, ocp.S(stage));

                copy_vector(data->c, current.u, ocp.r(stage));
            }

            /*
             * Dynamics:
             *
             * x_stage
             * - A_(stage-1) x_(stage-1)
             * - B_(stage-1) u_(stage-1)
             * = b_stage
             */

            layout.dynamics_rows[static_cast<std::size_t>(stage)] = equality_row;

            add_identity_block(A_triplets, equality_row, current.x, nx);

            const auto Ak = ocp.A(stage - 1);

            const auto Bk = ocp.B(stage - 1);

            if (stage == 1) {
                if (!eliminate_x0)
                    add_block(A_triplets, equality_row, data->root_x_offset, Ak, real_t{-1});

                add_block(A_triplets, equality_row, data->root_u_offset, Bk, real_t{-1});
            } else {
                const auto &previous = layout.stages[static_cast<std::size_t>(stage - 1)];

                add_block(A_triplets, equality_row, previous.x, Ak, real_t{-1});

                BATMAT_ASSERT(previous.nu == nu);

                add_block(A_triplets, equality_row, previous.u, Bk, real_t{-1});
            }

            if (eliminate_x0 && stage == 1)
                std::copy(reduced_root.b[branch].begin(), reduced_root.b[branch].end(),
                          data->b.data() + equality_row);
            else
                copy_vector(data->b, equality_row, ocp.b(stage));

            equality_row += nx;

            set_constraints(*data, fanqp::constraint_node(B, branch, stage), current.x, current.u,
                            G_triplets);
        }
    }

    BATMAT_ASSERT(equality_row == number_of_equalities);

    data->P.resize(number_of_variables, number_of_variables);

    data->P.setFromTriplets(P_triplets.begin(), P_triplets.end());

    data->P.makeCompressed();

    data->A.resize(number_of_equalities, number_of_variables);

    data->A.setFromTriplets(A_triplets.begin(), A_triplets.end());

    data->A.makeCompressed();

    data->G.resize(number_of_inequalities, number_of_variables);

    data->G.setFromTriplets(G_triplets.begin(), G_triplets.end());

    data->G.makeCompressed();

    return data;
}
std::shared_ptr<PIQPFanSolverData> create_piqp_fan_solver(std::shared_ptr<PIQPFanQPData> qp_data,
                                                          real_t tol) {
    if (!qp_data)
        throw std::invalid_argument("Null PIQP fan QP data");

    auto solver_data = std::make_shared<PIQPFanSolverData>();

    solver_data->qp_data = std::move(qp_data);

    auto &solver   = solver_data->solver;
    const auto &qp = *solver_data->qp_data;

    /*
     * Must be selected before setup().
     */
    solver.settings().kkt_solver = piqp::KKTSolver::sparse_multistage_parallel;

    solver.settings().verbose         = false;
    solver.settings().compute_timings = true;
    solver.settings().max_iter        = 100;
    solver.settings().eps_abs         = tol;
    solver.settings().eps_rel         = 0.0; // HPIPM and Cyqlone use absolute tolerances

    solver.settings().check_duality_gap   = false;
    solver.settings().eps_duality_gap_abs = tol;
    solver.settings().eps_duality_gap_rel = 0.0;

    solver.setup(qp.P, qp.c, qp.A, qp.b, qp.G, qp.h_lower, qp.h_upper, qp.z_lower, qp.z_upper);

    return solver_data;
}
std::chrono::nanoseconds solve_piqp_fan(PIQPFanSolverData &solver_data) {
    const auto start = std::chrono::steady_clock::now();

    solver_data.status = solver_data.solver.solve();

    const auto stop = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
}

PIQPStats get_stats_piqp_fan(const PIQPFanSolverData &solver_data) {
    const auto &result = solver_data.solver.result();

    PIQPStats stats;

    stats.status           = solver_data.status;
    stats.iter             = result.info.iter;
    stats.primal_objective = result.info.primal_obj + solver_data.qp_data->objective_offset;
    stats.run_time         = result.info.run_time;
    std::cout << result.info.run_time << std::endl;
    return stats;
}
fancyqlone::FanOCPStorage::Solution get_solution_piqp_fan(const PIQPFanSolverData &solver_data) {
    fancyqlone::FanOCPStorage::Solution fan_solution;

    const auto &data = *solver_data.qp_data;

    const auto &result = solver_data.solver.result();

    const auto &z                  = result.x;
    const PIQPVector bound_duals   = result.z_bu - result.z_bl;
    const PIQPVector general_duals = result.z_u - result.z_l;

    const int B  = data.num_branches;
    const int N  = data.horizon;
    const int nx = data.nx;
    const int nu = data.nu;

    fan_solution.solutions.resize(static_cast<std::size_t>(B));

    for (int branch = 0; branch < B; ++branch) {
        auto &branch_solution = fan_solution.solutions[static_cast<std::size_t>(branch)];

        /*
         * x0,u0,x1,u1,...,xN
         */
        const std::size_t primal_count = static_cast<std::size_t>((N + 1) * nx + N * nu);

        branch_solution.solution.resize(primal_count);

        real_t *primal_out = branch_solution.solution.data();

        std::copy_n(data.root_x_offset < 0 ? data.initial_state.data()
                                           : z.data() + data.root_x_offset,
                    nx, primal_out);

        primal_out += nx;

        std::copy_n(z.data() + data.root_u_offset, nu, primal_out);

        primal_out += nu;

        const auto &layout = data.branches[static_cast<std::size_t>(branch)];

        for (int stage = 1; stage <= N; ++stage) {
            const auto &offset = layout.stages[static_cast<std::size_t>(stage)];

            std::copy_n(z.data() + offset.x, offset.nx, primal_out);

            primal_out += offset.nx;

            if (offset.nu > 0) {
                std::copy_n(z.data() + offset.u, offset.nu, primal_out);

                primal_out += offset.nu;
            }
        }

        BATMAT_ASSERT(primal_out ==
                      branch_solution.solution.data() + branch_solution.solution.size());

        // Restore the original row order, including native bounds and skipped rows.
        for (int stage = 0; stage <= N; ++stage) {
            const int node          = fanqp::constraint_node(B, branch, stage);
            const auto &constraints = data.constraints[node];
            const int source        = stage == 0 ? branch : 0;
            const int x             = stage == 0 ? data.root_x_offset : layout.stages[stage].x;
            const int u             = stage == 0 ? data.root_u_offset : layout.stages[stage].u;
            const auto x_duals = std::span<const real_t>{x < 0 ? nullptr : bound_duals.data() + x,
                                                         constraints.xmin.size()};
            const auto u_duals = std::span<const real_t>{u < 0 ? nullptr : bound_duals.data() + u,
                                                         constraints.umin.size()};
            const auto g_duals =
                std::span<const real_t>{general_duals.data(),
                                        static_cast<std::size_t>(general_duals.size())}
                    .subspan(data.general_offsets[node], constraints.lower.size());
            for (int row = constraints.row_offsets[source];
                 row < constraints.row_offsets[source + 1]; ++row)
                branch_solution.inequality_multipliers.push_back(
                    fanqp::constraint_multiplier(constraints.rows[row], x_duals, u_duals, g_duals));
        }

        // Keep the original equality layout, with zeros for eliminated x0,
        // matching TreeQP's convention.
        branch_solution.equality_multipliers.resize(static_cast<std::size_t>((N + 1) * nx));

        real_t *equality_out = branch_solution.equality_multipliers.data();

        for (int i = 0; i < nx; ++i) {
            equality_out[i] = data.root_x_offset < 0 ? 0 : bound_duals[data.root_x_offset + i];
        }

        equality_out += nx;

        /*
         * PIQP y corresponds directly to rows of A*z = b.
         */
        for (int stage = 1; stage <= N; ++stage) {
            const int row = layout.dynamics_rows[static_cast<std::size_t>(stage)];

            std::transform(result.y.data() + row, result.y.data() + row + nx, equality_out,
                           [](const auto value) { return -value; });
            equality_out += nx;
        }

        BATMAT_ASSERT(equality_out == branch_solution.equality_multipliers.data() +
                                          branch_solution.equality_multipliers.size());
    }

    return fan_solution;
}
void update_x0_piqp_fan(fancyqlone::FanOCPStorage &fan, PIQPFanSolverData &solver_data,
                        const std::vector<fancyqlone::LinearOCPStorage::Solution> &solution,
                        index_t selected_branch) {
    auto &data = *solver_data.qp_data;

    const auto branch = static_cast<std::size_t>(selected_branch);

    const int nx = data.nx;
    const int nu = data.nu;

    /*
     * Existing branch solution ordering:
     *
     * x0,u0,x1,u1,...
     */
    const auto &primal = solution.at(branch).solution;
    if (primal.size() < static_cast<std::size_t>(2 * nx + nu))
        throw std::invalid_argument("PIQP solution does not contain the next state");
    const auto x1 = std::span<const real_t>{primal}.subspan(nx + nu, nx);

    if (data.root_x_offset < 0) {
        auto root = fanqp::eliminate_root_state(fan, x1, data.native_bounds);
        if (root.constraints.lower.size() != data.constraints[0].lower.size())
            throw std::invalid_argument("PIQP root constraint dimensions changed");
        std::copy(root.r.begin(), root.r.end(), data.c.data() + data.root_u_offset);
        for (int b = 0; b < data.num_branches; ++b)
            std::copy(root.b[b].begin(), root.b[b].end(),
                      data.b.data() + data.branches[b].dynamics_rows[1]);
        if (!root.constraints.lower.empty()) {
            std::copy(root.constraints.lower.begin(), root.constraints.lower.end(),
                      data.h_lower.data() + data.general_offsets[0]);
            std::copy(root.constraints.upper.begin(), root.constraints.upper.end(),
                      data.h_upper.data() + data.general_offsets[0]);
        }
        data.constraints[0]   = std::move(root.constraints);
        data.objective_offset = root.objective_offset;
        solver_data.solver.update(piqp::nullopt, data.c, piqp::nullopt, data.b, piqp::nullopt,
                                  data.h_lower, data.h_upper, piqp::nullopt, piqp::nullopt);
    } else {
        for (int i = 0; i < nx; ++i) {
            data.z_lower[data.root_x_offset + i] = x1[i];
            data.z_upper[data.root_x_offset + i] = x1[i];
        }
        solver_data.solver.update(piqp::nullopt, piqp::nullopt, piqp::nullopt, piqp::nullopt,
                                  piqp::nullopt, piqp::nullopt, piqp::nullopt, data.z_lower,
                                  data.z_upper);
    }

    data.initial_state.assign(x1.begin(), x1.end());
    for (auto &ocp : fan.ocps) {
        BATMAT_ASSERT(static_cast<int>(ocp.dim.nx) == nx);

        std::ranges::copy_n(x1.data(), nx, ocp.b(0).data);
    }
}
