
#include <batmat/loop.hpp>
#include <guanaqo/io/csv.hpp>
#include <guanaqo/print.hpp>
#include <guanaqo/trace.hpp>
#include <cmath>
#include <fstream>

#include <format>

#include <iostream>
#include <numeric>

#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.hpp>
#include <cyqlone/qpalm/solver.hpp>
#include <cyqlone-version.h>

#include <cyqlone/conversion.hpp>
#include <cyqlone/cyqlone-storage.hpp>
#include <cyqlone/matio.hpp>
using cyqlone::index_t;
using cyqlone::real_t;
namespace qp = cyqlone::qpalm;
index_t cyq_get_num_proc() {
    int p = 8;
    if (const char *env_p = std::getenv("CI_JOB_CPU_LIMIT"))
        p = std::min(p, std::atoi(env_p));
    // floor to the nearest power of two
    std::cout << "Using " << p << " processors/threads\n";
    return static_cast<index_t>(std::bit_floor(static_cast<unsigned>(std::max(1, p))));
}
int main() try {
    auto matfp = cyqlone::open_mat("python/cmpc/ocp_data1024.mat");
    cyqlone::LinearOCPStorage ocp;
    cyqlone::read_from_mat(matfp.get(), "ocp", ocp);
    auto cocp          = cyqlone::CyqloneStorage<>::build(ocp);
    const bool verbose = true;
    auto &&backend     = qp::make_cyqpalm_backend<4>(cocp, {},
                                                        {.processors      = cyq_get_num_proc(),
                                                        .print_residuals = verbose,
                                                        .print_precision = 17,
                                                        .tricyqle_params = {.solve_method = cyqlone::SolveMethod::PCR}});
    qp::Solver<qp::CyQPALMBackend<4> *> qpalm{
        backend.get(),
        {.max_outer_iter                 = 400,
            .max_total_inner_iter           = 400,
            .tolerance                      = 1e-8,
            .dual_tolerance                 = 1e-8,
            .max_penalty_y                  = 1e7,
            .initial_penalty_y              = 1e-2,
            .verbose                        = verbose,
            .linesearch_include_multipliers = true},
    };

    auto status = qpalm();
    std::cout << "QPALM status: " << status << "\n";
    std::cout << "inner:   " << qpalm.stats->inner_iter << "\n"
                << "outer:   " << qpalm.stats->outer_iter << "\n"
                << "timings: " << qpalm.stats->timings.total << "\n";

    auto x = qpalm.get_solution(), λ = qpalm.get_equality_multipliers(),
        y = qpalm.get_inequality_multipliers();
    auto err = cocp.compute_kkt_error(ocp, x, y, λ);
    std::cout << "KKT error:\n"
            << "  stationarity:        " << err.stationarity << "\n"
            << "  inequality residual: " << err.inequality_residual << "\n"
            << "  equality residual:   " << err.equality_residual << "\n"
            << "  complementarity:     " << err.complementarity << std::endl;
    std::cout << std::sqrt(std::inner_product(x.begin(), x.end(), x.begin(), 0.0)) << "\n"; // print norm of solution
    std::filesystem::path filename = std::format("python/cmpc/results/data_{}.mat", ocp.dim.N_horiz);
    auto matfile                   = cyqlone::create_mat(filename);
    cyqlone::add_to_mat(matfile.get(), "ocp", ocp);
    cyqlone::add_to_mat(matfile.get(), "sol_x", x);
    cyqlone::add_to_mat(matfile.get(), "sol_lam", λ);
    cyqlone::add_to_mat(matfile.get(), "sol_y", y);
    std::cout << "Saved OCP and solution to " << filename << "\n";
    return 0;
} catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
}