#pragma once


#include <cyqlone/ocp.hpp>

#include <chrono>
#include <cstddef>
#include <memory>
#include <span>
#include <vector>

#include <hpipm_d_tree_ocp_qp.h>
#include <hpipm_d_tree_ocp_qp_dim.h>
#include <hpipm_d_tree_ocp_qp_ipm.h>
#include <hpipm_d_tree_ocp_qp_sol.h>
#include <hpipm_scenario_tree.h>
#pragma once




using real_t = double;


struct HPIPMTreeQPData {
    std::unique_ptr<std::byte[]> tree_mem;
    std::unique_ptr<struct tree> tree;

    std::unique_ptr<std::byte[]> dim_mem;
    std::unique_ptr<struct d_tree_ocp_qp_dim> dim;

    std::unique_ptr<std::byte[]> qp_mem;
    std::unique_ptr<struct d_tree_ocp_qp> qp;

    int num_branches{};
    int horizon{};

    // Indexed as node_index[branch][stage], stage in [0, horizon].
    // Stage zero maps to the common root node zero.
    std::vector<std::vector<int>> node_index;

    // Indexed as edge_index[branch][stage], stage in [1, horizon].
    std::vector<std::vector<int>> edge_index;
};

struct HPIPMTreeSolverData {
    std::shared_ptr<HPIPMTreeQPData> qp_data;

    std::unique_ptr<std::byte[]> qp_sol_mem;
    std::unique_ptr<struct d_tree_ocp_qp_sol> qp_sol;

    std::unique_ptr<std::byte[]> solver_arg_mem;
    std::unique_ptr<struct d_tree_ocp_qp_ipm_arg> arg;

    std::unique_ptr<std::byte[]> solver_mem;
    std::unique_ptr<struct d_tree_ocp_qp_ipm_ws> workspace;
};

/// Tree solution layout:
///   primal = [x_root, u_root,
///             branch 0: x_1, u_1, ..., x_N,
///             branch 1: x_1, u_1, ..., x_N, ...]
/// Terminal nodes have no control entry.
struct HPIPMTreeSolution {
    std::vector<cyqlone::real_t> primal;

    // Signed general-constraint multipliers, lam_ug - lam_lg, in node order.
    std::vector<cyqlone::real_t> inequality_multipliers;

    // Initial-state bound multiplier followed by edge dynamics multipliers.
    // Edge multipliers are stored in HPIPM edge order.
    std::vector<cyqlone::real_t> equality_multipliers;
};

struct HPIPMStats {
    int status;
    int iter;
    double max_res_stat;
    double max_res_eq;
    double max_res_ineq;
    double max_res_comp;
};
std::shared_ptr<HPIPMTreeQPData>
build_hpipm_tree_qp(const cyqlone::FanOCPStorage &fan);

std::shared_ptr<HPIPMTreeSolverData>
create_hpipm_tree_solver(std::shared_ptr<HPIPMTreeQPData> qp_data,
                         int warm_start, int mode = 0);

std::chrono::nanoseconds
solve_hpipm_tree(const HPIPMTreeQPData &qp_data,
                 HPIPMTreeSolverData &solver_data);

HPIPMStats get_stats_hpipm_tree(HPIPMTreeSolverData &solver_data);

cyqlone::FanOCPStorage::Solution get_solution_hpipm_tree(HPIPMTreeSolverData &solver_data);

void warm_start_hpipm_tree(HPIPMTreeSolverData &solver_data,
                           std::span<const cyqlone::real_t> primal);

/// Replace the common root state by the stage-one state of branch `branch`.
/// This is useful for receding-horizon simulation when one fan outcome is chosen.
void update_x0_hpipm_tree(cyqlone::FanOCPStorage &fan,
                          HPIPMTreeQPData &qp_data,
                          std::vector<cyqlone::LinearOCPStorage::Solution> &solution,
                          cyqlone::index_t branch);
void tree_ocp_qp_sol_set_u(
    int node,
    std::span<const double> u,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_x(
    int node,
    std::span<const double> x,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_sl(
    int node,
    std::span<const double> sl,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_su(
    int node,
    std::span<const double> su,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_ux(
    int node,
    std::span<const double> ux,
    d_tree_ocp_qp_sol &solution);

// =============================================================================
// Dynamics multiplier
//
// pi[edge] contains the multiplier associated with one tree edge.
//
// Under HPIPM's normal node/edge numbering:
//
//     edge = child_node - 1
//     size(pi[edge]) = nx[child_node]
// =============================================================================

void tree_ocp_qp_sol_set_pi(
    int edge,
    std::span<const double> pi,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_pi_for_node(
    int child_node,
    std::span<const double> pi,
    d_tree_ocp_qp_sol &solution);

// =============================================================================
// Inequality multipliers
//
// HPIPM layout:
//
//     lam[node] = [lb; lg; ub; ug; ls; us]
// =============================================================================

void tree_ocp_qp_sol_set_lam_lb(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_lam_lg(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_lam_ub(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_lam_ug(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_lam_ls(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_lam_us(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_lam(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

// =============================================================================
// Inequality slacks
//
// HPIPM layout:
//
//     t[node] = [lb; lg; ub; ug; ls; us]
// =============================================================================

void tree_ocp_qp_sol_set_t_lb(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_t_lg(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_t_ub(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_t_ug(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_t_ls(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_t_us(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void tree_ocp_qp_sol_set_t(
    int node,
    std::span<const double> value,
    d_tree_ocp_qp_sol &solution);

void shift_hpipm_tree_solution(
    HPIPMTreeSolverData &solver_data,
    cyqlone::real_t positive_floor = 1e-8);