#include "treehpipm.hpp"

#include <batmat/assume.hpp>
#include <guanaqo/mat-view.hpp>

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <memory>
#include <numeric>
#include <ranges>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using cyqlone::index_t;
using cyqlone::real_t;

namespace {

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

} // namespace

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
    guanaqo::MatrixView<real_t, index_t> R0 = {{.rows = nu, .cols = nu}};
    guanaqo::MatrixView< real_t, index_t> r0 = {{.rows = nu, .cols = 1}};
    guanaqo::MatrixView< real_t, index_t> q0 = {{.rows = nx, .cols = 1}};
    guanaqo::MatrixView<real_t, index_t> Q0 = {{.rows = nx, .cols = nx}};
    guanaqo::MatrixView<real_t, index_t> S0 = {{.rows = nu, .cols = nx}};


    guanaqo::MatrixView<real_t, index_t> D0 = {{.rows = ng_0, .cols = nu}};
    guanaqo::MatrixView<real_t, index_t> lg0 = {{.rows = ng_0, .cols = 1}};
    guanaqo::MatrixView<real_t, index_t> ug0 = {{.rows = ng_0, .cols = 1}};
    R0.set_constant(real_t{0});
    r0.set_constant(real_t{0});
    q0.set_constant(real_t{0});
    Q0.set_constant(real_t{0});
    S0.set_constant(real_t{0});

    index_t row_offset = 0;

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

    assert(row_offset == D0.rows);
    assert(row_offset == lg0.rows);
    assert(row_offset == ug0.rows);
    d_tree_ocp_qp_set_R(0, const_cast<real_t *>(compress_col_major(R0).data()), d.qp.get());
    d_tree_ocp_qp_set_r(0, const_cast<real_t *>(compress_col_major(r0).data()), d.qp.get());
    d_tree_ocp_qp_set_D(0, const_cast<real_t *>(compress_col_major(D0).data()), d.qp.get());
    d_tree_ocp_qp_set_lg(0, const_cast<real_t *>(compress_col_major(lg0).data()), d.qp.get());
    d_tree_ocp_qp_set_ug(0, const_cast<real_t *>(compress_col_major(ug0).data()), d.qp.get());
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
            d_tree_ocp_qp_set_lg(node,
                const_cast<real_t *>(ocp.b_min(stage).data), d.qp.get());
            d_tree_ocp_qp_set_ug(node,
                const_cast<real_t *>(ocp.b_max(stage).data), d.qp.get());

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
                         int warm_start) {
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
    double tol_comp = 1e-5;

    d_tree_ocp_qp_ipm_arg_set_default(hpipm_mode::SPEED, d.arg.get());
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

void update_x0_hpipm_tree(cyqlone::FanOCPStorage &fan,
                          HPIPMTreeQPData &qp_data,
                          const HPIPMTreeSolution &solution,
                          index_t branch) {
    BATMAT_ASSERT(branch >= 0 && branch < fan.num_branches());
    const int b = static_cast<int>(branch);
    const auto &dim = *qp_data.dim;
    const int first_node = qp_data.node_index[b][1];
    const std::size_t offset = branch_offset(qp_data, b);
    BATMAT_ASSERT(solution.primal.size() >=
                  offset + static_cast<std::size_t>(dim.nx[first_node]));

    const real_t *x1 = solution.primal.data() + offset;
    d_tree_ocp_qp_set_lbx(0, const_cast<real_t *>(x1), qp_data.qp.get());
    d_tree_ocp_qp_set_ubx(0, const_cast<real_t *>(x1), qp_data.qp.get());

    for (auto &ocp : fan.ocps) {
        BATMAT_ASSERT(ocp.dim.nx == dim.nx[0]);
        std::ranges::copy_n(x1, dim.nx[0], ocp.b(0).data);
    }
}
