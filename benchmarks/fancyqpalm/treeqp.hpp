#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include <cmath>
#include <cyqlone/ocp.hpp>

// Adjust this include path if your treeQP package exports it differently.
#include <treeqp_cpp_interface/treeqp_cpp_interface.hpp>

struct TreeQpBoundMapping {
    enum class Kind {
        State,
        Input,
    };

    Kind kind = Kind::State;
    int index = -1;
};

struct TreeQpData {
    int num_branches = 0;
    int horizon = 0;

    std::vector<int> nx;
    std::vector<int> nu;
    std::vector<int> nc;
    std::vector<int> nk;
    bool native_bounds = false;
    bool shared_root_constraints = true;
    std::vector<double> initial_state;
    std::vector<double> root_xmin;
    std::vector<double> root_xmax;
    std::vector<std::vector<int>> branch_nc;
    std::vector<std::vector<std::vector<TreeQpBoundMapping>>> bound_mapping;
    std::vector<std::vector<int>> node_index;
    std::vector<std::vector<int>> edge_index;

    // Owns QpIn, QpOut, and their associated treeQP storage.
    std::unique_ptr<TreeQp> qp;

    TreeQpData() = default;
    ~TreeQpData() = default;

    TreeQpData(const TreeQpData &) = delete;
    TreeQpData &operator=(const TreeQpData &) = delete;

    TreeQpData(TreeQpData &&) noexcept = default;
    TreeQpData &operator=(TreeQpData &&) noexcept = default;
};

struct TreeQpSolverData {
    std::shared_ptr<TreeQpData> qp_data;

    // Owns the TDUNES options and workspace.
    std::unique_ptr<TdunesSolver> solver;
    std::vector<double> zero_dual;

    int last_status = -1;

    TreeQpSolverData() = default;
    ~TreeQpSolverData() = default;

    TreeQpSolverData(const TreeQpSolverData &) = delete;
    TreeQpSolverData &operator=(const TreeQpSolverData &) = delete;

    TreeQpSolverData(TreeQpSolverData &&) noexcept = default;
    TreeQpSolverData &operator=(TreeQpSolverData &&) noexcept = default;
};

struct TreeQpStats {
    int status = -1;
    int iterations = 0;
    double residual = 0.0;
};

std::shared_ptr<TreeQpData>
build_tree_qp(const cyqlone::FanOCPStorage &fan, bool clipping = true);

std::shared_ptr<TreeQpSolverData>
create_tree_qp_solver(
    std::shared_ptr<TreeQpData> qp_data,
    int max_iterations,
    double tolerance
);

std::chrono::nanoseconds
solve_tree_qp(
    const TreeQpData &qp_data,
    TreeQpSolverData &solver_data,
    bool cold_start = false
);

TreeQpStats
get_stats_tree_qp(TreeQpSolverData &solver_data);

cyqlone::FanOCPStorage::Solution
get_solution_tree_qp(TreeQpSolverData &solver_data);

void update_x0_tree_qp(
    cyqlone::FanOCPStorage &fan,
    TreeQpData &qp_data,
    const std::vector<cyqlone::LinearOCPStorage::Solution> &solution,
    cyqlone::index_t branch
);
