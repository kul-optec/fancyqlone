extern "C" {
#define blasfeo_unpack_dvec treeqp_blasfeo_unpack_dvec
#include <blasfeo/blasfeo_d_aux.h>
#undef blasfeo_unpack_dvec
}

#include "treeqp.hpp"

#include <guanaqo/mat-view.hpp>
#include <iostream>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using cyqlone::index_t;

namespace {

template <class T, class I, class S, guanaqo::StorageOrder O>
std::vector<double> col_major(guanaqo::MatrixView<T, I, S, O> matrix) {
    std::vector<double> result(
        static_cast<std::size_t>(matrix.rows * matrix.cols));

    for (I column = 0; column < matrix.cols; ++column)
        for (I row = 0; row < matrix.rows; ++row)
            result[static_cast<std::size_t>(row + column * matrix.rows)] =
                matrix(row, column);

    return result;
}

std::vector<double> copy_vector(const double *data, int size) {
    if (size < 0)
        throw std::invalid_argument("Cannot copy a vector with a negative size");
    if (size == 0)
        return {};
    if (data == nullptr)
        throw std::invalid_argument("Cannot copy a null vector");
    return {data, data + static_cast<std::ptrdiff_t>(size)};
}
bool nearly_equal(double first,
                  double second,
                  double absolute_tolerance = 1e-12,
                  double relative_tolerance = 1e-12)
{
    if (first == second)
        return true;
    if (!std::isfinite(first) || !std::isfinite(second))
        return false;
    const double difference = std::abs(first - second);
    const double scale =
        std::max({1.0, std::abs(first), std::abs(second)});

    return difference <=
           absolute_tolerance + relative_tolerance * scale;
}

template <class MatrixView>
bool is_diagonal(const MatrixView &matrix) {
    for (decltype(matrix.rows) row = 0; row < matrix.rows; ++row)
        for (decltype(matrix.cols) column = 0; column < matrix.cols; ++column)
            if (row != column && matrix(row, column) != 0)
                return false;
    return true;
}

template <class MatrixView>
bool is_zero(const MatrixView &matrix) {
    for (decltype(matrix.rows) row = 0; row < matrix.rows; ++row)
        for (decltype(matrix.cols) column = 0; column < matrix.cols; ++column)
            if (matrix(row, column) != 0)
                return false;
    return true;
}

bool supports_clipping_objective(const cyqlone::LinearOCPStorage &ocp,
                                 int stage) {
    if (!is_diagonal(ocp.Q(stage)))
        return false;
    if (stage == ocp.dim.N_horiz)
        return true;
    return is_diagonal(ocp.R(stage)) && is_zero(ocp.S(stage));
}


void validate(const cyqlone::FanOCPStorage &fan) {
    if (fan.ocps.empty())
        throw std::invalid_argument("FanOCPStorage must contain at least one branch");

    const auto &dimensions = fan.ocps.front().dim;
    if (dimensions.N_horiz <= 0)
        throw std::invalid_argument("treeQP requires a positive horizon");

    for (const auto &ocp : fan.ocps)
        if (ocp.dim.N_horiz != dimensions.N_horiz ||
            ocp.dim.nx != dimensions.nx ||
            ocp.dim.nu != dimensions.nu)
            throw std::invalid_argument("All branches must have equal N, nx and nu");
}

int bfs_node(int branches, int branch, int stage) {
    return 1 + (stage - 1) * branches + branch;
}

TreeQp &get_qp(TreeQpData &data) {
    if (!data.qp)
        throw std::logic_error("treeQP data has not been initialized");
    return *data.qp;
}

const TreeQp &get_qp(const TreeQpData &data) {
    if (!data.qp)
        throw std::logic_error("treeQP data has not been initialized");
    return *data.qp;
}

double tree_qp_bound(double value) {
    if (std::isinf(value))
        return std::copysign(static_cast<double>(TREEQP_INF), value);
    return value;
}

void set_general_constraints(TreeQp &qp,
                             std::vector<double> C,
                             std::vector<double> D,
                             std::vector<double> lower,
                             std::vector<double> upper,
                             int node) {
    std::transform(lower.begin(), lower.end(), lower.begin(), tree_qp_bound);
    std::transform(upper.begin(), upper.end(), upper.begin(), tree_qp_bound);
    tree_qp_in_set_node_general_constraints(
        C.empty() ? nullptr : C.data(),
        D.empty() ? nullptr : D.data(),
        lower.empty() ? nullptr : lower.data(),
        upper.empty() ? nullptr : upper.data(),
        &qp.QpIn,
        node);
}

void set_terminal_objective(TreeQp &qp,
                            std::vector<double> Q,
                            std::vector<double> q,
                            int node) {
    qp.SetMatrixColMajor("Q", std::move(Q), -1, node);
    qp.SetVector("q", std::move(q), node);
}

void set_stage_objective(TreeQp &qp,
                         std::vector<double> Q,
                         std::vector<double> R,
                         std::vector<double> S,
                         std::vector<double> q,
                         std::vector<double> r,
                         int node) {
    qp.SetMatrixColMajor("Q", std::move(Q), -1, node);
    qp.SetMatrixColMajor("R", std::move(R), -1, node);
    qp.SetMatrixColMajor("S", std::move(S), -1, node);
    qp.SetVector("q", std::move(q), node);
    qp.SetVector("r", std::move(r), node);
}


void set_bound_vector(TreeQp &qp, const char *name, std::vector<double> values, int node) {
    std::transform(values.begin(), values.end(), values.begin(), tree_qp_bound);
    qp.SetVector(name, std::move(values), node);
}

} // namespace

std::shared_ptr<TreeQpData>
build_tree_qp(const cyqlone::FanOCPStorage &fan,bool clipping)
{
    validate(fan);

    auto data = std::make_shared<TreeQpData>();


    const int branches =
        static_cast<int>(fan.ocps.size());

    const int horizon =
        static_cast<int>(
            fan.ocps.front().dim.N_horiz);

    const int state_size =
        static_cast<int>(
            fan.ocps.front().dim.nx);

    const int input_size =
        static_cast<int>(
            fan.ocps.front().dim.nu);

    const int node_count =
        1 + branches * horizon;

    const auto &root_ocp =
        fan.ocps.front();

    data->num_branches = branches;
    data->horizon = horizon;

    data->nx.assign(node_count, state_size);
    data->nu.assign(node_count, input_size);
    data->nc.assign(node_count, 0);
    data->nk.assign(node_count, 0);

    // The root node is always node 0, and it has J children.
    data->nk[0] = branches;

    data->node_index.assign(
        branches,
        std::vector<int>(
            static_cast<std::size_t>(horizon + 1),
            0));

    data->edge_index.assign(
        branches,
        std::vector<int>(
            static_cast<std::size_t>(horizon + 1),
            -1));


    data->constraints.resize(node_count);
    data->constraints[0] = fanqp::analyze_constraints(fan.ocps, 0, clipping);
    bool native_bounds_supported = clipping && data->constraints[0].lower.empty();

    for (int branch = 0;
         branch < branches;
         ++branch)
    {
        const auto branch_index =
            static_cast<std::size_t>(branch);

        const auto &ocp =
            fan.ocps[branch_index];

        native_bounds_supported =
            native_bounds_supported && supports_clipping_objective(ocp, 0);

        data->node_index[branch][0] = 0;
        for (int stage = 1;
             stage <= horizon;
             ++stage)
        {
            const int node =
                bfs_node(branches, branch, stage);

            const bool terminal =
                stage == horizon;

            data->node_index[branch][stage] =
                node;

            // treeQP associates edge node-1 with non-root node.
             
            data->edge_index[branch][stage] =
                node - 1;

            data->nu[node] =
                terminal ? 0 : input_size;

            const int constraint_count =
                static_cast<int>(
                    terminal
                        ? ocp.dim.ny_N
                        : ocp.dim.ny);

            data->nc[node] =
                constraint_count;

            data->constraints[node] = fanqp::analyze_constraints({&ocp, 1}, stage, clipping);
            const auto &bounds =
                data->constraints[node];
            native_bounds_supported =
                native_bounds_supported && bounds.lower.empty() &&
                supports_clipping_objective(ocp, stage);

            if (!terminal)
                data->nk[node] = 1;
        }
    }

    for (int index = 0; index < state_size; ++index) {
        const double initial = root_ocp.b(0)(index, 0);
        const auto &root_bounds = data->constraints[0];
        if (initial < root_bounds.xmin[static_cast<std::size_t>(index)] ||
            initial > root_bounds.xmax[static_cast<std::size_t>(index)]) {
            native_bounds_supported = false;
            break;
        }
    }
    data->native_bounds = native_bounds_supported;
    if (data->native_bounds) {
        data->root_xmin = data->constraints[0].xmin;
        data->root_xmax = data->constraints[0].xmax;
        std::fill(data->nc.begin(), data->nc.end(), 0);
    } else {
        // TDUNES clipping requires every node to have only box constraints.
        data->constraints[0] = fanqp::analyze_constraints(fan.ocps, 0, false);
        for (int branch = 0; branch < branches; ++branch)
            for (int stage = 1; stage <= horizon; ++stage)
                data->constraints[data->node_index[branch][stage]] =
                    fanqp::analyze_constraints({&fan.ocps[branch], 1}, stage, false);
        for (int node = 0; node < node_count; ++node)
            data->nc[node] = static_cast<int>(data->constraints[node].lower.size());
    }

    data->qp = std::make_unique<TreeQp>(
        data->nx,
        data->nu,
        data->nc,
        data->nk);

    TreeQp &qp =
        get_qp(*data);

    std::vector<double> root_Q(
        static_cast<std::size_t>(
            state_size * state_size),
        0.0);

    std::vector<double> root_R(
        static_cast<std::size_t>(
            input_size * input_size),
        0.0);

    std::vector<double> root_S(
        static_cast<std::size_t>(
            input_size * state_size),
        0.0);

    std::vector<double> root_q(
        static_cast<std::size_t>(state_size),
        0.0);

    std::vector<double> root_r(
        static_cast<std::size_t>(input_size),
        0.0);

    for (const auto &ocp : fan.ocps)
    {
        const auto Q =
            col_major(ocp.Q(0));

        const auto R =
            col_major(ocp.R(0));

        const auto S =
            col_major(ocp.S(0));

        std::transform(
            root_Q.begin(),
            root_Q.end(),
            Q.begin(),
            root_Q.begin(),
            std::plus<>{});

        std::transform(
            root_R.begin(),
            root_R.end(),
            R.begin(),
            root_R.begin(),
            std::plus<>{});

        std::transform(
            root_S.begin(),
            root_S.end(),
            S.begin(),
            root_S.begin(),
            std::plus<>{});

        for (int index = 0;
             index < state_size;
             ++index)
        {
            root_q[static_cast<std::size_t>(index)] +=
                ocp.q(0)(index, 0);
        }

        for (int index = 0;
             index < input_size;
             ++index)
        {
            root_r[static_cast<std::size_t>(index)] +=
                ocp.r(0)(index, 0);
        }
    }

    set_stage_objective(
        qp,
        std::move(root_Q),
        std::move(root_R),
        std::move(root_S),
        std::move(root_q),
        std::move(root_r),
        0);

    // treeQP represents the initial state with one root node.
    const auto initial_state_reference =
        copy_vector(
            root_ocp.b(0).data,
            state_size);
    data->initial_state = initial_state_reference;

    for (std::size_t branch = 1;
         branch < fan.ocps.size();
         ++branch)
    {
        for (int index = 0;
             index < state_size;
             ++index)
        {
            const double candidate =
                fan.ocps[branch].b(0)(index, 0);

            const double reference =
                initial_state_reference[
                    static_cast<std::size_t>(index)];

            if (!nearly_equal(candidate, reference))
            {
                throw std::invalid_argument(
                    "All fan branches must share the same "
                    "initial state");
            }
        }
    }

    auto initial_state =
        initial_state_reference;

    qp.SetVector(
        "xmin",
        initial_state,
        0);

    qp.SetVector(
        "xmax",
        std::move(initial_state),
        0);

    if (data->native_bounds) {
        const auto &bounds = data->constraints[0];
        set_bound_vector(qp, "umin", bounds.umin, 0);
        set_bound_vector(qp, "umax", bounds.umax, 0);
    } else {
        const auto &constraints = data->constraints[0];
        set_general_constraints(qp, constraints.C, constraints.D,
                                constraints.lower, constraints.upper, 0);
    }

    // Construct each scenario branch.
    for (int branch = 0;
         branch < branches;
         ++branch)
    {
        const auto branch_index =
            static_cast<std::size_t>(branch);

        const auto &ocp =
            fan.ocps[branch_index];

        for (int stage = 1;
             stage <= horizon;
             ++stage)
        {
            const int node =
                data->node_index[branch][stage];

            const int edge =
                data->edge_index[branch][stage];

            const bool terminal =
                stage == horizon;

            auto A =
                col_major(
                    ocp.A(stage - 1));

            auto B =
                col_major(
                    ocp.B(stage - 1));

            auto dynamics_offset =
                copy_vector(
                    ocp.b(stage).data,
                    state_size);

            qp.SetMatrixColMajor(
                "A",
                std::move(A),
                -1,
                edge);

            qp.SetMatrixColMajor(
                "B",
                std::move(B),
                -1,
                edge);

            qp.SetVector(
                "b",
                std::move(dynamics_offset),
                edge);

            auto Q =
                col_major(
                    ocp.Q(stage));

            auto q =
                copy_vector(
                    ocp.q(stage).data,
                    state_size);

            if (!terminal)
            {
                auto R =
                    col_major(
                        ocp.R(stage));

                auto S =
                    col_major(
                        ocp.S(stage));

                auto r =
                    copy_vector(
                        ocp.r(stage).data,
                        input_size);

                set_stage_objective(
                    qp,
                    std::move(Q),
                    std::move(R),
                    std::move(S),
                    std::move(q),
                    std::move(r),
                    node);
            }
            else
            {
                set_terminal_objective(
                    qp,
                    std::move(Q),
                    std::move(q),
                    node);
            }

            if (data->native_bounds) {
                const auto &bounds = data->constraints[node];
                set_bound_vector(qp, "xmin", bounds.xmin, node);
                set_bound_vector(qp, "xmax", bounds.xmax, node);
                if (!terminal) {
                    set_bound_vector(qp, "umin", bounds.umin, node);
                    set_bound_vector(qp, "umax", bounds.umax, node);
                }
            } else {
                const auto &constraints = data->constraints[node];
                set_general_constraints(qp, constraints.C, constraints.D,
                                        constraints.lower, constraints.upper, node);
            }
        }
    }

    tree_qp_in_eliminate_x0(&qp.QpIn);
    tree_qp_out_eliminate_x0(&qp.QpOut);

    return data;
}

std::shared_ptr<TreeQpSolverData>
create_tree_qp_solver(std::shared_ptr<TreeQpData> qp_data,
                      int max_iterations,
                      double tolerance) {
    if (!qp_data)
        throw std::invalid_argument("Null treeQP data");
    if (!qp_data->qp)
        throw std::invalid_argument("treeQP data has not been initialized");
            // std::cout << "creating solver" << "\n";
    auto solver_data = std::make_shared<TreeQpSolverData>();
    solver_data->qp_data = std::move(qp_data);
    solver_data->solver =
        std::make_unique<TdunesSolver>(solver_data->qp_data->qp.get());
    // std::cout << "created solver" << "\n";

    if (solver_data->solver->SetOption(
            "clipping", solver_data->qp_data->native_bounds) != 0)
        throw std::runtime_error("Failed to configure the treeQP clipping solver");
    if (solver_data->solver->SetOption("maxIter", max_iterations) != 0)
        throw std::runtime_error("Failed to set the treeQP maximum iteration count");
    if (solver_data->solver->SetOption("stationarityTolerance", tolerance) != 0)
        throw std::runtime_error("Failed to set the treeQP stationarity tolerance");

    std::size_t dual_size = 0;
    for (int block = 0; block < solver_data->solver->TdunesWork.Np; ++block)
        dual_size += static_cast<std::size_t>(
            solver_data->solver->TdunesWork.slambda[block].m);
    solver_data->zero_dual.assign(dual_size, 0.0);
    
    return solver_data;
}

std::chrono::nanoseconds
solve_tree_qp(const TreeQpData &qp_data,
              TreeQpSolverData &solver_data,
              bool cold_start) {
    const TreeQp &qp = get_qp(qp_data);
    if (!solver_data.solver)
        throw std::logic_error("treeQP solver has not been initialized");

    const auto start = std::chrono::steady_clock::now();
    if (cold_start) {
        treeqp_tdunes_set_dual_initialization(
            solver_data.zero_dual.data(),
            &solver_data.solver->TdunesWork);
    }
    solver_data.last_status =
        solver_data.solver->Solve(const_cast<TreeQp *>(&qp));

    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now() - start);
}

TreeQpStats get_stats_tree_qp(TreeQpSolverData &solver_data) {
    if (!solver_data.qp_data)
        throw std::logic_error("treeQP solver has no associated QP");

    TreeQp &qp = get_qp(*solver_data.qp_data);
    return {
        solver_data.last_status,
        qp.QpOut.info.iter,
        tree_qp_out_max_KKT_res(&qp.QpIn, &qp.QpOut)
    };
}

cyqlone::FanOCPStorage::Solution
get_solution_tree_qp(
    TreeQpSolverData &solver_data)
{
    if (!solver_data.qp_data)
    {
        throw std::logic_error(
            "treeQP solver has no associated QP");
    }

    cyqlone::FanOCPStorage::Solution result;

    const auto &mapping =
        *solver_data.qp_data;

    TreeQp &qp =
        get_qp(*solver_data.qp_data);

    result.solutions.resize(
        static_cast<std::size_t>(
            mapping.num_branches));

    for (int branch = 0;
         branch < mapping.num_branches;
         ++branch)
    {
        auto &destination =
            result.solutions[
                static_cast<std::size_t>(branch)];

        std::size_t primal_count = 0;

        for (int stage = 0;
             stage <= mapping.horizon;
             ++stage)
        {
            const int node =
                mapping.node_index[branch][stage];

            primal_count +=
                static_cast<std::size_t>(
                    mapping.nx[node] +
                    mapping.nu[node]);
        }

        destination.solution.resize(
            primal_count);

        double *primal_out =
            destination.solution.data();

        for (int stage = 0;
             stage <= mapping.horizon;
             ++stage)
        {
            const int node =
                mapping.node_index[branch][stage];

            if (stage == 0) {
                std::copy(mapping.initial_state.begin(),
                          mapping.initial_state.end(),
                          primal_out);
            } else {
                treeqp_blasfeo_unpack_dvec(
                    mapping.nx[node],
                    &qp.QpOut.x[node],
                    0,
                    primal_out);
            }

            primal_out +=
                mapping.nx[node];

            if (mapping.nu[node] > 0)
            {
                treeqp_blasfeo_unpack_dvec(
                    mapping.nu[node],
                    &qp.QpOut.u[node],
                    0,
                    primal_out);

                primal_out +=
                    mapping.nu[node];
            }
        }

        for (int stage = 0; stage <= mapping.horizon; ++stage) {
            const int node = mapping.node_index[branch][stage];
            const auto &constraints = mapping.constraints[node];
            std::vector<double> x_duals(mapping.nx[node]), u_duals(mapping.nu[node]);
            std::vector<double> general_duals(mapping.nc[node]);
            if (mapping.native_bounds) {
                // x0 has been eliminated; its original bound multipliers may be zero.
                if (stage > 0)
                    treeqp_blasfeo_unpack_dvec(mapping.nx[node], &qp.QpOut.mu_x[node], 0, x_duals.data());
                if (mapping.nu[node] > 0)
                    treeqp_blasfeo_unpack_dvec(mapping.nu[node], &qp.QpOut.mu_u[node], 0, u_duals.data());
            } else if (mapping.nc[node] > 0) {
                treeqp_blasfeo_unpack_dvec(mapping.nc[node], &qp.QpOut.mu_d[node], 0, general_duals.data());
            }
            const int source = stage == 0 ? branch : 0;
            for (int row = constraints.row_offsets[source];
                 row < constraints.row_offsets[source + 1]; ++row)
                destination.inequality_multipliers.push_back(
                    fanqp::constraint_multiplier(constraints.rows[row], x_duals, u_duals, general_duals));
        }

        // Initial-state and branch-specific dynamics multipliers.
        std::size_t equality_count =
            static_cast<std::size_t>(
                mapping.nx[0]);

        for (int stage = 1;
             stage <= mapping.horizon;
             ++stage)
        {
            const int node =
                mapping.node_index[branch][stage];

            equality_count +=
                static_cast<std::size_t>(
                    mapping.nx[node]);
        }

        destination.equality_multipliers.resize(
            equality_count);

        double *eq_out =
            destination.equality_multipliers.data();

        // FanOCPStorage excludes x0 stationarity for an eliminated x0.
        std::fill_n(eq_out, mapping.nx[0], 0.0);

        eq_out +=
            mapping.nx[0];

        /*
         * Branch-specific dynamics multipliers.
         */
        for (int stage = 1;
             stage <= mapping.horizon;
             ++stage)
        {
            const int node =
                mapping.node_index[branch][stage];

            const int edge =
                mapping.edge_index[branch][stage];

            if (edge < 0)
            {
                throw std::logic_error(
                    "Invalid treeQP dynamics edge index");
            }

            treeqp_blasfeo_unpack_dvec(
                mapping.nx[node],
                &qp.QpOut.lam[edge],
                0,
                eq_out);

            eq_out +=
                mapping.nx[node];
        }
    }

    return result;
}

std::vector<double> make_dual_initialization_tree_qp(
    const TreeQpSolverData &solver_data, const cyqlone::FanOCPStorage::Solution &guess) {
    const auto &data = *solver_data.qp_data;
    const auto &work = solver_data.solver->TdunesWork;
    if (guess.solutions.size() != static_cast<size_t>(data.num_branches))
        throw std::invalid_argument("TreeQP initial guess branch count mismatch");
    std::vector<size_t> offsets(work.Np + 1, 0);
    for (int parent = 0; parent < work.Np; ++parent)
        offsets[parent + 1] = offsets[parent] + work.slambda[parent].m;
    std::vector<double> dual(offsets.back(), 0);
    for (int branch = 0; branch < data.num_branches; ++branch) {
        const auto &src = guess.solutions[branch].equality_multipliers;
        size_t source_offset = data.nx[0]; // Skip eliminated x0 multiplier.
        for (int stage = 1; stage <= data.horizon; ++stage) {
            const int node = data.node_index[branch][stage];
            const int parent = data.node_index[branch][stage - 1];
            const int nx = data.nx[node];
            if (source_offset + nx > src.size())
                throw std::invalid_argument("TreeQP initial guess dimensions mismatch");
            std::copy_n(src.data() + source_offset, nx,
                        dual.data() + offsets[parent] + work.idxpos[node]);
            source_offset += nx;
        }
    }
    return dual;
}

void set_dual_initialization_tree_qp(TreeQpSolverData &solver_data, std::span<const double> dual) {
    if (dual.size() != solver_data.zero_dual.size())
        throw std::invalid_argument("TreeQP initial dual size mismatch");
    treeqp_tdunes_set_dual_initialization(dual.data(), &solver_data.solver->TdunesWork);
}
void shift_treeqp_solution(
    TreeQpSolverData &solver_data,
    const cyqlone::FanOCPStorage::Solution &solution)
{
    const auto &data = *solver_data.qp_data;
    auto &work = solver_data.solver->TdunesWork;

    const int B = data.num_branches;
    const int N = data.horizon;

    if (solution.solutions.size() != static_cast<std::size_t>(B))
        throw std::invalid_argument(
            "TreeQP warm-start branch count mismatch");

    // -------------------------------------------------------------------------
    // TDunes stores lambda in one block per parent node.
    // Build offsets into the flattened initialization vector.
    // -------------------------------------------------------------------------

    std::vector<std::size_t> offsets(
        static_cast<std::size_t>(work.Np + 1),
        0);

    for (int parent = 0; parent < work.Np; ++parent) {
        offsets[static_cast<std::size_t>(parent + 1)] =
            offsets[static_cast<std::size_t>(parent)]
            + static_cast<std::size_t>(work.slambda[parent].m);
    }

    std::vector<double> dual(offsets.back(), 0.0);

    // -------------------------------------------------------------------------
    // Fan equality multipliers are stored as
    //
    //   [lambda_x0, lambda_1, ..., lambda_N]
    //
    // TreeQP does not have a multiplier corresponding to x0.
    //
    // Shift:
    //
    //   destination stage k <- source stage min(k + 1, N)
    //
    // Hence
    //
    //   new lambda_1 <- old lambda_2
    //   new lambda_2 <- old lambda_3
    //   ...
    //   new lambda_N <- old lambda_N
    //
    // -------------------------------------------------------------------------

    for (int b = 0; b < B; ++b) {

        const auto &src =
            solution.solutions[static_cast<std::size_t>(b)]
                .equality_multipliers;

        // Offset of every stage multiplier inside the Fan solution.
        std::vector<std::size_t> source_offsets(
            static_cast<std::size_t>(N + 1),
            0);

        std::size_t source_offset =
            static_cast<std::size_t>(data.nx[0]);

        for (int k = 1; k <= N; ++k) {
            source_offsets[static_cast<std::size_t>(k)] =
                source_offset;

            const int node = data.node_index[b][k];

            source_offset +=
                static_cast<std::size_t>(data.nx[node]);
        }

        if (source_offset > src.size())
            throw std::invalid_argument(
                "TreeQP warm-start dimensions mismatch");

        for (int k = 1; k <= N; ++k) {

            const int destination_node =
                data.node_index[b][k];

            const int destination_parent =
                data.node_index[b][k - 1];

            const int source_stage =
                std::min(k + 1, N);

            const int source_node =
                data.node_index[b][source_stage];

            const int destination_nx =
                data.nx[destination_node];

            const int source_nx =
                data.nx[source_node];

            if (destination_nx != source_nx)
                throw std::invalid_argument(
                    "TreeQP shifted multiplier dimension mismatch");

            const std::size_t src_offset =
                source_offsets[
                    static_cast<std::size_t>(source_stage)];

            const std::size_t dst_offset =
                offsets[
                    static_cast<std::size_t>(destination_parent)]
                + static_cast<std::size_t>(
                    work.idxpos[destination_node]);

            std::copy_n(
                src.data() + src_offset,
                destination_nx,
                dual.data() + dst_offset);
        }
    }

    // Set the shifted equality multipliers as the TDunes warm start.
    treeqp_tdunes_set_dual_initialization(
        dual.data(),
        &work);
}
void reset_treeqp_solution(TreeQpSolverData &solver_data) {
    treeqp_tdunes_set_dual_initialization(
        solver_data.zero_dual.data(),
        &solver_data.solver->TdunesWork);
}
void update_x0_tree_qp(
    cyqlone::FanOCPStorage &fan,
    TreeQpData &qp_data,
    const std::vector<cyqlone::LinearOCPStorage::Solution> &solution,
    index_t branch) {
    TreeQp &qp = get_qp(qp_data);
    const auto branch_index = static_cast<std::size_t>(branch);

    if (branch_index >= solution.size())
        throw std::out_of_range("Invalid branch index");

    const auto &branch_solution = solution[branch_index].solution;
    const std::size_t state_offset =
        static_cast<std::size_t>(qp_data.nx[0] + qp_data.nu[0]);
    const std::size_t state_size =
        static_cast<std::size_t>(qp_data.nx[0]);

    if (state_offset > branch_solution.size() ||
        state_size > branch_solution.size() - state_offset)
        throw std::out_of_range(
            "Branch solution does not contain the next state");

    const double *next_state = branch_solution.data() + state_offset;
    std::vector<double> next_state_vector(
        next_state, next_state + static_cast<std::ptrdiff_t>(state_size));

    if (qp_data.native_bounds) {
        for (std::size_t index = 0; index < state_size; ++index) {
            if (next_state_vector[index] < qp_data.root_xmin[index] ||
                next_state_vector[index] > qp_data.root_xmax[index]) {
                throw std::invalid_argument(
                    "Updated initial state violates a TreeQP state bound");
            }
        }
    }

    tree_qp_in_set_x0_colmaj(&qp.QpIn, next_state_vector.data());
    qp_data.initial_state = next_state_vector;

    for (auto &ocp : fan.ocps)
        std::copy_n(next_state, state_size, ocp.b(0).data);
}
