#include "treehpipm.hpp"
#include "root-elimination.hpp"

#include <batmat/assume.hpp>
#include <guanaqo/mat-view.hpp>

#include <blasfeo_d_aux.h>


#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <memory>
#include <numeric>
#include <ranges>
#include <stdexcept>
#include <string>
#include <iostream>
#include <utility>
#include <vector>

using fancyqlone::index_t;
using fancyqlone::real_t;



template <class T, class I, class S, guanaqo::StorageOrder O>
std::vector<real_t>
compress_col_major(guanaqo::MatrixView<T, I, S, O> mat) {
    std::vector<real_t> data(
        static_cast<std::size_t>(mat.rows) * static_cast<std::size_t>(mat.cols));
    for (I j = 0; j < mat.cols; ++j)
        for (I i = 0; i < mat.rows; ++i)
            data[static_cast<std::size_t>(i + j * mat.rows)] = mat(i, j);
    return data;
}

std::vector<real_t> eye(index_t n) {
    std::vector<real_t> data(static_cast<std::size_t>(n * n), real_t{0});
    for (index_t i = 0; i < n; ++i)
        data[static_cast<std::size_t>(i + i * n)] = real_t{1};
    return data;
}

static auto prepare_hpipm_bounds(std::span<const real_t> bounds) {
    std::vector<real_t> values(bounds.size()), mask(bounds.size());
    for (std::size_t i = 0; i < bounds.size(); ++i) {
        const auto finite = std::isfinite(bounds[i]);
        values[i] = finite ? bounds[i] : real_t{0};
        mask[i]   = finite ? real_t{1} : real_t{0};
    }
    return std::pair{std::move(values), std::move(mask)};
}

static void set_hpipm_constraints(d_tree_ocp_qp &qp, int node,
                                  fanqp::StageConstraints &constraints) {
    if (!constraints.lower.empty()) {
        if (!constraints.C.empty())
            d_tree_ocp_qp_set_C(node, constraints.C.data(), &qp);
        if (!constraints.D.empty())
            d_tree_ocp_qp_set_D(node, constraints.D.data(), &qp);
        auto [lg, lg_mask] = prepare_hpipm_bounds(constraints.lower);
        auto [ug, ug_mask] = prepare_hpipm_bounds(constraints.upper);
        d_tree_ocp_qp_set_lg(node, lg.data(), &qp);
        d_tree_ocp_qp_set_ug(node, ug.data(), &qp);
        d_tree_ocp_qp_set_lg_mask(node, lg_mask.data(), &qp);
        d_tree_ocp_qp_set_ug_mask(node, ug_mask.data(), &qp);
    }
    auto compact = [](const auto &values, const auto &indices) {
        std::vector<real_t> result;
        for (int i : indices)
            result.push_back(values[i]);
        return result;
    };
    if (!constraints.state_indices.empty()) {
        auto [lb, lb_mask] = prepare_hpipm_bounds(compact(constraints.xmin, constraints.state_indices));
        auto [ub, ub_mask] = prepare_hpipm_bounds(compact(constraints.xmax, constraints.state_indices));
        d_tree_ocp_qp_set_idxbx(node, constraints.state_indices.data(), &qp);
        d_tree_ocp_qp_set_lbx(node, lb.data(), &qp);
        d_tree_ocp_qp_set_ubx(node, ub.data(), &qp);
        d_tree_ocp_qp_set_lbx_mask(node, lb_mask.data(), &qp);
        d_tree_ocp_qp_set_ubx_mask(node, ub_mask.data(), &qp);
    }
    if (!constraints.input_indices.empty()) {
        auto [lb, lb_mask] = prepare_hpipm_bounds(compact(constraints.umin, constraints.input_indices));
        auto [ub, ub_mask] = prepare_hpipm_bounds(compact(constraints.umax, constraints.input_indices));
        d_tree_ocp_qp_set_idxbu(node, constraints.input_indices.data(), &qp);
        d_tree_ocp_qp_set_lbu(node, lb.data(), &qp);
        d_tree_ocp_qp_set_ubu(node, ub.data(), &qp);
        d_tree_ocp_qp_set_lbu_mask(node, lb_mask.data(), &qp);
        d_tree_ocp_qp_set_ubu_mask(node, ub_mask.data(), &qp);
    }
}

struct FanTreeIndex {
    int branches{};
    int horizon{};

    [[nodiscard]] int num_nodes() const { return 1 + branches * horizon; }
    [[nodiscard]] int num_edges() const { return num_nodes() - 1; }

    [[nodiscard]] int node(int branch, int stage) const {
        BATMAT_ASSERT(branch >= 0 && branch < branches);
        BATMAT_ASSERT(stage >= 1 && stage <= horizon);
        return 1 + branch * horizon + stage - 1;
    }

    [[nodiscard]] int edge(int branch, int stage) const {
        return node(branch, stage) - 1;
    }
};

void validate_fan(const fancyqlone::FanOCPStorage &fan) {
    if (fan.ocps.empty())
        throw std::invalid_argument("FanOCPStorage must contain at least one branch");

    const auto &first = fan.ocps.front();
    if (first.dim.N_horiz <= 0)
        throw std::invalid_argument("FanOCPStorage horizon must be positive");

    for (std::size_t b = 0; b < fan.ocps.size(); ++b) {
        const auto &ocp = fan.ocps[b];
        if (ocp.dim.N_horiz != first.dim.N_horiz)
            throw std::invalid_argument("All fan branches must have the same horizon");
        if (ocp.dim.nx != first.dim.nx || ocp.dim.nu != first.dim.nu)
            throw std::invalid_argument("All fan branches must have equal nx and nu");
    }

}

std::size_t primal_size(const HPIPMTreeQPData &data) {
    const auto &dim = *data.dim;
    std::size_t size = static_cast<std::size_t>(dim.nx[0] + dim.nu[0]);
    for (int b = 0; b < data.num_branches; ++b)
        for (int stage = 1; stage <= data.horizon; ++stage) {
            const int node = data.node_index[b][stage];
            size += static_cast<std::size_t>(dim.nx[node] + dim.nu[node]);
        }
    return size;
}

std::size_t branch_offset(const HPIPMTreeQPData &data, int branch) {
    const auto &dim = *data.dim;
    std::size_t offset = static_cast<std::size_t>(dim.nx[0] + dim.nu[0]);
    for (int b = 0; b < branch; ++b)
        for (int stage = 1; stage <= data.horizon; ++stage) {
            const int node = data.node_index[b][stage];
            offset += static_cast<std::size_t>(dim.nx[node] + dim.nu[node]);
        }
    return offset;
}


std::shared_ptr<HPIPMTreeQPData>
build_hpipm_tree_qp(const fancyqlone::FanOCPStorage &fan, bool native_bounds, bool eliminate_x0) {
    validate_fan(fan);

    HPIPMTreeQPData d;
    d.native_bounds = native_bounds;
    d.eliminated_x0 = eliminate_x0;
    d.initial_state = fanqp::initial_state(fan);

    const int branches = static_cast<int>(fan.num_branches());
    const int horizon  = static_cast<int>(fan.ocps.front().dim.N_horiz);
    const int nx       = static_cast<int>(fan.ocps.front().dim.nx);
    const int nu       = static_cast<int>(fan.ocps.front().dim.nu);
    const FanTreeIndex map{branches, horizon};

    d.num_branches = branches;
    d.horizon      = horizon;
    d.node_index.assign(branches, std::vector<int>(horizon + 1, 0));
    d.edge_index.assign(branches, std::vector<int>(horizon + 1, -1));
    d.constraints.resize(map.num_nodes());
    fanqp::ReducedRoot reduced_root;
    if (eliminate_x0) {
        reduced_root = fanqp::eliminate_root_state(fan, d.initial_state, native_bounds);
        d.constraints[0] = std::move(reduced_root.constraints);
    } else {
        d.constraints[0] = fanqp::analyze_constraints(fan.ocps, 0, native_bounds, false);
    }


    // HPIPM's tree_create uses breadth-first node numbering and the number of
    // children of each node.  Therefore nodes are generated level-by-level:
    // root, all stage-1 nodes, all stage-2 nodes, ... .

    auto bfs_node = [branches](int branch, int stage) {
        return 1 + (stage - 1) * branches + branch;
    };

    d.tree_mem = std::make_unique<std::byte[]>(sctree_memsize(branches,1, horizon));

    d.tree = std::make_unique<struct tree>();
    std::unique_ptr<struct sctree> sctree = std::make_unique<struct sctree>();
    sctree_create(branches, 1, horizon, sctree.get(), d.tree_mem.get());
    sctree_cast_to_tree(sctree.get(), d.tree.get());

    d.dim_mem = std::make_unique<std::byte[]>(
        d_tree_ocp_qp_dim_memsize(map.num_nodes()));
    d.dim = std::make_unique<struct d_tree_ocp_qp_dim>();
    d_tree_ocp_qp_dim_create(map.num_nodes(), d.dim.get(), d.dim_mem.get());
    d_tree_ocp_qp_dim_set_tree(d.tree.get(), d.dim.get());

    d_tree_ocp_qp_dim_set_nx(0, eliminate_x0 ? 0 : nx, d.dim.get());
    d_tree_ocp_qp_dim_set_nu(0, nu, d.dim.get());
    d_tree_ocp_qp_dim_set_nbx(0, eliminate_x0 ? 0 : nx, d.dim.get());
    d_tree_ocp_qp_dim_set_nbu(0, static_cast<int>(d.constraints[0].input_indices.size()), d.dim.get());
    d_tree_ocp_qp_dim_set_ng(0, static_cast<int>(d.constraints[0].lower.size()), d.dim.get());
    for (int branch = 0; branch < branches; ++branch) {
        const auto &ocp = fan.ocps[static_cast<std::size_t>(branch)];
        d.node_index[branch][0] = 0;

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = bfs_node(branch, stage);
            // In a rooted tree with breadth-first numbering, edge node-1 enters node.
            const int edge = node - 1;
            d.node_index[branch][stage] = node;
            d.edge_index[branch][stage] = edge;

            d_tree_ocp_qp_dim_set_nx(node, nx, d.dim.get());
            d_tree_ocp_qp_dim_set_nu(node, stage < horizon ? nu : 0, d.dim.get());
            auto &constraints = d.constraints[node];
            constraints = fanqp::analyze_constraints({&ocp, 1}, stage, native_bounds);
            d_tree_ocp_qp_dim_set_nbx(node, static_cast<int>(constraints.state_indices.size()), d.dim.get());
            d_tree_ocp_qp_dim_set_nbu(node, static_cast<int>(constraints.input_indices.size()), d.dim.get());
            d_tree_ocp_qp_dim_set_ng(node, static_cast<int>(constraints.lower.size()), d.dim.get());
        }
    }

    d.qp_mem = std::make_unique<std::byte[]>(d_tree_ocp_qp_memsize(d.dim.get()));
    d.qp = std::make_unique<struct d_tree_ocp_qp>();
    d_tree_ocp_qp_create(d.dim.get(), d.qp.get(), d.qp_mem.get());

    if (!eliminate_x0) {
        auto Jbx0 = eye(nx);
        d_tree_ocp_qp_set_Jbx(0, Jbx0.data(), d.qp.get());
        d_tree_ocp_qp_set_lbx(0, d.initial_state.data(), d.qp.get());
        d_tree_ocp_qp_set_ubx(0, d.initial_state.data(), d.qp.get());
    }
    std::vector<real_t> R0_data(static_cast<std::size_t>(nu) * nu);
    std::vector<real_t> r0_data(static_cast<std::size_t>(nu));
    std::vector<real_t> q0_data(static_cast<std::size_t>(nx));
    std::vector<real_t> Q0_data(static_cast<std::size_t>(nx) * nx);
    std::vector<real_t> S0_data(static_cast<std::size_t>(nu) * nx);

    guanaqo::MatrixView<real_t, index_t> R0 = {{
        .data = R0_data.data(),
        .rows = nu,
        .cols = nu,
    }};

    guanaqo::MatrixView<real_t, index_t> r0 = {{
        .data = r0_data.data(),
        .rows = nu,
        .cols = 1,
    }};

    guanaqo::MatrixView<real_t, index_t> q0 = {{
        .data = q0_data.data(),
        .rows = nx,
        .cols = 1,
    }};

    guanaqo::MatrixView<real_t, index_t> Q0 = {{
        .data = Q0_data.data(),
        .rows = nx,
        .cols = nx,
    }};

    guanaqo::MatrixView<real_t, index_t> S0 = {{
        .data = S0_data.data(),
        .rows = nu,
        .cols = nx,
    }};

    R0.set_constant(0);
    r0.set_constant(0);
    q0.set_constant(0);
    Q0.set_constant(0);
    S0.set_constant(0);

    for (int branch = 0; branch < branches; ++branch) {
        const auto &ocp = fan.ocps[static_cast<std::size_t>(branch)]; 
        const auto Rj  = ocp.R(0);
        const auto rj  = ocp.r(0);
        const auto qj  = ocp.q(0);
        const auto Qj  = ocp.Q(0);
        const auto Sj  = ocp.S(0);

        assert(Rj.rows == R0.rows);
        assert(Rj.cols == R0.cols);
        assert(rj.rows == r0.rows);
        assert(rj.cols == 1);
        assert(Qj.rows == Q0.rows);
        assert(Qj.cols == Q0.cols);
        assert(Sj.rows == S0.rows);
        assert(Sj.cols == S0.cols);

        // R0 = sum_j Rj(0)
        R0 += Rj;

        // r0 = sum_j rj(0)
        r0 += rj;
        q0 += qj;
        // Q0 = sum_j Qj(0)
        Q0 += Qj;
        // S0 = sum_j Sj(0)
        S0 += Sj;
    }

    d_tree_ocp_qp_set_R(0, const_cast<real_t *>(compress_col_major(R0).data()), d.qp.get());
    if (eliminate_x0) {
        d_tree_ocp_qp_set_r(0, reduced_root.r.data(), d.qp.get());
    } else {
        d_tree_ocp_qp_set_r(0, const_cast<real_t *>(compress_col_major(r0).data()), d.qp.get());
        d_tree_ocp_qp_set_Q(0, const_cast<real_t *>(compress_col_major(Q0).data()), d.qp.get());
        d_tree_ocp_qp_set_S(0, const_cast<real_t *>(compress_col_major(S0).data()), d.qp.get());
        d_tree_ocp_qp_set_q(0, const_cast<real_t *>(compress_col_major(q0).data()), d.qp.get());
    }
    set_hpipm_constraints(*d.qp, 0, d.constraints[0]);

    for (int branch = 0; branch < branches; ++branch) {
        const auto &ocp = fan.ocps[static_cast<std::size_t>(branch)];
        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = d.node_index[branch][stage];
            const int edge = d.edge_index[branch][stage];

            auto B = compress_col_major(ocp.B(stage - 1));
            d_tree_ocp_qp_set_B(edge, B.data(), d.qp.get());
            if (eliminate_x0 && stage == 1) {
                d_tree_ocp_qp_set_b(edge, reduced_root.b[branch].data(), d.qp.get());
            } else {
                auto A = compress_col_major(ocp.A(stage - 1));
                d_tree_ocp_qp_set_A(edge, A.data(), d.qp.get());
                d_tree_ocp_qp_set_b(edge,
                    const_cast<real_t *>(ocp.b(stage).data), d.qp.get());
            }

            auto Q = compress_col_major(ocp.Q(stage));
            d_tree_ocp_qp_set_Q(node, Q.data(), d.qp.get());
            d_tree_ocp_qp_set_q(node,
                const_cast<real_t *>(ocp.q(stage).data), d.qp.get());
            set_hpipm_constraints(*d.qp, node, d.constraints[node]);

            if (stage < horizon) {
                auto R = compress_col_major(ocp.R(stage));
                auto S = compress_col_major(ocp.S(stage));
                d_tree_ocp_qp_set_R(node, R.data(), d.qp.get());
                d_tree_ocp_qp_set_S(node, S.data(), d.qp.get());
                d_tree_ocp_qp_set_r(node,
                    const_cast<real_t *>(ocp.r(stage).data), d.qp.get());
            }
        }
    }

    return std::make_shared<HPIPMTreeQPData>(std::move(d));
}

std::shared_ptr<HPIPMTreeSolverData>
create_hpipm_tree_solver(std::shared_ptr<HPIPMTreeQPData> qp_data,
                         int warm_start, int mode, real_t tol, int t0_init) {
    BATMAT_ASSERT(qp_data);
    HPIPMTreeSolverData d;

    d.qp_sol_mem = std::make_unique<std::byte[]>(
        d_tree_ocp_qp_sol_memsize(qp_data->dim.get()));
    d.qp_sol = std::make_unique<struct d_tree_ocp_qp_sol>();
    d_tree_ocp_qp_sol_create(qp_data->dim.get(), d.qp_sol.get(), d.qp_sol_mem.get());

    d.solver_arg_mem = std::make_unique<std::byte[]>(
        d_tree_ocp_qp_ipm_arg_memsize(qp_data->dim.get()));
    d.arg = std::make_unique<struct d_tree_ocp_qp_ipm_arg>();
    d_tree_ocp_qp_ipm_arg_create(qp_data->dim.get(), d.arg.get(),
                                  d.solver_arg_mem.get());

    int iter_max    = 100;
    double tol_stat = tol;
    double tol_eq   = tol;
    double tol_ineq = tol;
    double tol_comp = tol*100; // set lower tolerance for complementarity as FanCyqlone does not check this explicitly
    if (mode == 0) {
        d_tree_ocp_qp_ipm_arg_set_default(hpipm_mode::SPEED, d.arg.get());
    }
    else if (mode == 1) {
        d_tree_ocp_qp_ipm_arg_set_default(hpipm_mode::BALANCE, d.arg.get());
    }
    else {
        throw std::invalid_argument("Invalid HPIPM mode. Use 0 for SPEED or 1 for BALANCE.");
    }
    d_tree_ocp_qp_ipm_arg_set_iter_max(&iter_max, d.arg.get());
    d_tree_ocp_qp_ipm_arg_set_tol_stat(&tol_stat, d.arg.get());
    d_tree_ocp_qp_ipm_arg_set_tol_eq(&tol_eq, d.arg.get());
    d_tree_ocp_qp_ipm_arg_set_tol_ineq(&tol_ineq, d.arg.get());
    d_tree_ocp_qp_ipm_arg_set_tol_comp(&tol_comp, d.arg.get());
    d_tree_ocp_qp_ipm_arg_set_warm_start(&warm_start, d.arg.get());
    d.arg.get()->t0_init = t0_init;
    d.solver_mem = std::make_unique<std::byte[]>(
        d_tree_ocp_qp_ipm_ws_memsize(qp_data->dim.get(), d.arg.get()));
    d.workspace = std::make_unique<struct d_tree_ocp_qp_ipm_ws>();
    d_tree_ocp_qp_ipm_ws_create(qp_data->dim.get(), d.arg.get(),
                                 d.workspace.get(), d.solver_mem.get());

    d.qp_data = std::move(qp_data);
    return std::make_shared<HPIPMTreeSolverData>(std::move(d));
}

std::chrono::nanoseconds
solve_hpipm_tree(const HPIPMTreeQPData &qp_data,
                 HPIPMTreeSolverData &solver_data) {
    const auto t0 = std::chrono::steady_clock::now();
    d_tree_ocp_qp_ipm_solve(qp_data.qp.get(), solver_data.qp_sol.get(),
                             solver_data.arg.get(), solver_data.workspace.get());
    const auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0);
}

HPIPMStats get_stats_hpipm_tree(HPIPMTreeSolverData &solver_data) {
    HPIPMStats stats;
    d_tree_ocp_qp_ipm_get_status(solver_data.workspace.get(), &stats.status);
    d_tree_ocp_qp_ipm_get_iter(solver_data.workspace.get(), &stats.iter);
    d_tree_ocp_qp_ipm_get_max_res_stat(solver_data.workspace.get(), &stats.max_res_stat);
    d_tree_ocp_qp_ipm_get_max_res_eq(solver_data.workspace.get(), &stats.max_res_eq);
    d_tree_ocp_qp_ipm_get_max_res_ineq(solver_data.workspace.get(), &stats.max_res_ineq);
    d_tree_ocp_qp_ipm_get_max_res_comp(solver_data.workspace.get(), &stats.max_res_comp);
    return stats;
}

fancyqlone::FanOCPStorage::Solution
get_solution_hpipm_tree(HPIPMTreeSolverData &solver_data) {
    fancyqlone::FanOCPStorage::Solution fan_sol;

    const auto &data = *solver_data.qp_data;
    const auto &dim  = *data.dim;
    auto *qp_sol     = solver_data.qp_sol.get();

    const int num_branches = data.num_branches;
    const int horizon      = data.horizon;
    const int root         = 0;
    const int original_nx = static_cast<int>(data.initial_state.size());

    fan_sol.solutions.resize(
        static_cast<std::size_t>(num_branches));

    std::vector<real_t> x0 = data.initial_state;

    std::vector<real_t> u0(
        static_cast<std::size_t>(dim.nu[root]));

    if (!data.eliminated_x0)
        d_tree_ocp_qp_sol_get_x(root, qp_sol, x0.data());

    if (dim.nu[root] > 0)
        d_tree_ocp_qp_sol_get_u(root, qp_sol, u0.data());

    std::vector<std::vector<real_t>> multipliers(dim.Nn);
    for (int node = 0; node < dim.Nn; ++node) {
        const auto &constraints = data.constraints[node];
        std::vector<real_t> lb(dim.nb[node]), ub(dim.nb[node]);
        std::vector<real_t> lg(dim.ng[node]), ug(dim.ng[node]);
        if (dim.nb[node] > 0) {
            d_tree_ocp_qp_sol_get_lam_lb(node, qp_sol, lb.data());
            d_tree_ocp_qp_sol_get_lam_ub(node, qp_sol, ub.data());
        }
        if (dim.ng[node] > 0) {
            d_tree_ocp_qp_sol_get_lam_lg(node, qp_sol, lg.data());
            d_tree_ocp_qp_sol_get_lam_ug(node, qp_sol, ug.data());
        }
        std::vector<real_t> x_duals(dim.nx[node]), u_duals(dim.nu[node]);
        for (int i = 0; i < static_cast<int>(constraints.input_indices.size()); ++i)
            u_duals[constraints.input_indices[i]] = ub[i] - lb[i];
        for (int i = 0; i < static_cast<int>(constraints.state_indices.size()); ++i)
            x_duals[constraints.state_indices[i]] = ub[dim.nbu[node] + i] - lb[dim.nbu[node] + i];
        for (int i = 0; i < dim.ng[node]; ++i)
            ug[i] -= lg[i];
        for (const auto &row : constraints.rows)
            multipliers[node].push_back(fanqp::constraint_multiplier(row, x_duals, u_duals, ug));
    }

     //The root-state bound multiplier is shared by all branches.
     //This is the multiplier of x0 = x_init in the merged tree QP.
    std::vector<real_t> root_lam_lbx(
        static_cast<std::size_t>(dim.nb[root]));

    std::vector<real_t> root_lam_ubx(
        static_cast<std::size_t>(dim.nb[root]));

    if (dim.nx[root] > 0) {
        d_tree_ocp_qp_sol_get_lam_lb(
            root, qp_sol, root_lam_lbx.data());

        d_tree_ocp_qp_sol_get_lam_ub(
            root, qp_sol, root_lam_ubx.data());
    }

    for (int branch = 0; branch < num_branches; ++branch) {
        auto &branch_sol =
            fan_sol.solutions[static_cast<std::size_t>(branch)];

        std::size_t primal_count =
            static_cast<std::size_t>(original_nx) +
            static_cast<std::size_t>(dim.nu[root]);

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];

            primal_count +=
                static_cast<std::size_t>(dim.nx[node]);

            primal_count +=
                static_cast<std::size_t>(dim.nu[node]);
        }

        branch_sol.solution.resize(primal_count);

        real_t *primal_out = branch_sol.solution.data();

        std::copy(
            x0.begin(),
            x0.end(),
            primal_out);

        primal_out += original_nx;

        std::copy(
            u0.begin(),
            u0.end(),
            primal_out);

        primal_out += dim.nu[root];

        /*
         * Extract branch-specific states and inputs.
         */
        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];

            d_tree_ocp_qp_sol_get_x(
                node,
                qp_sol,
                primal_out);

            primal_out += dim.nx[node];

            if (dim.nu[node] > 0) {
                d_tree_ocp_qp_sol_get_u(
                    node,
                    qp_sol,
                    primal_out);

                primal_out += dim.nu[node];
            }
        }

        BATMAT_ASSERT(
            primal_out ==
            branch_sol.solution.data() +
                branch_sol.solution.size());

        for (int stage = 0; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];
            const auto &offsets = data.constraints[node].row_offsets;
            const int source = stage == 0 ? branch : 0;
            branch_sol.inequality_multipliers.insert(
                branch_sol.inequality_multipliers.end(),
                multipliers[node].begin() + offsets[source],
                multipliers[node].begin() + offsets[source + 1]);
        }

        std::size_t equality_count =
            static_cast<std::size_t>(original_nx);

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];

            equality_count +=
                static_cast<std::size_t>(dim.nx[node]);
        }

        branch_sol.equality_multipliers.resize(
            equality_count);

        real_t *eq_out =
            branch_sol.equality_multipliers.data();


        // Preserve the original layout, with zero multipliers for eliminated x0.
        for (int i = 0; i < original_nx; ++i) {
            eq_out[i] = data.eliminated_x0 ? 0 :
                root_lam_lbx[static_cast<std::size_t>(dim.nbu[root] + i)] -
                root_lam_ubx[static_cast<std::size_t>(dim.nbu[root] + i)];
        }

        eq_out += original_nx;

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];
            const int edge = data.edge_index[branch][stage];

            d_tree_ocp_qp_sol_get_pi(
                edge,
                qp_sol,
                eq_out);

            eq_out += dim.nx[node];
        }

        BATMAT_ASSERT(
            eq_out ==
            branch_sol.equality_multipliers.data() +
                branch_sol.equality_multipliers.size());
    }

    return fan_sol;
}


// Validation helpers

void check_tree_solution(
    const d_tree_ocp_qp_sol &solution)
{
    if (solution.dim == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has a null dimension pointer");
}

void check_node(
    int node,
    const d_tree_ocp_qp_sol &solution)
{
    check_tree_solution(solution);

    if (node < 0 || node >= solution.dim->Nn) {
        throw std::out_of_range(
            "Invalid HPIPM tree node " +
            std::to_string(node) +
            "; number of nodes is " +
            std::to_string(solution.dim->Nn));
    }
}

void check_edge(
    int edge,
    const d_tree_ocp_qp_sol &solution)
{
    check_tree_solution(solution);

    const int number_of_edges = solution.dim->Nn - 1;

    if (edge < 0 || edge >= number_of_edges) {
        throw std::out_of_range(
            "Invalid HPIPM tree edge " +
            std::to_string(edge) +
            "; number of edges is " +
            std::to_string(number_of_edges));
    }
}

void check_size(
    std::span<const double> value,
    int expected_size,
    const char *field)
{
    if (expected_size < 0) {
        throw std::invalid_argument(
            std::string{"Negative expected dimension for "} + field);
    }

    if (value.size() !=
        static_cast<std::size_t>(expected_size)) {
        throw std::invalid_argument(
            std::string{"Invalid size for "} + field +
            ": got " + std::to_string(value.size()) +
            ", expected " + std::to_string(expected_size));
    }
}

// BLASFEO packing helper

void pack_vector(
    std::span<const double> source,
    blasfeo_dvec &destination,
    int destination_offset)
{
    if (source.empty())
        return;

    if (destination_offset < 0)
        throw std::invalid_argument(
            "Negative BLASFEO destination offset");

    // BLASFEO's API takes double*, even though the source data is only read.
    blasfeo_pack_dvec(
        static_cast<int>(source.size()),
        const_cast<double *>(source.data()),
        1,
        &destination,
        destination_offset);
}

// ux offsets
//
// ux = [u; x; sl; su]

struct UXOffsets {
    int u;
    int x;
    int sl;
    int su;
    int total;
};

UXOffsets get_ux_offsets(
    int node,
    const d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    const auto &dim = *solution.dim;

    UXOffsets offsets{};

    offsets.u     = 0;
    offsets.x     = offsets.u + dim.nu[node];
    offsets.sl    = offsets.x + dim.nx[node];
    offsets.su    = offsets.sl + dim.ns[node];
    offsets.total = offsets.su + dim.ns[node];

    return offsets;
}

// lam/t offsets
//
// lam = [lb; lg; ub; ug; ls; us]
// t   = [lb; lg; ub; ug; ls; us]

struct InequalityOffsets {
    int lb;
    int lg;
    int ub;
    int ug;
    int ls;
    int us;
    int total;
};

InequalityOffsets get_inequality_offsets(
    int node,
    const d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    const auto &dim = *solution.dim;

    InequalityOffsets offsets{};

    offsets.lb    = 0;
    offsets.lg    = offsets.lb + dim.nb[node];
    offsets.ub    = offsets.lg + dim.ng[node];
    offsets.ug    = offsets.ub + dim.nb[node];
    offsets.ls    = offsets.ug + dim.ng[node];
    offsets.us    = offsets.ls + dim.ns[node];
    offsets.total = offsets.us + dim.ns[node];

    return offsets;
}


// =============================================================================
// ux setters
// =============================================================================

void tree_ocp_qp_sol_set_u(
    int node,
    std::span<const double> u,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.ux == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null ux storage");

    const auto &dim = *solution.dim;
    const auto offsets = get_ux_offsets(node, solution);

    check_size(u, dim.nu[node], "u");

    pack_vector(
        u,
        solution.ux[node],
        offsets.u);
}

void tree_ocp_qp_sol_set_x(
    int node,
    std::span<const double> x,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.ux == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null ux storage");

    const auto &dim = *solution.dim;
    const auto offsets = get_ux_offsets(node, solution);

    check_size(x, dim.nx[node], "x");

    pack_vector(
        x,
        solution.ux[node],
        offsets.x);
}

void tree_ocp_qp_sol_set_sl(
    int node,
    std::span<const double> sl,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.ux == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null ux storage");

    const auto &dim = *solution.dim;
    const auto offsets = get_ux_offsets(node, solution);

    check_size(sl, dim.ns[node], "sl");

    pack_vector(
        sl,
        solution.ux[node],
        offsets.sl);
}

void tree_ocp_qp_sol_set_su(
    int node,
    std::span<const double> su,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.ux == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null ux storage");

    const auto &dim = *solution.dim;
    const auto offsets = get_ux_offsets(node, solution);

    check_size(su, dim.ns[node], "su");

    pack_vector(
        su,
        solution.ux[node],
        offsets.su);
}

void tree_ocp_qp_sol_set_ux(
    int node,
    std::span<const double> ux,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.ux == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null ux storage");

    const auto offsets = get_ux_offsets(node, solution);

    check_size(
        ux,
        offsets.total,
        "ux");

    pack_vector(
        ux,
        solution.ux[node],
        0);
}

// =============================================================================
// pi setters
// =============================================================================

void tree_ocp_qp_sol_set_pi(
    int edge,
    std::span<const double> pi,
    d_tree_ocp_qp_sol &solution)
{
    check_edge(edge, solution);

    if (solution.pi == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null pi storage");

    // HPIPM convention: pi[edge] corresponds to the edge entering
    // child node edge + 1.
    const int child_node = edge + 1;

    check_size(
        pi,
        solution.dim->nx[child_node],
        "pi");

    pack_vector(
        pi,
        solution.pi[edge],
        0);
}

void tree_ocp_qp_sol_set_pi_for_node(
    int child_node,
    std::span<const double> pi,
    d_tree_ocp_qp_sol &solution)
{
    check_node(child_node, solution);

    if (child_node == 0)
        throw std::invalid_argument(
            "The root node has no incoming dynamics multiplier");

    tree_ocp_qp_sol_set_pi(
        child_node - 1,
        pi,
        solution);
}

// lam setters
//
// lam = [lb; lg; ub; ug; ls; us]

void tree_ocp_qp_sol_set_lam_lb(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.lam == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null lam storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.nb[node], "lam_lb");

    pack_vector(
        value,
        solution.lam[node],
        offsets.lb);
}

void tree_ocp_qp_sol_set_lam_lg(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.lam == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null lam storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ng[node], "lam_lg");

    pack_vector(
        value,
        solution.lam[node],
        offsets.lg);
}

void tree_ocp_qp_sol_set_lam_ub(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.lam == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null lam storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.nb[node], "lam_ub");

    pack_vector(
        value,
        solution.lam[node],
        offsets.ub);
}

void tree_ocp_qp_sol_set_lam_ug(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.lam == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null lam storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ng[node], "lam_ug");

    pack_vector(
        value,
        solution.lam[node],
        offsets.ug);
}

void tree_ocp_qp_sol_set_lam_ls(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.lam == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null lam storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ns[node], "lam_ls");

    pack_vector(
        value,
        solution.lam[node],
        offsets.ls);
}

void tree_ocp_qp_sol_set_lam_us(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.lam == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null lam storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ns[node], "lam_us");

    pack_vector(
        value,
        solution.lam[node],
        offsets.us);
}

void tree_ocp_qp_sol_set_lam(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.lam == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null lam storage");

    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(
        value,
        offsets.total,
        "lam");

    pack_vector(
        value,
        solution.lam[node],
        0);
}

// t setters
//
// t = [lb; lg; ub; ug; ls; us]

void tree_ocp_qp_sol_set_t_lb(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.t == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null t storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.nb[node], "t_lb");

    pack_vector(
        value,
        solution.t[node],
        offsets.lb);
}

void tree_ocp_qp_sol_set_t_lg(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.t == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null t storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ng[node], "t_lg");

    pack_vector(
        value,
        solution.t[node],
        offsets.lg);
}

void tree_ocp_qp_sol_set_t_ub(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.t == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null t storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.nb[node], "t_ub");

    pack_vector(
        value,
        solution.t[node],
        offsets.ub);
}

void tree_ocp_qp_sol_set_t_ug(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.t == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null t storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ng[node], "t_ug");

    pack_vector(
        value,
        solution.t[node],
        offsets.ug);
}

void tree_ocp_qp_sol_set_t_ls(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.t == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null t storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ns[node], "t_ls");

    pack_vector(
        value,
        solution.t[node],
        offsets.ls);
}

void tree_ocp_qp_sol_set_t_us(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.t == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null t storage");

    const auto &dim = *solution.dim;
    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(value, dim.ns[node], "t_us");

    pack_vector(
        value,
        solution.t[node],
        offsets.us);
}

void tree_ocp_qp_sol_set_t(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution)
{
    check_node(node, solution);

    if (solution.t == nullptr)
        throw std::invalid_argument(
            "HPIPM tree solution has null t storage");

    const auto offsets =
        get_inequality_offsets(node, solution);

    check_size(
        value,
        offsets.total,
        "t");

    pack_vector(
        value,
        solution.t[node],
        0);
}
void set_initial_guess_hpipm_tree(HPIPMTreeSolverData &solver_data,
                                  const fancyqlone::FanOCPStorage &fan,
                                  const fancyqlone::FanOCPStorage::Solution &guess) {
    const auto &data = *solver_data.qp_data;
    const auto &dim = *data.dim;
    auto &sol = *solver_data.qp_sol;
    constexpr real_t floor = 1e-8;
    if (fan.ocps.size() != static_cast<size_t>(data.num_branches) ||
        guess.solutions.size() != fan.ocps.size())
        throw std::invalid_argument("HPIPM initial guess branch count mismatch");

    // Root constraints are stacked by branch; other nodes belong to one branch.
    std::vector<real_t> root_lg(dim.ng[0], floor), root_ug(dim.ng[0], floor);
    std::vector<real_t> root_tl(dim.ng[0], floor), root_tu(dim.ng[0], floor);
    std::vector<real_t> root_lambda(dim.nx[0], 0);
    int root_offset = 0;
    for (int branch = 0; branch < data.num_branches; ++branch) {
        const auto &ocp = fan.ocps[branch];
        const auto &src = guess.solutions[branch];
        const auto N = ocp.dim.N_horiz, nx = ocp.dim.nx, nu = ocp.dim.nu;
        if (src.solution.size() != static_cast<size_t>(N * (nx + nu) + nx) ||
            src.equality_multipliers.size() != static_cast<size_t>((N + 1) * nx) ||
            src.inequality_multipliers.size() != static_cast<size_t>(N * ocp.dim.ny + ocp.dim.ny_N))
            throw std::invalid_argument("HPIPM initial guess dimensions mismatch");
        for (int i = 0; i < nx; ++i)
            root_lambda[i] += src.equality_multipliers[i];
        size_t y_offset = 0;
        for (int stage = 0; stage <= N; ++stage) {
            const int node = data.node_index[branch][stage];
            const auto x = stage == 0 ? std::span<const real_t>{ocp.b(0).data, static_cast<size_t>(nx)}
                                     : std::span{src.solution}.subspan(stage * (nx + nu), nx);
            const auto u = stage == N ? std::span<const real_t>{}
                                     : std::span{src.solution}.subspan(stage * (nx + nu) + nx, nu);
            tree_ocp_qp_sol_set_x(node, x, sol);
            tree_ocp_qp_sol_set_u(node, u, sol);
            if (stage > 0)
                tree_ocp_qp_sol_set_pi(data.edge_index[branch][stage],
                    std::span{src.equality_multipliers}.subspan(stage * nx, nx), sol);
            const auto C = ocp.C(stage);
            const auto lb = ocp.b_min(stage), ub = ocp.b_max(stage);
            std::vector<real_t> lg(C.rows), ug(C.rows), tl(C.rows), tu(C.rows);
            for (int row = 0; row < C.rows; ++row) {
                real_t value = 0;
                for (int col = 0; col < nx; ++col)
                    value += C(row, col) * x[col];
                if (stage < N)
                    for (int col = 0; col < nu; ++col)
                        value += ocp.D(stage)(row, col) * u[col];
                const auto y = src.inequality_multipliers[y_offset + row];
                lg[row] = std::max(-y, floor);
                ug[row] = std::max(y, floor);
                tl[row] = std::isfinite(lb(row, 0)) ? std::max(value - lb(row, 0), floor) : 1;
                tu[row] = std::isfinite(ub(row, 0)) ? std::max(ub(row, 0) - value, floor) : 1;
            }
            y_offset += C.rows;
            if (stage == 0) {
                std::ranges::copy(lg, root_lg.begin() + root_offset);
                std::ranges::copy(ug, root_ug.begin() + root_offset);
                std::ranges::copy(tl, root_tl.begin() + root_offset);
                std::ranges::copy(tu, root_tu.begin() + root_offset);
                root_offset += C.rows;
            } else {
                tree_ocp_qp_sol_set_lam_lg(node, lg, sol);
                tree_ocp_qp_sol_set_lam_ug(node, ug, sol);
                tree_ocp_qp_sol_set_t_lg(node, tl, sol);
                tree_ocp_qp_sol_set_t_ug(node, tu, sol);
            }
        }
    }
    std::vector<real_t> lb(dim.nb[0], floor), ub(dim.nb[0], floor), t(dim.nb[0], floor);
    for (int i = 0; i < dim.nx[0]; ++i) {
        lb[i] = std::max(root_lambda[i], floor);
        ub[i] = std::max(-root_lambda[i], floor);
    }
    tree_ocp_qp_sol_set_lam_lb(0, lb, sol);
    tree_ocp_qp_sol_set_lam_ub(0, ub, sol);
    tree_ocp_qp_sol_set_t_lb(0, t, sol);
    tree_ocp_qp_sol_set_t_ub(0, t, sol);
    tree_ocp_qp_sol_set_lam_lg(0, root_lg, sol);
    tree_ocp_qp_sol_set_lam_ug(0, root_ug, sol);
    tree_ocp_qp_sol_set_t_lg(0, root_tl, sol);
    tree_ocp_qp_sol_set_t_ug(0, root_tu, sol);
}

void shift_hpipm_tree_solution(
    HPIPMTreeSolverData &solver_data,
    real_t floor)
{
    auto &data = *solver_data.qp_data;
    auto &dim  = *data.dim;
    auto &sol  = *solver_data.qp_sol;

    const int B  = data.num_branches;
    const int N  = data.horizon;
    const int nx = dim.nx[0];
    const int nu = dim.nu[0];

    // Snapshot helpers. The snapshot is necessary because shifting overwrites
    // values that later stages still need to read.
    auto get_x = [&] (int node) {
        std::vector<real_t> x(static_cast<std::size_t>(dim.nx[node]));
        d_tree_ocp_qp_sol_get_x(node, &sol, x.data());
        return x;
    };

    auto get_u = [&] (int node) {
        std::vector<real_t> u(static_cast<std::size_t>(dim.nu[node]));
        if (dim.nu[node] > 0)
            d_tree_ocp_qp_sol_get_u(node, &sol, u.data());
        return u;
    };

    auto get_pi = [&] (int edge) {
        const int child = edge + 1;
        std::vector<real_t> pi(static_cast<std::size_t>(dim.nx[child]));
        d_tree_ocp_qp_sol_get_pi(edge, &sol, pi.data());
        return pi;
    };

    auto get_lam_lg = [&] (int node) {
        std::vector<real_t> v(static_cast<std::size_t>(dim.ng[node]));
        if (dim.ng[node] > 0)
            d_tree_ocp_qp_sol_get_lam_lg(node, &sol, v.data());
        return v;
    };

    auto get_lam_ug = [&] (int node) {
        std::vector<real_t> v(static_cast<std::size_t>(dim.ng[node]));
        if (dim.ng[node] > 0)
            d_tree_ocp_qp_sol_get_lam_ug(node, &sol, v.data());
        return v;
    };

    // Snapshot each branch before writing anything.
    struct BranchSnapshot {
        std::vector<std::vector<real_t>> x;
        std::vector<std::vector<real_t>> u;
        std::vector<std::vector<real_t>> pi;
        std::vector<std::vector<real_t>> lam_lg;
        std::vector<std::vector<real_t>> lam_ug;
    };

    std::vector<BranchSnapshot> old(static_cast<std::size_t>(B));

    for (int b = 0; b < B; ++b) {
        auto &s = old[static_cast<std::size_t>(b)];

        s.x.resize(static_cast<std::size_t>(N + 1));
        s.u.resize(static_cast<std::size_t>(N + 1));
        s.pi.resize(static_cast<std::size_t>(N + 1));
        s.lam_lg.resize(static_cast<std::size_t>(N + 1));
        s.lam_ug.resize(static_cast<std::size_t>(N + 1));

        // Root is duplicated conceptually for every branch.
        s.x[0] = get_x(0);
        s.u[0] = get_u(0);

        for (int k = 1; k <= N; ++k) {
            const int node = data.node_index[b][k];
            const int edge = data.edge_index[b][k];

            s.x[static_cast<std::size_t>(k)] = get_x(node);
            s.u[static_cast<std::size_t>(k)] = get_u(node);
            s.pi[static_cast<std::size_t>(k)] = get_pi(edge);
            s.lam_lg[static_cast<std::size_t>(k)] = get_lam_lg(node);
            s.lam_ug[static_cast<std::size_t>(k)] = get_lam_ug(node);
        }
    }

    // -------------------------------------------------------------------------
    // New root primal:
    //
    //   x0_new = mean_b x1_b
    //   u0_new = mean_b u1_b
    //
    // For N == 1, stage 1 is terminal and has no input, so retain old u0.
    // -------------------------------------------------------------------------

    std::vector<real_t> mean_x1(static_cast<std::size_t>(nx), 0.0);
    std::vector<real_t> mean_u1(static_cast<std::size_t>(nu), 0.0);

    for (int b = 0; b < B; ++b) {
        const auto &x1 = old[static_cast<std::size_t>(b)].x[1];

        for (int i = 0; i < nx; ++i)
            mean_x1[static_cast<std::size_t>(i)] +=
                x1[static_cast<std::size_t>(i)];

        const auto &u_source =
            N > 1
                ? old[static_cast<std::size_t>(b)].u[1]
                : old[static_cast<std::size_t>(b)].u[0];

        for (int i = 0; i < nu; ++i)
            mean_u1[static_cast<std::size_t>(i)] +=
                u_source[static_cast<std::size_t>(i)];
    }

    for (auto &v : mean_x1)
        v /= static_cast<real_t>(B);

    for (auto &v : mean_u1)
        v /= static_cast<real_t>(B);

    tree_ocp_qp_sol_set_x(0, mean_x1, sol);
    tree_ocp_qp_sol_set_u(0, mean_u1, sol);

    // The QP bound and the initial solution must use the same new x0.
    d_tree_ocp_qp_set_lbx(
        0,
        mean_x1.data(),
        data.qp.get());

    d_tree_ocp_qp_set_ubx(
        0,
        mean_x1.data(),
        data.qp.get());

    // -------------------------------------------------------------------------
    // New root equality multiplier:
    //
    //   lambda_x0_new = sum_b pi_b,1
    //
    // Represent lambda = lam_lb - lam_ub using positive components.
    // -------------------------------------------------------------------------

    std::vector<real_t> lambda_root(
        static_cast<std::size_t>(nx),
        0.0);

    for (int b = 0; b < B; ++b) {
        const auto &pi1 =
            old[static_cast<std::size_t>(b)].pi[1];

        for (int i = 0; i < nx; ++i)
            lambda_root[static_cast<std::size_t>(i)] +=
                pi1[static_cast<std::size_t>(i)];
    }

    std::vector<real_t> root_lb(
        static_cast<std::size_t>(dim.nb[0]),
        floor);

    std::vector<real_t> root_ub(
        static_cast<std::size_t>(dim.nb[0]),
        floor);

    for (int i = 0; i < nx; ++i) {
        const real_t lambda =
            lambda_root[static_cast<std::size_t>(i)];

        root_lb[static_cast<std::size_t>(i)] =
            std::max(lambda, real_t{0}) + floor;

        root_ub[static_cast<std::size_t>(i)] =
            std::max(-lambda, real_t{0}) + floor;
    }

    tree_ocp_qp_sol_set_lam_lb(0, root_lb, sol);
    tree_ocp_qp_sol_set_lam_ub(0, root_ub, sol);

    // -------------------------------------------------------------------------
    // New root general multipliers:
    //
    // Root general constraints are stacked branch by branch, so copy each
    // branch's old stage-1 block into the corresponding root block.
    // -------------------------------------------------------------------------

    std::vector<real_t> root_lg(
        static_cast<std::size_t>(dim.ng[0]),
        floor);

    std::vector<real_t> root_ug(
        static_cast<std::size_t>(dim.ng[0]),
        floor);

    int root_offset = 0;

    for (int b = 0; b < B; ++b) {
        const auto &lg1 =
            old[static_cast<std::size_t>(b)].lam_lg[1];

        const auto &ug1 =
            old[static_cast<std::size_t>(b)].lam_ug[1];

        std::copy(
            lg1.begin(),
            lg1.end(),
            root_lg.begin() + root_offset);

        std::copy(
            ug1.begin(),
            ug1.end(),
            root_ug.begin() + root_offset);

        root_offset += static_cast<int>(lg1.size());
    }

    BATMAT_ASSERT(root_offset == dim.ng[0]);

    tree_ocp_qp_sol_set_lam_lg(0, root_lg, sol);
    tree_ocp_qp_sol_set_lam_ug(0, root_ug, sol);

    // -------------------------------------------------------------------------
    // Shift branch stages:
    //
    //   destination k <- source min(k + 1, N)
    //
    // At the terminal end, hold the last state and multiplier.
    // -------------------------------------------------------------------------

    for (int b = 0; b < B; ++b) {
        const auto &s = old[static_cast<std::size_t>(b)];

        for (int k = 1; k <= N; ++k) {
            const int destination_node = data.node_index[b][k];
            const int destination_edge = data.edge_index[b][k];

            const int source_stage = std::min(k + 1, N);

            tree_ocp_qp_sol_set_x(
                destination_node,
                s.x[static_cast<std::size_t>(source_stage)],
                sol);

            if (dim.nu[destination_node] > 0) {
                // Terminal stage has no input. Hold the last available input.
                const int source_input_stage =
                    std::min(k + 1, N - 1);

                tree_ocp_qp_sol_set_u(
                    destination_node,
                    s.u[static_cast<std::size_t>(source_input_stage)],
                    sol);
            }

            tree_ocp_qp_sol_set_pi(
                destination_edge,
                s.pi[static_cast<std::size_t>(source_stage)],
                sol);

            // Copy general-constraint multipliers only when dimensions match.
            if (dim.ng[destination_node] ==
                static_cast<int>(
                    s.lam_lg[
                        static_cast<std::size_t>(source_stage)].size())) {
                tree_ocp_qp_sol_set_lam_lg(
                    destination_node,
                    s.lam_lg[
                        static_cast<std::size_t>(source_stage)],
                    sol);

                tree_ocp_qp_sol_set_lam_ug(
                    destination_node,
                    s.lam_ug[
                        static_cast<std::size_t>(source_stage)],
                    sol);
            }
        }
    }
}
void update_x0_hpipm_tree(fancyqlone::FanOCPStorage &fan,
                          HPIPMTreeQPData &qp_data,
                          std::vector<fancyqlone::LinearOCPStorage::Solution> &solution,
                          index_t branch) {
    const int b = static_cast<int>(branch);
    const auto &dim = *qp_data.dim;
    const auto nx = qp_data.initial_state.size();
    const auto &primal = solution.at(b).solution;
    if (primal.size() < 2 * nx + dim.nu[0])
        throw std::invalid_argument("HPIPM solution does not contain the next state");
    const auto x1 = std::span<const real_t>{primal}.subspan(nx + dim.nu[0], nx);
    if (qp_data.eliminated_x0) {
        auto root = fanqp::eliminate_root_state(fan, x1, qp_data.native_bounds);
        if (root.constraints.lower.size() != qp_data.constraints[0].lower.size())
            throw std::invalid_argument("HPIPM root constraint dimensions changed");
        qp_data.constraints[0] = std::move(root.constraints);
        set_hpipm_constraints(*qp_data.qp, 0, qp_data.constraints[0]);
        d_tree_ocp_qp_set_r(0, root.r.data(), qp_data.qp.get());
        for (int branch_index = 0; branch_index < qp_data.num_branches; ++branch_index)
            d_tree_ocp_qp_set_b(qp_data.edge_index[branch_index][1], root.b[branch_index].data(),
                              qp_data.qp.get());
    } else {
        d_tree_ocp_qp_set_lbx(0, const_cast<real_t *>(x1.data()), qp_data.qp.get());
        d_tree_ocp_qp_set_ubx(0, const_cast<real_t *>(x1.data()), qp_data.qp.get());
    }
    qp_data.initial_state.assign(x1.begin(), x1.end());

    for (auto &ocp : fan.ocps) {
        BATMAT_ASSERT(static_cast<std::size_t>(ocp.dim.nx) == nx);
        std::ranges::copy(x1, ocp.b(0).data);
    }
}
