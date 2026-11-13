#include <interfaces/treeqp_cpp/treeqp_cpp_interface.hpp>
#include <treeqp/src/hpipm_tree.h>

#include <cmath>
#include <cstdlib>
#include <memory>

int main() {
    // min (x0^2 + u0^2 + x1^2)/2 - x1, subject to x1 = x0 + u0, x1 <= 0.2.
    TreeQp qp({1, 1}, {1, 0}, {1, 0}, {1, 0});
    for (int i = 0; i < 2; ++i) {
        qp.SetMatrixColMajor("Q", {1.0}, i);
        qp.SetVector("q", {i == 0 ? 0.0 : -1.0}, i);
        qp.SetVector("xmin", {-10.0}, i);
        qp.SetVector("xmax", {i == 0 ? 10.0 : 0.2}, i);
    }
    qp.SetMatrixColMajor("R", {1.0}, 0);
    qp.SetMatrixColMajor("S", {0.0}, 0);
    qp.SetVector("r", {0.0}, 0);
    qp.SetVector("umin", {-10.0}, 0);
    qp.SetVector("umax", {10.0}, 0);
    qp.SetMatrixColMajor("A", {1.0}, 0);
    qp.SetMatrixColMajor("B", {1.0}, 0);
    qp.SetVector("b", {0.0}, 0);
    double one = 1.0, zero = 0.0, lower = -10.0, upper = 10.0;
    tree_qp_in_set_node_general_constraints(&one, &zero, &lower, &upper, &qp.QpIn, 0);

    auto check_solution = [&]() {
        double x, u;
        tree_qp_out_get_node_x(&x, &qp.QpOut, 1);
        tree_qp_out_get_node_u(&u, &qp.QpOut, 0);
        return std::isfinite(x) && std::isfinite(u) &&
               std::abs(x - 0.2) < 1e-7 && std::abs(u - 0.1) < 1e-7;
    };

    // Exercises both QProblem (root) and QProblemB (leaf), including the fork fixes.
    TdunesSolver solver(&qp);
    if (solver.TdunesOpts.qp_solver[0] != TREEQP_QPOASES_SOLVER ||
        solver.Solve(&qp) != TREEQP_OPTIMAL_SOLUTION_FOUND || !check_solution())
        return 1;

    using Buffer = std::unique_ptr<void, decltype(&std::free)>;
    treeqp_hpipm_opts_t opts;
    Buffer opts_mem(std::malloc(treeqp_hpipm_opts_calculate_size(qp.NumNodes)), &std::free);
    if (!opts_mem) return 2;
    treeqp_hpipm_opts_create(qp.NumNodes, &opts, opts_mem.get());
    treeqp_hpipm_opts_set_default(qp.NumNodes, &opts);
    treeqp_hpipm_workspace work;
    Buffer work_mem(std::malloc(treeqp_hpipm_calculate_size(&qp.QpIn, &opts)), &std::free);
    if (!work_mem) return 3;
    treeqp_hpipm_create(&qp.QpIn, &opts, &work, work_mem.get());
    if (treeqp_hpipm_solve(&qp.QpIn, &qp.QpOut, &opts, &work) !=
            TREEQP_OPTIMAL_SOLUTION_FOUND || !check_solution())
        return 4;
}
