#include "treehpipm.hpp"

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

using cyqlone::index_t;
using cyqlone::real_t;



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

template <class T, class I, class S, guanaqo::StorageOrder O>
auto prepare_hpipm_bounds(guanaqo::MatrixView<T, I, S, O> bounds) {
    std::vector<real_t> values(static_cast<std::size_t>(bounds.rows));
    std::vector<real_t> mask(static_cast<std::size_t>(bounds.rows));
    for (I i = 0; i < bounds.rows; ++i) {
        const auto finite = std::isfinite(bounds(i, 0));
        values[static_cast<std::size_t>(i)] = finite ? bounds(i, 0) : real_t{0};
        mask[static_cast<std::size_t>(i)]   = finite ? real_t{1} : real_t{0};
    }
    return std::pair{std::move(values), std::move(mask)};
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

void validate_fan(const cyqlone::FanOCPStorage &fan) {
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
build_hpipm_tree_qp(const cyqlone::FanOCPStorage &fan) {
    validate_fan(fan);

    HPIPMTreeQPData d;

    const int branches = static_cast<int>(fan.num_branches());
    const int horizon  = static_cast<int>(fan.ocps.front().dim.N_horiz);
    const int nx       = static_cast<int>(fan.ocps.front().dim.nx);
    const int nu       = static_cast<int>(fan.ocps.front().dim.nu);
    const FanTreeIndex map{branches, horizon};

    d.num_branches = branches;
    d.horizon      = horizon;
    d.node_index.assign(branches, std::vector<int>(horizon + 1, 0));
    d.edge_index.assign(branches, std::vector<int>(horizon + 1, -1));

    // HPIPM's tree_create uses breadth-first node numbering and the number of
    // children of each node.  Therefore nodes are generated level-by-level:
    // root, all stage-1 nodes, all stage-2 nodes, ... .
    //
    // The public branch-oriented mapping below decouples callers from that
    // HPIPM node order.
    auto bfs_node = [branches](int branch, int stage) {
        return 1 + (stage - 1) * branches + branch;
    };

    // std::vector<int> nkids(static_cast<std::size_t>(map.num_nodes()), 0);
    // nkids[0] = branches;
    // for (int stage = 1; stage < horizon; ++stage)
    //     for (int branch = 0; branch < branches; ++branch)
    //         nkids[static_cast<std::size_t>(bfs_node(branch, stage))] = 1;

    d.tree_mem = std::make_unique<std::byte[]>(sctree_memsize(branches,1, horizon));

    d.tree = std::make_unique<struct tree>();
    std::unique_ptr<struct sctree> sctree = std::make_unique<struct sctree>();
    sctree_create(branches, 1, horizon, sctree.get(), d.tree_mem.get());
    sctree_cast_to_tree(sctree.get(), d.tree.get());
    // tree_create(map.num_nodes(), nkids.data(), d.tree.get(), d.tree_mem.get());


    d.dim_mem = std::make_unique<std::byte[]>(
        d_tree_ocp_qp_dim_memsize(map.num_nodes()));
    d.dim = std::make_unique<struct d_tree_ocp_qp_dim>();
    d_tree_ocp_qp_dim_create(map.num_nodes(), d.dim.get(), d.dim_mem.get());
    d_tree_ocp_qp_dim_set_tree(d.tree.get(), d.dim.get());

    d_tree_ocp_qp_dim_set_nx(0, nx, d.dim.get());
    d_tree_ocp_qp_dim_set_nu(0, nu, d.dim.get());
    d_tree_ocp_qp_dim_set_nbx(0, nx, d.dim.get());
    int ng_0 = 0 ;
    for (int branch = 0; branch < branches; ++branch) {
        ng_0 += static_cast<int>(fan.ocps[static_cast<std::size_t>(branch)].dim.ny);
    }
    d_tree_ocp_qp_dim_set_ng(0, ng_0, d.dim.get());
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
            d_tree_ocp_qp_dim_set_ng(
                node,
                stage < horizon ? static_cast<int>(ocp.dim.ny)
                                : static_cast<int>(ocp.dim.ny_N),
                d.dim.get());
        }
    }

    d.qp_mem = std::make_unique<std::byte[]>(d_tree_ocp_qp_memsize(d.dim.get()));
    d.qp = std::make_unique<struct d_tree_ocp_qp>();
    d_tree_ocp_qp_create(d.dim.get(), d.qp.get(), d.qp_mem.get());

    auto Jbx0 = eye(nx);
    d_tree_ocp_qp_set_Jbx(0, Jbx0.data(), d.qp.get());
    const auto &x0 = fan.ocps.front().b(0);
    d_tree_ocp_qp_set_lbx(0, const_cast<real_t *>(x0.data), d.qp.get());
    d_tree_ocp_qp_set_ubx(0, const_cast<real_t *>(x0.data), d.qp.get());
    std::vector<real_t> R0_data(static_cast<std::size_t>(nu) * nu);
    std::vector<real_t> r0_data(static_cast<std::size_t>(nu));
    std::vector<real_t> q0_data(static_cast<std::size_t>(nx));
    std::vector<real_t> Q0_data(static_cast<std::size_t>(nx) * nx);
    std::vector<real_t> S0_data(static_cast<std::size_t>(nu) * nx);

    std::vector<real_t> D0_data(static_cast<std::size_t>(ng_0) * nu);
    std::vector<real_t> lg0_data(static_cast<std::size_t>(ng_0));
    std::vector<real_t> ug0_data(static_cast<std::size_t>(ng_0));

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

guanaqo::MatrixView<real_t, index_t> D0 = {{
    .data = D0_data.data(),
    .rows = ng_0,
    .cols = nu,
}};

guanaqo::MatrixView<real_t, index_t> lg0 = {{
    .data = lg0_data.data(),
    .rows = ng_0,
    .cols = 1,
}};

guanaqo::MatrixView<real_t, index_t> ug0 = {{
    .data = ug0_data.data(),
    .rows = ng_0,
    .cols = 1,
}};
    // std::cout << " Constraint Matrices initialized." << std::endl;

    R0.set_constant(0);
    // std::cout << " R0 initialized." << std::endl;

    r0.set_constant(0);
    q0.set_constant(0);
    Q0.set_constant(0);
    S0.set_constant(0);

    index_t row_offset = 0;
    // std::cout << " Tree Matrices initialized." << std::endl;

    for (int branch = 0; branch < branches; ++branch) {
        const auto &ocp = fan.ocps[static_cast<std::size_t>(branch)]; 
        const auto Rj  = ocp.R(0);
        const auto rj  = ocp.r(0);
        const auto Qj  = ocp.Q(0);
        const auto Sj  = ocp.S(0);
        const auto Dj  = ocp.D(0);
        const auto lgj = ocp.b_min(0);
        const auto ugj = ocp.b_max(0);

        assert(Rj.rows == R0.rows);
        assert(Rj.cols == R0.cols);
        assert(rj.rows == r0.rows);
        assert(rj.cols == 1);
        assert(Qj.rows == Q0.rows);
        assert(Qj.cols == Q0.cols);
        assert(Sj.rows == S0.rows);
        assert(Sj.cols == S0.cols);

        assert(Dj.cols == D0.cols);
        assert(lgj.rows == Dj.rows);
        assert(ugj.rows == Dj.rows);

        // R0 = sum_j Rj(0)
        R0 += Rj;

        // r0 = sum_j rj(0)
        r0 += rj;
        // Q0 = sum_j Qj(0)
        Q0 += Qj;
        // S0 = sum_j Sj(0)
        S0 += Sj;
        // D0 = vstack_j Dj(0)
        D0.middle_rows(row_offset, Dj.rows) = Dj;

        // lg0 = vstack_j b_min,j(0)
        lg0.middle_rows(row_offset, lgj.rows) = lgj;

        // ug0 = vstack_j b_max,j(0)
        ug0.middle_rows(row_offset, ugj.rows) = ugj;

        row_offset += Dj.rows;
    }
    // std::cout << " Matrices Calculated." << std::endl;

    assert(row_offset == D0.rows);
    assert(row_offset == lg0.rows);
    assert(row_offset == ug0.rows);
    d_tree_ocp_qp_set_R(0, const_cast<real_t *>(compress_col_major(R0).data()), d.qp.get());
    d_tree_ocp_qp_set_r(0, const_cast<real_t *>(compress_col_major(r0).data()), d.qp.get());
    d_tree_ocp_qp_set_D(0, const_cast<real_t *>(compress_col_major(D0).data()), d.qp.get());
    auto [lg0_values, lg0_mask] = prepare_hpipm_bounds(lg0);
    auto [ug0_values, ug0_mask] = prepare_hpipm_bounds(ug0);
    d_tree_ocp_qp_set_lg(0, lg0_values.data(), d.qp.get());
    d_tree_ocp_qp_set_lg_mask(0, lg0_mask.data(), d.qp.get());
    d_tree_ocp_qp_set_ug(0, ug0_values.data(), d.qp.get());
    d_tree_ocp_qp_set_ug_mask(0, ug0_mask.data(), d.qp.get());
    d_tree_ocp_qp_set_Q(0, const_cast<real_t *>(compress_col_major(Q0).data()), d.qp.get());
    d_tree_ocp_qp_set_S(0, const_cast<real_t *>(compress_col_major(S0).data()), d.qp.get());
    d_tree_ocp_qp_set_q(0, const_cast<real_t *>(compress_col_major(q0).data()), d.qp.get());

    for (int branch = 0; branch < branches; ++branch) {
        const auto &ocp = fan.ocps[static_cast<std::size_t>(branch)];
        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = d.node_index[branch][stage];
            const int edge = d.edge_index[branch][stage];

            auto A = compress_col_major(ocp.A(stage - 1));
            auto B = compress_col_major(ocp.B(stage - 1));
            d_tree_ocp_qp_set_A(edge, A.data(), d.qp.get());
            d_tree_ocp_qp_set_B(edge, B.data(), d.qp.get());
            d_tree_ocp_qp_set_b(edge,
                const_cast<real_t *>(ocp.b(stage).data), d.qp.get());

            auto Q = compress_col_major(ocp.Q(stage));
            auto C = compress_col_major(ocp.C(stage));
            d_tree_ocp_qp_set_Q(node, Q.data(), d.qp.get());
            d_tree_ocp_qp_set_q(node,
                const_cast<real_t *>(ocp.q(stage).data), d.qp.get());
            d_tree_ocp_qp_set_C(node, C.data(), d.qp.get());
            auto [lg, lg_mask] = prepare_hpipm_bounds(ocp.b_min(stage));
            auto [ug, ug_mask] = prepare_hpipm_bounds(ocp.b_max(stage));
            d_tree_ocp_qp_set_lg(node, lg.data(), d.qp.get());
            d_tree_ocp_qp_set_lg_mask(node, lg_mask.data(), d.qp.get());
            d_tree_ocp_qp_set_ug(node, ug.data(), d.qp.get());
            d_tree_ocp_qp_set_ug_mask(node, ug_mask.data(), d.qp.get());

            if (stage < horizon) {
                auto R = compress_col_major(ocp.R(stage));
                auto S = compress_col_major(ocp.S(stage));
                auto D = compress_col_major(ocp.D(stage));
                d_tree_ocp_qp_set_R(node, R.data(), d.qp.get());
                d_tree_ocp_qp_set_S(node, S.data(), d.qp.get());
                d_tree_ocp_qp_set_r(node,
                    const_cast<real_t *>(ocp.r(stage).data), d.qp.get());
                d_tree_ocp_qp_set_D(node, D.data(), d.qp.get());
            }
        }
    }

    return std::make_shared<HPIPMTreeQPData>(std::move(d));
}

std::shared_ptr<HPIPMTreeSolverData>
create_hpipm_tree_solver(std::shared_ptr<HPIPMTreeQPData> qp_data,
                         int warm_start, int mode) {
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
    double tol_stat = 1e-8;
    double tol_eq   = 1e-8;
    double tol_ineq = 1e-8;
    double tol_comp = 1e-8;
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

cyqlone::FanOCPStorage::Solution
get_solution_hpipm_tree(HPIPMTreeSolverData &solver_data) {
    cyqlone::FanOCPStorage::Solution fan_sol;

    const auto &data = *solver_data.qp_data;
    const auto &dim  = *data.dim;
    auto *qp_sol     = solver_data.qp_sol.get();

    const int num_branches = data.num_branches;
    const int horizon      = data.horizon;
    const int root         = 0;

    fan_sol.solutions.resize(
        static_cast<std::size_t>(num_branches));

    /*
     * Extract the shared root variables once.
     */
    std::vector<real_t> x0(
        static_cast<std::size_t>(dim.nx[root]));

    std::vector<real_t> u0(
        static_cast<std::size_t>(dim.nu[root]));

    d_tree_ocp_qp_sol_get_x(root, qp_sol, x0.data());

    if (dim.nu[root] > 0)
        d_tree_ocp_qp_sol_get_u(root, qp_sol, u0.data());

    /*
     * Root inequality multipliers are stacked branch-by-branch:
     *
     *     [mu_0^(0)]
     *     [mu_0^(1)]
     *     [   ...  ]
     *
     * because D0, lg0 and ug0 were vertically stacked in that order.
     */
    std::vector<real_t> root_lam_ug(
        static_cast<std::size_t>(dim.ng[root]));

    std::vector<real_t> root_lam_lg(
        static_cast<std::size_t>(dim.ng[root]));

    if (dim.ng[root] > 0) {
        d_tree_ocp_qp_sol_get_lam_ug(
            root, qp_sol, root_lam_ug.data());

        d_tree_ocp_qp_sol_get_lam_lg(
            root, qp_sol, root_lam_lg.data());
    }

    /*
     * The root-state bound multiplier is shared by all branches.
     *
     * This is the multiplier of x0 = x_init in the merged tree QP.
     */
    std::vector<real_t> root_lam_lbx(
        static_cast<std::size_t>(dim.nx[root]));

    std::vector<real_t> root_lam_ubx(
        static_cast<std::size_t>(dim.nx[root]));

    if (dim.nx[root] > 0) {
        d_tree_ocp_qp_sol_get_lam_lb(
            root, qp_sol, root_lam_lbx.data());

        d_tree_ocp_qp_sol_get_lam_ub(
            root, qp_sol, root_lam_ubx.data());
    }

    index_t root_ineq_offset = 0;

    for (int branch = 0; branch < num_branches; ++branch) {
        auto &branch_sol =
            fan_sol.solutions[static_cast<std::size_t>(branch)];

        /*
         * Compute the size of
         *
         * x0, u0, x1, u1, ..., xN.
         */
        std::size_t primal_count =
            static_cast<std::size_t>(dim.nx[root]) +
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

        /*
         * Copy the shared x0 and u0 into this branch solution.
         */
        std::copy(
            x0.begin(),
            x0.end(),
            primal_out);

        primal_out += dim.nx[root];

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

        /*
         * Inequality multiplier ordering:
         *
         * stage 0 constraints,
         * stage 1 constraints,
         * ...
         * terminal-stage constraints.
         */
        int ng_branch_total = 0;

        /*
         * Root ng is the sum over branches, so obtain the root
         * contribution from the original branch dimensions.
         *
         * If HPIPMTreeQPData stores branch_ng0, use that directly.
         */
        const int first_node = data.node_index[branch][1];

        /*
         * For your construction, all nonterminal stages of a branch
         * use the same ny. The first branch node therefore has the
         * same ng as the branch's original stage zero.
         */
        const int ng_branch_root =
            horizon > 1
                ? dim.ng[first_node]
                : static_cast<int>(
                      dim.ng[root] / num_branches);

        ng_branch_total += ng_branch_root;

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];
            ng_branch_total += dim.ng[node];
        }

        branch_sol.inequality_multipliers.resize(
            static_cast<std::size_t>(ng_branch_total));

        real_t *ineq_out =
            branch_sol.inequality_multipliers.data();

        /*
         * Extract this branch's block from the stacked root
         * inequality multipliers.
         *
         * Signed multiplier convention:
         *
         *     mu = mu_upper - mu_lower.
         */
        for (int i = 0; i < ng_branch_root; ++i) {
            const auto idx = static_cast<std::size_t>(
                root_ineq_offset + i);

            ineq_out[i] =
                root_lam_ug[idx] -
                root_lam_lg[idx];
        }

        ineq_out += ng_branch_root;
        root_ineq_offset += ng_branch_root;

        /*
         * Extract branch-specific inequality multipliers.
         */
        int ng_max = 0;

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];
            ng_max = std::max(ng_max, dim.ng[node]);
        }

        std::vector<real_t> lam_lg(
            static_cast<std::size_t>(ng_max));

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];
            const int ng   = dim.ng[node];

            if (ng == 0)
                continue;

            d_tree_ocp_qp_sol_get_lam_ug(
                node,
                qp_sol,
                ineq_out);

            d_tree_ocp_qp_sol_get_lam_lg(
                node,
                qp_sol,
                lam_lg.data());

            for (int i = 0; i < ng; ++i)
                ineq_out[i] -=
                    lam_lg[static_cast<std::size_t>(i)];

            ineq_out += ng;
        }

        BATMAT_ASSERT(
            ineq_out ==
            branch_sol.inequality_multipliers.data() +
                branch_sol.inequality_multipliers.size());

        /*
         * Equality multipliers:
         *
         * initial-state multiplier followed by one dynamics
         * multiplier for every branch edge.
         */
        std::size_t equality_count =
            static_cast<std::size_t>(dim.nx[root]);

        for (int stage = 1; stage <= horizon; ++stage) {
            const int node = data.node_index[branch][stage];

            equality_count +=
                static_cast<std::size_t>(dim.nx[node]);
        }

        branch_sol.equality_multipliers.resize(
            equality_count);

        real_t *eq_out =
            branch_sol.equality_multipliers.data();

        /*
         * This is the shared, aggregated root multiplier.
         *
         * Copying it into every branch is convenient, but it should
         * not be interpreted as a separately recovered multiplier
         * for each original branch initial-state constraint.
         */
        for (int i = 0; i < dim.nx[root]; ++i) {
            eq_out[i] =
                root_lam_lbx[static_cast<std::size_t>(i)] -
                root_lam_ubx[static_cast<std::size_t>(i)];
        }

        eq_out += dim.nx[root];

        /*
         * Each pi corresponds to the dynamics constraint on the
         * edge entering the branch node.
         */
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

    BATMAT_ASSERT(root_ineq_offset == dim.ng[root]);
    
    return fan_sol;
}
// TODO: Implement warm start for HPIPM tree solver.  The following code is commented out because HPIPM tree does,t provide any setters.
// void warm_start_hpipm_tree(HPIPMTreeSolverData &solver_data,
//                            std::span<const real_t> primal) {
//     const auto &data = *solver_data.qp_data;
//     const auto &dim  = *data.dim;
//     BATMAT_ASSERT(primal.size() == primal_size(data));

//     const real_t *in = primal.data();
//     d_tree_ocp_qp_sol_set_x(0, const_cast<real_t *>(in), solver_data.qp_sol.get());
//     in += dim.nx[0];
//     d_tree_ocp_qp_sol_set_u(0, const_cast<real_t *>(in), solver_data.qp_sol.get());
//     in += dim.nu[0];

//     for (int branch = 0; branch < data.num_branches; ++branch)
//         for (int stage = 1; stage <= data.horizon; ++stage) {
//             const int node = data.node_index[branch][stage];
//             d_tree_ocp_qp_sol_set_x(node, const_cast<real_t *>(in),
//                                      solver_data.qp_sol.get());
//             in += dim.nx[node];
//             if (dim.nu[node] > 0) {
//                 d_tree_ocp_qp_sol_set_u(node, const_cast<real_t *>(in),
//                                          solver_data.qp_sol.get());
//                 in += dim.nu[node];
//             }
//         }
// }



// =============================================================================
// Validation helpers
// =============================================================================

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

// =============================================================================
// BLASFEO packing helper
// =============================================================================

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

// =============================================================================
// ux offsets
//
// ux = [u; x; sl; su]
// =============================================================================

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

// =============================================================================
// lam/t offsets
//
// lam = [lb; lg; ub; ug; ls; us]
// t   = [lb; lg; ub; ug; ls; us]
// =============================================================================

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

// =============================================================================
// lam setters
//
// lam = [lb; lg; ub; ug; ls; us]
// =============================================================================

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

// =============================================================================
// t setters
//
// t = [lb; lg; ub; ug; ls; us]
// =============================================================================

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
void update_x0_hpipm_tree(cyqlone::FanOCPStorage &fan,
                          HPIPMTreeQPData &qp_data,
                          std::vector<cyqlone::LinearOCPStorage::Solution> &solution,
                          index_t branch) {
    const int b = static_cast<int>(branch);
    const auto &dim = *qp_data.dim;
    const int first_node = qp_data.node_index[b][1];    
    const real_t *x1 = solution[b].solution.data() + dim.nx[0] + dim.nu[0];
    d_tree_ocp_qp_set_lbx(0, const_cast<real_t *>(x1), qp_data.qp.get());
    d_tree_ocp_qp_set_ubx(0, const_cast<real_t *>(x1), qp_data.qp.get());

    for (auto &ocp : fan.ocps) {
        BATMAT_ASSERT(ocp.dim.nx == dim.nx[0]);
        std::ranges::copy_n(x1, dim.nx[0], ocp.b(0).data);
    }
}
