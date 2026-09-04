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
    const double difference = std::abs(first - second);
    const double scale =
        std::max({1.0, std::abs(first), std::abs(second)});

    return difference <=
           absolute_tolerance + relative_tolerance * scale;
}

void validate_identical_root_constraints(
    const cyqlone::FanOCPStorage &fan)
{
    const auto &reference = fan.ocps.front();

    const int nx = static_cast<int>(reference.dim.nx);
    const int nu = static_cast<int>(reference.dim.nu);
    const int ny = static_cast<int>(reference.dim.ny);

    for (std::size_t branch = 1;
         branch < fan.ocps.size();
         ++branch)
    {
        const auto &candidate = fan.ocps[branch];

        if (static_cast<int>(candidate.dim.ny) != ny)
        {
            throw std::invalid_argument(
                "Root constraints cannot be deduplicated because "
                "the branches have different root constraint counts");
        }

        for (int row = 0; row < ny; ++row)
        {
            for (int column = 0; column < nx; ++column)
            {
                if (!nearly_equal(
                        reference.C(0)(row, column),
                        candidate.C(0)(row, column)))
                {
                    throw std::invalid_argument(
                        "Root constraints cannot be deduplicated because "
                        "the branches have different root C matrices");
                }
            }

            for (int column = 0; column < nu; ++column)
            {
                if (!nearly_equal(
                        reference.D(0)(row, column),
                        candidate.D(0)(row, column)))
                {
                    throw std::invalid_argument(
                        "Root constraints cannot be deduplicated because "
                        "the branches have different root D matrices");
                }
            }

            if (!nearly_equal(
                    reference.b_min(0)(row, 0),
                    candidate.b_min(0)(row, 0)))
            {
                throw std::invalid_argument(
                    "Root constraints cannot be deduplicated because "
                    "the branches have different root lower bounds");
            }

            if (!nearly_equal(
                    reference.b_max(0)(row, 0),
                    candidate.b_max(0)(row, 0)))
            {
                throw std::invalid_argument(
                    "Root constraints cannot be deduplicated because "
                    "the branches have different root upper bounds");
            }
        }
    }
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

void set_general_constraints(TreeQp &qp,
                             std::vector<double> C,
                             std::vector<double> D,
                             std::vector<double> lower,
                             std::vector<double> upper,
                             int node) {
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

// Avoid mixed TDUNES stage solvers: the fast path is enabled only when every
// constraint in every node is an exact, unique +1 selector row.
struct NativeNodeBounds {
    bool supported = true;
    std::vector<double> xmin;
    std::vector<double> xmax;
    std::vector<double> umin;
    std::vector<double> umax;
    std::vector<TreeQpBoundMapping> mapping;
};

double tree_qp_bound(double value) {
    if (std::isinf(value))
        return std::copysign(static_cast<double>(TREEQP_INF), value);
    return value;
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

NativeNodeBounds extract_native_bounds(const cyqlone::LinearOCPStorage &ocp,
                                       int stage) {
    const int nx = static_cast<int>(ocp.dim.nx);
    const int nu = stage < ocp.dim.N_horiz ? static_cast<int>(ocp.dim.nu) : 0;
    const auto C = ocp.C(stage);
    const auto lower = ocp.b_min(stage);
    const auto upper = ocp.b_max(stage);

    NativeNodeBounds result{
        .xmin = std::vector<double>(static_cast<std::size_t>(nx), -TREEQP_INF),
        .xmax = std::vector<double>(static_cast<std::size_t>(nx), TREEQP_INF),
        .umin = std::vector<double>(static_cast<std::size_t>(nu), -TREEQP_INF),
        .umax = std::vector<double>(static_cast<std::size_t>(nu), TREEQP_INF),
        .mapping = std::vector<TreeQpBoundMapping>(static_cast<std::size_t>(C.rows)),
    };
    std::vector<bool> used(static_cast<std::size_t>(nx + nu), false);

    for (cyqlone::index_t row = 0; row < C.rows; ++row) {
        TreeQpBoundMapping mapping;
        int nonzeros = 0;
        for (int column = 0; column < nx; ++column) {
            const double coefficient = C(row, column);
            if (coefficient == 0)
                continue;
            if (coefficient != 1 || ++nonzeros != 1) {
                result.supported = false;
                return result;
            }
            mapping.kind = TreeQpBoundMapping::Kind::State;
            mapping.index = column;
        }
        if (nu > 0) {
            const auto D = ocp.D(stage);
            for (int column = 0; column < nu; ++column) {
                const double coefficient = D(row, column);
                if (coefficient == 0)
                    continue;
                if (coefficient != 1 || ++nonzeros != 1) {
                    result.supported = false;
                    return result;
                }
                mapping.kind = TreeQpBoundMapping::Kind::Input;
                mapping.index = column;
            }
        }
        if (nonzeros != 1) {
            result.supported = false;
            return result;
        }

        const int offset = mapping.kind == TreeQpBoundMapping::Kind::Input ? nx : 0;
        const auto variable = static_cast<std::size_t>(offset + mapping.index);
        if (used.at(variable)) {
            result.supported = false;
            return result;
        }
        used.at(variable) = true;
        result.mapping.at(static_cast<std::size_t>(row)) = mapping;

        if (mapping.kind == TreeQpBoundMapping::Kind::State) {
            result.xmin.at(static_cast<std::size_t>(mapping.index)) =
                tree_qp_bound(lower(row, 0));
            result.xmax.at(static_cast<std::size_t>(mapping.index)) =
                tree_qp_bound(upper(row, 0));
        } else {
            result.umin.at(static_cast<std::size_t>(mapping.index)) =
                tree_qp_bound(lower(row, 0));
            result.umax.at(static_cast<std::size_t>(mapping.index)) =
                tree_qp_bound(upper(row, 0));
        }
    }
    return result;
}

} // namespace

std::shared_ptr<TreeQpData>
build_tree_qp(const cyqlone::FanOCPStorage &fan,bool clipping)
{
    validate(fan);

    /*
     * All branches share the same treeQP root node. Consequently,
     * root constraints can be represented once only if the branch
     * descriptions contain identical root constraints.
     */
    validate_identical_root_constraints(fan);

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

    /*
     * The root has one child for each scenario branch.
     */
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

    /*
     * Preserve the constraint counts expected by each original
     * branch solution. This is distinct from data->nc, which
     * describes the deduplicated internal treeQP problem.
     */
    data->branch_nc.assign(
        branches,
        std::vector<int>(
            static_cast<std::size_t>(horizon + 1),
            0));
    data->bound_mapping.assign(
        branches,
        std::vector<std::vector<TreeQpBoundMapping>>(
            static_cast<std::size_t>(horizon + 1)));

    std::vector<NativeNodeBounds> native_node_bounds(
        static_cast<std::size_t>(node_count));
    native_node_bounds[0] = extract_native_bounds(root_ocp, 0);
    bool native_bounds_supported = native_node_bounds[0].supported&&clipping;

    /*
     * Store the shared root constraints only once internally.
     */
    const int root_constraint_count =
        static_cast<int>(root_ocp.dim.ny);

    data->nc[0] = root_constraint_count;

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
        data->bound_mapping[branch][0] = native_node_bounds[0].mapping;

        /*
         * Each external branch still expects its own copy of
         * the shared root multiplier.
         */
        data->branch_nc[branch][0] =
            static_cast<int>(ocp.dim.ny);

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

            /*
             * treeQP associates edge node-1 with non-root node.
             */
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

            data->branch_nc[branch][stage] =
                constraint_count;

            native_node_bounds[static_cast<std::size_t>(node)] =
                extract_native_bounds(ocp, stage);
            const auto &bounds =
                native_node_bounds[static_cast<std::size_t>(node)];
            data->bound_mapping[branch][stage] = bounds.mapping;
            native_bounds_supported =
                native_bounds_supported && bounds.supported &&
                supports_clipping_objective(ocp, stage);

            if (!terminal)
                data->nk[node] = 1;
        }
    }

    for (int index = 0; index < state_size; ++index) {
        const double initial = root_ocp.b(0)(index, 0);
        const auto &root_bounds = native_node_bounds[0];
        if (initial < root_bounds.xmin[static_cast<std::size_t>(index)] ||
            initial > root_bounds.xmax[static_cast<std::size_t>(index)]) {
            native_bounds_supported = false;
            break;
        }
    }
    data->native_bounds = native_bounds_supported;
    if (data->native_bounds) {
        data->root_xmin = native_node_bounds[0].xmin;
        data->root_xmax = native_node_bounds[0].xmax;
        std::fill(data->nc.begin(), data->nc.end(), 0);
    } else {
        data->bound_mapping.clear();
    }

    data->qp = std::make_unique<TreeQp>(
        data->nx,
        data->nu,
        data->nc,
        data->nk);

    TreeQp &qp =
        get_qp(*data);

    /*
     * Root objective.
     *
     * This retains the original behavior: the stage-zero
     * objective contributions of all branches are summed.
     *
     * If every branch stores an unweighted duplicate of the
     * same root objective and that objective should occur only
     * once, this summation must be replaced by the first
     * branch's objective. That is independent of constraint
     * deduplication.
     */
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

    /*
     * All branches must share the same initial state because
     * treeQP represents the initial state with one root node.
     */
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
        auto &bounds = native_node_bounds[0];
        qp.SetVector("umin", std::move(bounds.umin), 0);
        qp.SetVector("umax", std::move(bounds.umax), 0);
    } else {
        /*
         * Deduplicated shared-root constraints.
         *
         * The identical root constraint block is inserted once.
         */
        auto root_C =
            col_major(root_ocp.C(0));

        auto root_D =
            col_major(root_ocp.D(0));

        auto root_lower =
            copy_vector(
                root_ocp.b_min(0).data,
                root_constraint_count);

        auto root_upper =
            copy_vector(
                root_ocp.b_max(0).data,
                root_constraint_count);

        set_general_constraints(
            qp,
            std::move(root_C),
            std::move(root_D),
            std::move(root_lower),
            std::move(root_upper),
            0);
    }

    /*
     * Construct each scenario branch.
     */
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
                auto &bounds = native_node_bounds[static_cast<std::size_t>(node)];
                qp.SetVector("xmin", std::move(bounds.xmin), node);
                qp.SetVector("xmax", std::move(bounds.xmax), node);
                if (!terminal) {
                    qp.SetVector("umin", std::move(bounds.umin), node);
                    qp.SetVector("umax", std::move(bounds.umax), node);
                }
            } else {
                const int constraint_count =
                    data->nc[node];

                auto C =
                    col_major(
                        ocp.C(stage));

                std::vector<double> D;

                if (!terminal)
                {
                    D =
                        col_major(
                            ocp.D(stage));
                }

                auto lower =
                    copy_vector(
                        ocp.b_min(stage).data,
                        constraint_count);

                auto upper =
                    copy_vector(
                        ocp.b_max(stage).data,
                        constraint_count);

                set_general_constraints(
                    qp,
                    std::move(C),
                    std::move(D),
                    std::move(lower),
                    std::move(upper),
                    node);
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
    solver_data->solver->SetOption(
        "regType", "TREEQP_ALWAYS_LEVENBERG_MARQUARDT");
    solver_data->solver->TdunesOpts.checkLastActiveSet = 1;

    // Clipping needs stronger regularization on the active-state benchmarks.
    const double regularization =
        solver_data->qp_data->native_bounds ? 1e-2 : 1e-8;
    solver_data->solver->SetOption("regValue", regularization);
    solver_data->solver->SetOption("regTol", regularization);
    solver_data->solver->TdunesOpts.lineSearchMaxIter =
        solver_data->qp_data->native_bounds ? 50 : 60;

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

        /*
         * Primal solution.
         *
         * The root primal variables are copied into every branch
         * because node_index[branch][0] equals zero.
         */
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

        /*
         * General-constraint multipliers.
         *
         * branch_nc describes the original branch-wise layout,
         * whereas mapping.nc describes the internal deduplicated
         * treeQP representation.
         */
        std::size_t inequality_count = 0;

        for (int stage = 0;
             stage <= mapping.horizon;
             ++stage)
        {
            inequality_count +=
                static_cast<std::size_t>(
                    mapping.branch_nc[branch][stage]);
        }

        destination.inequality_multipliers.resize(
            inequality_count);

        double *ineq_out =
            destination.inequality_multipliers.data();

        if (mapping.native_bounds) {
            for (int stage = 0; stage <= mapping.horizon; ++stage) {
                const int node = mapping.node_index[branch][stage];
                const auto &bound_mapping = mapping.bound_mapping[branch][stage];
                if (bound_mapping.size() !=
                    static_cast<std::size_t>(mapping.branch_nc[branch][stage])) {
                    throw std::logic_error("Invalid native-bound multiplier mapping");
                }
                for (const auto &bound : bound_mapping) {
                    double multiplier = 0;
                    if (bound.kind == TreeQpBoundMapping::Kind::Input) {
                        treeqp_blasfeo_unpack_dvec(
                            1, &qp.QpOut.mu_u[node], bound.index, &multiplier);
                    } else if (stage > 0) {
                        treeqp_blasfeo_unpack_dvec(
                            1, &qp.QpOut.mu_x[node], bound.index, &multiplier);
                    }
                    if (stage == 0)
                        multiplier /= mapping.num_branches;
                    *ineq_out++ = multiplier;
                }
            }
        } else {
        /*
         * Distribute treeQP's shared root multiplier across the
         * duplicated branch constraints expected by FanOCPStorage.
         */
        const int branch_root_nc =
            mapping.branch_nc[branch][0];

        if (branch_root_nc > 0)
        {
            if (mapping.nc[0] != branch_root_nc)
            {
                throw std::logic_error(
                    "Branch root constraint count does not match "
                    "the deduplicated treeQP root constraint count");
            }

            treeqp_blasfeo_unpack_dvec(
                branch_root_nc,
                &qp.QpOut.mu_d[0],
                0,
                ineq_out);
            for (int index = 0; index < branch_root_nc; ++index)
                ineq_out[index] /= mapping.num_branches;

            ineq_out +=
                branch_root_nc;
        }

        /*
         * Branch-specific non-root multipliers.
         */
        for (int stage = 1;
             stage <= mapping.horizon;
             ++stage)
        {
            const int node =
                mapping.node_index[branch][stage];

            const int branch_stage_nc =
                mapping.branch_nc[branch][stage];

            if (branch_stage_nc == 0)
                continue;

            if (mapping.nc[node] != branch_stage_nc)
            {
                throw std::logic_error(
                    "Branch constraint count does not match "
                    "the corresponding treeQP node");
            }

            treeqp_blasfeo_unpack_dvec(
                branch_stage_nc,
                &qp.QpOut.mu_d[node],
                0,
                ineq_out);

            ineq_out +=
                branch_stage_nc;
        }
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
