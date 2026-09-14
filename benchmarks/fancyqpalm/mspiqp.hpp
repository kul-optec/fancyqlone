#pragma once

#include <cyqlone/ocp.hpp> // Replace with the header defining FanOCPStorage.
#include <piqp/piqp.hpp>

#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <chrono>
#include <memory>
#include <vector>

using cyqlone::index_t;
using cyqlone::real_t;

using PIQPSparseMatrix =
    Eigen::SparseMatrix<real_t, Eigen::ColMajor, int>;

using PIQPVector =
    Eigen::Matrix<real_t, Eigen::Dynamic, 1>;

struct PIQPStageOffset {
    int x = -1;
    int u = -1;
    int nx = 0;
    int nu = 0;
};

struct PIQPBranchLayout {
    // Stage zero is the common/root stage and is therefore not stored here.
    // Entries 1 ... horizon identify the branch-specific stages.
    std::vector<PIQPStageOffset> stages;

    // Dynamics rows for transitions 0->1, 1->2, ..., N-1->N.
    std::vector<int> dynamics_rows;

    // PIQP row for each original general constraint, or -1 if fully unbounded.
    std::vector<std::vector<int>> inequality_rows;
    std::vector<int> inequality_sizes;
};

struct PIQPFanQPData {
    int num_branches = 0;
    int horizon = 0;
    int nx = 0;
    int nu = 0;

    int root_x_offset = -1;
    int root_u_offset = -1;

    std::vector<PIQPBranchLayout> branches;

    PIQPSparseMatrix P;
    PIQPVector c;

    PIQPSparseMatrix A;
    PIQPVector b;

    PIQPSparseMatrix G;
    PIQPVector h_lower;
    PIQPVector h_upper;

    PIQPVector z_lower;
    PIQPVector z_upper;
};

struct PIQPFanSolverData {
    std::shared_ptr<PIQPFanQPData> qp_data;
    piqp::SparseSolver<real_t> solver;
    piqp::Status status = piqp::Status::PIQP_UNSOLVED;
};

struct PIQPStats {
    piqp::Status status = piqp::Status::PIQP_UNSOLVED;
    int iter = 0;
    real_t primal_objective = 0;
    real_t run_time = 0;
};

std::shared_ptr<PIQPFanQPData>
build_piqp_fan_qp(const cyqlone::FanOCPStorage &fan);

std::shared_ptr<PIQPFanSolverData>
create_piqp_fan_solver(
    std::shared_ptr<PIQPFanQPData> qp_data);

std::chrono::nanoseconds
solve_piqp_fan(PIQPFanSolverData &solver_data);

PIQPStats
get_stats_piqp_fan(const PIQPFanSolverData &solver_data);

cyqlone::FanOCPStorage::Solution
get_solution_piqp_fan(const PIQPFanSolverData &solver_data);

void update_x0_piqp_fan(
    cyqlone::FanOCPStorage &fan,
    PIQPFanSolverData &solver_data,
    const std::vector<cyqlone::LinearOCPStorage::Solution> &solution,
    index_t selected_branch);
