#include "mspiqp.hpp"

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

void validate_piqp_fan(const cyqlone::FanOCPStorage &fan)
{
    if (fan.ocps.empty())
        throw std::invalid_argument(
            "FanOCPStorage must contain at least one branch");

    const auto &first = fan.ocps.front();

    if (first.dim.N_horiz <= 0)
        throw std::invalid_argument(
            "FanOCPStorage horizon must be positive");

    for (const auto &ocp : fan.ocps) {
        if (ocp.dim.N_horiz != first.dim.N_horiz)
            throw std::invalid_argument(
                "All branches must have the same horizon");

        if (ocp.dim.nx != first.dim.nx ||
            ocp.dim.nu != first.dim.nu)
            throw std::invalid_argument(
                "All branches must have equal nx and nu");
    }
}

template <
    class T,
    class I,
    class S,
    guanaqo::StorageOrder Order>
void add_block(
    std::vector<PIQPTriplet> &triplets,
    int row_offset,
    int column_offset,
    guanaqo::MatrixView<T, I, S, Order> matrix,
    real_t scale = real_t{1})
{
    for (I column = 0; column < matrix.cols; ++column) {
        for (I row = 0; row < matrix.rows; ++row) {
            const real_t value =
                scale * static_cast<real_t>(
                    matrix(row, column));

            if (value != real_t{0}) {
                triplets.emplace_back(
                    row_offset + static_cast<int>(row),
                    column_offset + static_cast<int>(column),
                    value);
            }
        }
    }
}

template <
    class T,
    class I,
    class S,
    guanaqo::StorageOrder Order>
void add_transposed_block(
    std::vector<PIQPTriplet> &triplets,
    int row_offset,
    int column_offset,
    guanaqo::MatrixView<T, I, S, Order> matrix,
    real_t scale = real_t{1})
{
    for (I column = 0; column < matrix.cols; ++column) {
        for (I row = 0; row < matrix.rows; ++row) {
            const real_t value =
                scale * static_cast<real_t>(
                    matrix(row, column));

            if (value != real_t{0}) {
                triplets.emplace_back(
                    row_offset + static_cast<int>(column),
                    column_offset + static_cast<int>(row),
                    value);
            }
        }
    }
}

template <
    class T,
    class I,
    class S,
    guanaqo::StorageOrder Order>
void add_upper_triangular_block(
    std::vector<PIQPTriplet> &triplets,
    int offset,
    guanaqo::MatrixView<T, I, S, Order> matrix,
    real_t scale = real_t{1})
{
    BATMAT_ASSERT(matrix.rows == matrix.cols);

    for (I column = 0; column < matrix.cols; ++column) {
        for (I row = 0; row <= column; ++row) {
            const real_t value =
                scale * static_cast<real_t>(
                    matrix(row, column));

            if (value != real_t{0}) {
                triplets.emplace_back(
                    offset + static_cast<int>(row),
                    offset + static_cast<int>(column),
                    value);
            }
        }
    }
}

template <
    class T,
    class I,
    class S,
    guanaqo::StorageOrder Order>
void copy_vector(
    PIQPVector &destination,
    int offset,
    guanaqo::MatrixView<T, I, S, Order> source,
    real_t scale = real_t{1})
{
    BATMAT_ASSERT(source.cols == 1);

    for (I row = 0; row < source.rows; ++row) {
        destination[offset + static_cast<int>(row)] =
            scale * static_cast<real_t>(
                source(row, 0));
    }
}

template <
    class T,
    class I,
    class S,
    guanaqo::StorageOrder Order>
void add_vector(
    PIQPVector &destination,
    int offset,
    guanaqo::MatrixView<T, I, S, Order> source,
    real_t scale = real_t{1})
{
    BATMAT_ASSERT(source.cols == 1);

    for (I row = 0; row < source.rows; ++row) {
        destination[offset + static_cast<int>(row)] +=
            scale * static_cast<real_t>(
                source(row, 0));
    }
}

void add_identity_block(
    std::vector<PIQPTriplet> &triplets,
    int row_offset,
    int column_offset,
    int size,
    real_t scale = real_t{1})
{
    for (int i = 0; i < size; ++i) {
        triplets.emplace_back(
            row_offset + i,
            column_offset + i,
            scale);
    }
}

} // namespace
std::shared_ptr<PIQPFanQPData>
build_piqp_fan_qp(const cyqlone::FanOCPStorage &fan)
{
    validate_piqp_fan(fan);

    auto data = std::make_shared<PIQPFanQPData>();

    data->num_branches =
        static_cast<int>(fan.num_branches());

    data->horizon =
        static_cast<int>(
            fan.ocps.front().dim.N_horiz);

    data->nx =
        static_cast<int>(
            fan.ocps.front().dim.nx);

    data->nu =
        static_cast<int>(
            fan.ocps.front().dim.nu);

    const int B = data->num_branches;
    const int N = data->horizon;
    const int nx = data->nx;
    const int nu = data->nu;

    data->branches.resize(
        static_cast<std::size_t>(B));

    /*
     * PIQP multistage ordering:
     *
     * z = [
     *     branch0: x1,u1,...,xN,
     *     branch1: x1,u1,...,xN,
     *     ...
     *     global:  x0,u0
     * ]
     */

    int number_of_variables = 0;

    for (int branch = 0; branch < B; ++branch) {
        auto &layout =
            data->branches[
                static_cast<std::size_t>(branch)];

        layout.stages.resize(
            static_cast<std::size_t>(N + 1));

        layout.dynamics_rows.assign(
            static_cast<std::size_t>(N + 1),
            -1);

        layout.inequality_rows.assign(
            static_cast<std::size_t>(N + 1),
            -1);

        layout.inequality_sizes.assign(
            static_cast<std::size_t>(N + 1),
            0);

        for (int stage = 1; stage <= N; ++stage) {
            const int stage_nu =
                stage < N ? nu : 0;

            layout.stages[
                static_cast<std::size_t>(stage)] = {
                    .x = number_of_variables,
                    .u = stage_nu > 0
                           ? number_of_variables + nx
                           : -1,
                    .nx = nx,
                    .nu = stage_nu,
            };

            number_of_variables += nx + stage_nu;
        }
    }

    data->root_x_offset = number_of_variables;
    number_of_variables += nx;

    data->root_u_offset = number_of_variables;
    number_of_variables += nu;

    const int number_of_equalities =
        B * N * nx;

    int number_of_inequalities = 0;

    for (int branch = 0; branch < B; ++branch) {
        const auto &ocp =
            fan.ocps[
                static_cast<std::size_t>(branch)];

        for (int stage = 0; stage <= N; ++stage) {
            number_of_inequalities +=
                stage < N
                    ? static_cast<int>(ocp.dim.ny)
                    : static_cast<int>(ocp.dim.ny_N);
        }
    }

    const real_t infinity =
        std::numeric_limits<real_t>::infinity();

    data->c =
        PIQPVector::Zero(number_of_variables);

    data->b =
        PIQPVector::Zero(number_of_equalities);

    data->h_lower =
        PIQPVector::Zero(number_of_inequalities);

    data->h_upper =
        PIQPVector::Zero(number_of_inequalities);

    data->z_lower =
        PIQPVector::Constant(
            number_of_variables,
            -infinity);

    data->z_upper =
        PIQPVector::Constant(
            number_of_variables,
            infinity);

    std::vector<PIQPTriplet> P_triplets;
    std::vector<PIQPTriplet> A_triplets;
    std::vector<PIQPTriplet> G_triplets;

    /*
     * Shared root objective.
     *
     * This is equivalent to your HPIPM root construction:
     *
     * Q0 = sum_branch Q_branch(0)
     * R0 = sum_branch R_branch(0)
     * S0 = sum_branch S_branch(0)
     * q0 = sum_branch q_branch(0)
     * r0 = sum_branch r_branch(0)
     */

    for (int branch = 0; branch < B; ++branch) {
        const auto &ocp =
            fan.ocps[
                static_cast<std::size_t>(branch)];

        add_upper_triangular_block(
            P_triplets,
            data->root_x_offset,
            ocp.Q(0));

        add_upper_triangular_block(
            P_triplets,
            data->root_u_offset,
            ocp.R(0));

        /*
         * HPIPM order is [u;x]:
         *
         *     [R  S ]
         *     [S' Q ]
         *
         * PIQP order here is [x;u]:
         *
         *     [Q  S']
         *     [S  R ]
         *
         * S is nu-by-nx, so insert S' into the upper-right block.
         */
        add_transposed_block(
            P_triplets,
            data->root_x_offset,
            data->root_u_offset,
            ocp.S(0));

        add_vector(
            data->c,
            data->root_x_offset,
            ocp.q(0));

        add_vector(
            data->c,
            data->root_u_offset,
            ocp.r(0));
    }

    /*
     * Fix x0 through PIQP's variable bounds.
     */

    const auto &initial_state =
        fan.ocps.front().b(0);

    BATMAT_ASSERT(initial_state.rows == nx);

    for (int i = 0; i < nx; ++i) {
        const real_t value = initial_state.data[i];

        data->z_lower[data->root_x_offset + i] =
            value;

        data->z_upper[data->root_x_offset + i] =
            value;
    }

    int equality_row = 0;
    int inequality_row = 0;

    for (int branch = 0; branch < B; ++branch) {
        const auto &ocp =
            fan.ocps[
                static_cast<std::size_t>(branch)];

        auto &layout =
            data->branches[
                static_cast<std::size_t>(branch)];

        /*
         * Stage-zero constraints:
         *
         * lower <= C0*x0 + D0*u0 <= upper
         */

        const auto C0 = ocp.C(0);
        const auto D0 = ocp.D(0);
        const auto lower0 = ocp.b_min(0);
        const auto upper0 = ocp.b_max(0);

        layout.inequality_rows[0] =
            inequality_row;

        layout.inequality_sizes[0] =
            static_cast<int>(C0.rows);

        add_block(
            G_triplets,
            inequality_row,
            data->root_x_offset,
            C0);

        add_block(
            G_triplets,
            inequality_row,
            data->root_u_offset,
            D0);

        copy_vector(
            data->h_lower,
            inequality_row,
            lower0);

        copy_vector(
            data->h_upper,
            inequality_row,
            upper0);

        inequality_row +=
            static_cast<int>(C0.rows);

        for (int stage = 1; stage <= N; ++stage) {
            const auto &current =
                layout.stages[
                    static_cast<std::size_t>(stage)];

            /*
             * Stage objective.
             */

            add_upper_triangular_block(
                P_triplets,
                current.x,
                ocp.Q(stage));

            copy_vector(
                data->c,
                current.x,
                ocp.q(stage));

            if (stage < N) {
                add_upper_triangular_block(
                    P_triplets,
                    current.u,
                    ocp.R(stage));

                add_transposed_block(
                    P_triplets,
                    current.x,
                    current.u,
                    ocp.S(stage));

                copy_vector(
                    data->c,
                    current.u,
                    ocp.r(stage));
            }

            /*
             * Dynamics:
             *
             * x_stage
             * - A_(stage-1) x_(stage-1)
             * - B_(stage-1) u_(stage-1)
             * = b_stage
             */

            layout.dynamics_rows[
                static_cast<std::size_t>(stage)] =
                equality_row;

            add_identity_block(
                A_triplets,
                equality_row,
                current.x,
                nx);

            const auto Ak =
                ocp.A(stage - 1);

            const auto Bk =
                ocp.B(stage - 1);

            if (stage == 1) {
                add_block(
                    A_triplets,
                    equality_row,
                    data->root_x_offset,
                    Ak,
                    real_t{-1});

                add_block(
                    A_triplets,
                    equality_row,
                    data->root_u_offset,
                    Bk,
                    real_t{-1});
            }
            else {
                const auto &previous =
                    layout.stages[
                        static_cast<std::size_t>(
                            stage - 1)];

                add_block(
                    A_triplets,
                    equality_row,
                    previous.x,
                    Ak,
                    real_t{-1});

                BATMAT_ASSERT(previous.nu == nu);

                add_block(
                    A_triplets,
                    equality_row,
                    previous.u,
                    Bk,
                    real_t{-1});
            }

            copy_vector(
                data->b,
                equality_row,
                ocp.b(stage));

            equality_row += nx;

            /*
             * General stage constraints:
             *
             * lower <= C*x + D*u <= upper
             */

            const auto Ck = ocp.C(stage);
            const auto lower = ocp.b_min(stage);
            const auto upper = ocp.b_max(stage);

            layout.inequality_rows[
                static_cast<std::size_t>(stage)] =
                inequality_row;

            layout.inequality_sizes[
                static_cast<std::size_t>(stage)] =
                static_cast<int>(Ck.rows);

            add_block(
                G_triplets,
                inequality_row,
                current.x,
                Ck);

            if (stage < N) {
                add_block(
                    G_triplets,
                    inequality_row,
                    current.u,
                    ocp.D(stage));
            }

            copy_vector(
                data->h_lower,
                inequality_row,
                lower);

            copy_vector(
                data->h_upper,
                inequality_row,
                upper);

            inequality_row +=
                static_cast<int>(Ck.rows);
        }
    }

    BATMAT_ASSERT(
        equality_row == number_of_equalities);

    BATMAT_ASSERT(
        inequality_row == number_of_inequalities);

    data->P.resize(
        number_of_variables,
        number_of_variables);

    data->P.setFromTriplets(
        P_triplets.begin(),
        P_triplets.end());

    data->P.makeCompressed();

    data->A.resize(
        number_of_equalities,
        number_of_variables);

    data->A.setFromTriplets(
        A_triplets.begin(),
        A_triplets.end());

    data->A.makeCompressed();

    data->G.resize(
        number_of_inequalities,
        number_of_variables);

    data->G.setFromTriplets(
        G_triplets.begin(),
        G_triplets.end());

    data->G.makeCompressed();

    return data;
}
std::shared_ptr<PIQPFanSolverData>
create_piqp_fan_solver(
    std::shared_ptr<PIQPFanQPData> qp_data)
{
    if (!qp_data)
        throw std::invalid_argument(
            "Null PIQP fan QP data");

    auto solver_data =
        std::make_shared<PIQPFanSolverData>();

    solver_data->qp_data =
        std::move(qp_data);

    auto &solver = solver_data->solver;
    const auto &qp = *solver_data->qp_data;

    /*
     * Must be selected before setup().
     */
    solver.settings().kkt_solver =
        piqp::KKTSolver::sparse_multistage;

    solver.settings().verbose = false;
    solver.settings().compute_timings = true;
    solver.settings().max_iter = 100;

    solver.setup(
        qp.P,
        qp.c,
        qp.A,
        qp.b,
        qp.G,
        qp.h_lower,
        qp.h_upper,
        qp.z_lower,
        qp.z_upper);

    return solver_data;
}
std::chrono::nanoseconds
solve_piqp_fan(PIQPFanSolverData &solver_data)
{
    const auto start =
        std::chrono::steady_clock::now();

    solver_data.status =
        solver_data.solver.solve();

    const auto stop =
        std::chrono::steady_clock::now();

    return std::chrono::duration_cast<
        std::chrono::nanoseconds>(
            stop - start);
}

PIQPStats
get_stats_piqp_fan(
    const PIQPFanSolverData &solver_data)
{
    const auto &result =
        solver_data.solver.result();

    PIQPStats stats;

    stats.status = solver_data.status;
    stats.iter = result.info.iter;
    stats.primal_objective =
        result.info.primal_obj;
    stats.run_time =
        result.info.run_time;
    std::cout << result.info.run_time << std::endl;
    return stats;
}
cyqlone::FanOCPStorage::Solution
get_solution_piqp_fan(
    const PIQPFanSolverData &solver_data)
{
    cyqlone::FanOCPStorage::Solution fan_solution;

    const auto &data =
        *solver_data.qp_data;

    const auto &result =
        solver_data.solver.result();

    const auto &z = result.x;

    const int B = data.num_branches;
    const int N = data.horizon;
    const int nx = data.nx;
    const int nu = data.nu;

    fan_solution.solutions.resize(
        static_cast<std::size_t>(B));

    for (int branch = 0; branch < B; ++branch) {
        auto &branch_solution =
            fan_solution.solutions[
                static_cast<std::size_t>(branch)];

        /*
         * x0,u0,x1,u1,...,xN
         */
        const std::size_t primal_count =
            static_cast<std::size_t>(
                (N + 1) * nx + N * nu);

        branch_solution.solution.resize(
            primal_count);

        real_t *primal_out =
            branch_solution.solution.data();

        std::copy_n(
            z.data() + data.root_x_offset,
            nx,
            primal_out);

        primal_out += nx;

        std::copy_n(
            z.data() + data.root_u_offset,
            nu,
            primal_out);

        primal_out += nu;

        const auto &layout =
            data.branches[
                static_cast<std::size_t>(branch)];

        for (int stage = 1; stage <= N; ++stage) {
            const auto &offset =
                layout.stages[
                    static_cast<std::size_t>(stage)];

            std::copy_n(
                z.data() + offset.x,
                offset.nx,
                primal_out);

            primal_out += offset.nx;

            if (offset.nu > 0) {
                std::copy_n(
                    z.data() + offset.u,
                    offset.nu,
                    primal_out);

                primal_out += offset.nu;
            }
        }

        BATMAT_ASSERT(
            primal_out ==
            branch_solution.solution.data() +
                branch_solution.solution.size());

        /*
         * General inequality multipliers:
         *
         * signed convention = upper - lower
         */
        std::size_t inequality_count = 0;

        for (int stage = 0; stage <= N; ++stage) {
            inequality_count +=
                static_cast<std::size_t>(
                    layout.inequality_sizes[
                        static_cast<std::size_t>(stage)]);
        }

        branch_solution.inequality_multipliers.resize(
            inequality_count);

        real_t *inequality_out =
            branch_solution.inequality_multipliers.data();

        for (int stage = 0; stage <= N; ++stage) {
            const int row =
                layout.inequality_rows[
                    static_cast<std::size_t>(stage)];

            const int count =
                layout.inequality_sizes[
                    static_cast<std::size_t>(stage)];

            for (int i = 0; i < count; ++i) {
                inequality_out[i] =
                    result.z_u[row + i] -
                    result.z_l[row + i];
            }

            inequality_out += count;
        }

        /*
         * Equality multipliers:
         *
         * root-state bound multiplier,
         * followed by N dynamics multipliers.
         */
        branch_solution.equality_multipliers.resize(
            static_cast<std::size_t>(
                (N + 1) * nx));

        real_t *equality_out =
            branch_solution.equality_multipliers.data();

        /*
         * x0 is fixed using z_lower == z_upper.
         *
         * Match the HPIPM signed convention:
         * upper multiplier - lower multiplier.
         */
        for (int i = 0; i < nx; ++i) {
            const int variable =
                data.root_x_offset + i;

            equality_out[i] =
                -result.z_bl[variable] +
                result.z_bu[variable];
        }

        equality_out += nx;

        /*
         * PIQP y corresponds directly to rows of A*z = b.
         */
        for (int stage = 1; stage <= N; ++stage) {
            const int row =
                layout.dynamics_rows[
                    static_cast<std::size_t>(stage)];


            std::transform(
                result.y.data() + row,
                result.y.data() + row + nx,
                equality_out,
                [](const auto value) {
                    return -value;
                });
            equality_out += nx;
        }

        BATMAT_ASSERT(
            equality_out ==
            branch_solution.equality_multipliers.data() +
                branch_solution.equality_multipliers.size());
    }

    return fan_solution;
}
void update_x0_piqp_fan(
    cyqlone::FanOCPStorage &fan,
    PIQPFanSolverData &solver_data,
    const std::vector<
        cyqlone::LinearOCPStorage::Solution> &solution,
    index_t selected_branch)
{
    auto &data =
        *solver_data.qp_data;

    const auto branch =
        static_cast<std::size_t>(
            selected_branch);

    const int nx = data.nx;
    const int nu = data.nu;

    /*
     * Existing branch solution ordering:
     *
     * x0,u0,x1,u1,...
     */
    const real_t *x1 =
        solution[branch].solution.data() +
        nx + nu;

    for (int i = 0; i < nx; ++i) {
        data.z_lower[
            data.root_x_offset + i] = x1[i];

        data.z_upper[
            data.root_x_offset + i] = x1[i];
    }

    for (auto &ocp : fan.ocps) {
        BATMAT_ASSERT(
            static_cast<int>(ocp.dim.nx) == nx);

        std::ranges::copy_n(
            x1,
            nx,
            ocp.b(0).data);
    }

    /*
     * PIQP 0.6.x update call.
     *
     * If your installed overload requires optional references,
     * use the equivalent optional/ref-wrapper form from
     * piqp/sparse/solver.hpp.
     */
    solver_data.solver.update(
        piqp::nullopt,    // P
        piqp::nullopt,    // c
        piqp::nullopt,    // A
        piqp::nullopt,    // b
        piqp::nullopt,    // G
        piqp::nullopt,    // h_lower
        piqp::nullopt,    // h_upper
        data.z_lower,
        data.z_upper);
}