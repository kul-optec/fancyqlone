#include <cyqlone/conversion.hpp>
#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.hpp>
#include <cyqlone/qpalm/example-problems/csv.hpp>
#include <cyqlone/qpalm/example-problems/platooning.hpp>
#include <cyqlone/qpalm/solver.hpp>
#include <cyqlone/tracing.hpp>
#include "cyqlone/cyqlone-storage.hpp"
#include "cyqlone/fan-cyqlone.hpp"

#include "cyqlone/matio.hpp"
#include "cyqlone/ocp.hpp"
#include <gtest/gtest.h>
#include <cyqlone-version.h>
#include <fstream>

#include <batmat/loop.hpp>
#include <guanaqo/io/csv.hpp>
#include <guanaqo/print.hpp>
#include <guanaqo/trace.hpp>
#include <iostream>
#include <vector>

#include <cyqlone/conversion.hpp>
using cyqlone::index_t;
using cyqlone::real_t;
using StorageOrder = cyqlone::StorageOrder;

namespace qp = cyqlone::qpalm;
index_t cyq_get_num_proc();

#include <fstream>

#include <iostream>

#include <cmath>
#include <cstddef>
#include <iostream>
#include <string_view>
#include <vector>
#if GUANAQO_WITH_TRACING
#include <filesystem>
#include <fstream>
#endif
#include <cmath>
#include <span>
#include <vector>

inline void approx(std::span<const double> a, std::span<const double> b, double tol) {
    EXPECT_TRUE(a.size() == b.size());
    for (std::size_t i = 0; i < a.size(); ++i)
        EXPECT_NEAR(a[i], b[i], tol * std::fabs(b[i]));
}

inline void is_zero(std::span<const double> a, double tol) {
    for (double v : a)
        EXPECT_NEAR(v, 0.0, tol);
}

void compare_combined_normal(std::span<const double> combined, std::span<const double> normal,
                             std::size_t N, std::size_t nu, std::span<const std::size_t> nx,
                             double tol = 1e-9) {
    const std::size_t B = nx.size();

    std::vector<std::size_t> x_off(B + 1, 0), base(B, 0);
    for (std::size_t j = 0; j < B; ++j)
        x_off[j + 1] = x_off[j] + nx[j];

    const std::size_t stage_size = B * nu + x_off[B];
    base[0]                      = 0;
    std::size_t off              = N * (nu + nx[0]);
    for (std::size_t j = 1; j < B; ++j) {
        base[j] = off;
        off += nx[j] + (N - 1) * (nu + nx[j]);
    }

    for (std::size_t k = 0; k < N; ++k) {
        const std::size_t ck = k * stage_size;

        for (std::size_t j = 0; j < B; ++j) {
            auto u = combined.subspan(ck + j * nu, nu);
            auto x = combined.subspan(ck + B * nu + x_off[j], nx[j]);

            if (j == 0) {
                std::size_t n = k * (nu + nx[0]);
                approx(u, normal.subspan(n, nu), tol);
                approx(x, normal.subspan(n + nu, nx[0]), tol);
            } else if (k == 0) {
                is_zero(u, tol); // u0j missing in normal
                approx(x, normal.subspan(base[j], nx[j]), tol);
            } else {
                std::size_t n = base[j] + nx[j] + (k - 1) * (nu + nx[j]);
                approx(u, normal.subspan(n, nu), tol);
                approx(x, normal.subspan(n + nu, nx[j]), tol);
            }
        }
    }
}

// TEST(QPALM, cyqlonefan) {
//     index_t num_branches = 2;
//     index_t N            = 16;
//     std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);
//     for (index_t i = 0; i < num_branches; ++i) {
//         auto filename = std::format("python/cmpc/ocp_data{}_{}.mat", N, i);

//         cyqlone::LinearOCPStorage ocp_fan;
//         auto matfp = cyqlone::open_mat(filename);
//         cyqlone::read_from_mat(matfp.get(), "ocp", ocp_fan);

//         ocps[i] = ocp_fan;
//         std::cout << "Loaded OCP data from " << filename << " with N=" << ocp_fan.dim.N_horiz
//                   << ", nu=" << ocp_fan.dim.nu << ", ny=" << ocp_fan.dim.ny << "\n";
//     }
//     std::cout << cyq_get_num_proc() << " processors detected\n";
//     cyqlone::FanOCPStorage fan_ocp{.ocps    = ocps,
//                                    .R0      = ocps[0].R(0),
//                                    .r0      = ocps[0].r(0),
//                                    .D0      = ocps[0].D(0),
//                                    .b_min_0 = ocps[0].b_min(0),
//                                    .b_max_0 = ocps[0].b_max(0)};
//     auto cocp          = cyqlone::FanCyqloneStorage<>::build(fan_ocp, 0);
//     const bool verbose = true;
//     auto &&backend =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>>(
//             cocp, {},
//             {
//                 .processors      = 2,
//                 .print_residuals = verbose,
//                 .print_precision = 17,
//                 .tricyqle_params = {.solve_method = cyqlone::SolveMethod::None},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>> *> qpalm{
//         backend.get(),
//         {.max_outer_iter       = 1,
//          .max_total_inner_iter = 1,
//          .tolerance            = 1e-6,
//          .verbose              = verbose,
//          .detailed_stats       = verbose},
//     };

//     for (index_t i = 0; !verbose && i < 0; ++i) {
//         auto status = qpalm(); // warm up
//         EXPECT_EQ(status, qp::SolverStatus::Converged);
//     }

//     auto status = qpalm();
//     EXPECT_EQ(status, qp::SolverStatus::Converged);

// #if GUANAQO_WITH_TRACING
//     std::cout << save_trace("test-FanCyQpalm.csv") << "\n\n";
// #endif

//     std::cout << "inner:   " << qpalm.stats->inner_iter << "\n"
//               << "outer:   " << qpalm.stats->outer_iter << "\n"
//               << "timings: " << qpalm.stats->timings.total << "\n";

//     std::ofstream solution{"solution-fan-cyqpalm.csv"};
//     auto x = qpalm.get_solution(), λ = qpalm.get_equality_multipliers(),
//          y = qpalm.get_inequality_multipliers();
//     guanaqo::print_csv(solution, std::span{x});
//     guanaqo::print_csv(solution, std::span{λ});
//     guanaqo::print_csv(solution, std::span{y});

//     //// check with combined solution from all branches
//     auto filename = std::format("python/cmpc/ocp_data{}_combined.mat", N);

//     cyqlone::LinearOCPStorage ocp_combined;
//     auto matfp = cyqlone::open_mat(filename);
//     cyqlone::read_from_mat(matfp.get(), "ocp", ocp_combined);
//     auto cocp_combined = cyqlone::CyqloneStorage<>::build(ocp_combined);
//     auto &&backend_combined =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>>(
//             cocp_combined, {},
//             {
//                 .processors      = 1,
//                 .print_residuals = verbose,
//                 .print_precision = 17,
//                 .tricyqle_params = {.solve_method = cyqlone::SolveMethod::PCR},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>> *>
//         qpalm_combined{
//             backend_combined.get(),
//             {.max_outer_iter       = 1,
//              .max_total_inner_iter = 1,
//              .tolerance            = 1e-6,
//              .verbose              = verbose,
//              .detailed_stats       = verbose},
//         };

//     for (index_t i = 0; !verbose && i < 0; ++i) {
//         auto status_combined = qpalm_combined(); // warm up
//         EXPECT_EQ(status_combined, qp::SolverStatus::Converged);
//     }

//     auto status_combined = qpalm_combined();
//     EXPECT_EQ(status_combined, qp::SolverStatus::Converged);

//     std::cout << "inner:   " << qpalm_combined.stats->inner_iter << "\n"
//               << "outer:   " << qpalm_combined.stats->outer_iter << "\n"
//               << "timings: " << qpalm_combined.stats->timings.total << "\n";

//     auto x_combined = qpalm_combined.get_solution(),
//          λ_combined = qpalm_combined.get_equality_multipliers(),
//          y_combined = qpalm_combined.get_inequality_multipliers();
//     guanaqo::print_csv(solution, std::span{x_combined});
//     guanaqo::print_csv(solution, std::span{λ_combined});
//     guanaqo::print_csv(solution, std::span{y_combined});

//     std::vector<std::size_t> nx;
//     nx.reserve(ocps.size());

//     for (const auto &ocp : ocps) {
//         nx.push_back(ocp.dim.nx);
//     }

//     compare_combined_normal(x_combined, x, N, ocps[0].dim.nu, nx, 1e-5);
//     compare_combined_normal(λ_combined, λ, N, 0, nx, 1e-5);
// }
// TEST(QPALM, with_inequality_1iter) {
//     index_t num_branches = 2;
//     index_t N            = 32;
//     std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);
//     for (index_t i = 0; i < num_branches; ++i) {
//         auto filename = std::format("python/cmpc/ocp_data_constr{}_{}.mat", N, i);

//         cyqlone::LinearOCPStorage ocp_fan;
//         auto matfp = cyqlone::open_mat(filename);
//         cyqlone::read_from_mat(matfp.get(), "ocp", ocp_fan);

//         ocps[i] = ocp_fan;
//         guanaqo::print_python(std::cout << "x(0) = ", ocp_fan.b(0), "\n");
//         std::cout << "Loaded OCP data from " << filename << " with N=" << ocp_fan.dim.N_horiz
//                   << ", nu=" << ocp_fan.dim.nu << ", ny=" << ocp_fan.dim.ny << "\n";
//     }
//     std::cout << cyq_get_num_proc() << " processors detected\n";
//     cyqlone::FanOCPStorage fan_ocp{.ocps    = ocps,
//                                    .R0      = ocps[0].R(0),
//                                    .r0      = ocps[0].r(0),
//                                    .D0      = ocps[0].D(0),
//                                    .b_min_0 = ocps[0].b_min(0),
//                                    .b_max_0 = ocps[0].b_max(0)};
//     auto cocp          = cyqlone::FanCyqloneStorage<>::build(fan_ocp, ocps[0].D(0).cols);
//     const bool verbose = true;
//     auto &&backend =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>>(
//             cocp, {},
//             {
//                 .processors             = cyq_get_num_proc(),
//                 .print_residuals        = verbose,
//                 .print_precision        = 17,
//                 .changing_constr_factor = 0,
//                 .max_update_count       = 0,
//                 .tricyqle_params        = {.solve_method = cyqlone::SolveMethod::None},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>> *> qpalm{
//         backend.get(),
//         {.max_outer_iter = 1, .max_total_inner_iter = 1, .tolerance = 1e-6, .verbose = verbose},
//     };

//     auto status = qpalm();
//     std::cout << "inner:   " << qpalm.stats->inner_iter << "\n"
//               << "outer:   " << qpalm.stats->outer_iter << "\n"
//               << "timings: " << qpalm.stats->timings.total << "\n";

//     std::ofstream solution{"solution-fan-cyqpalm.csv"};
//     auto x = qpalm.get_solution(), λ = qpalm.get_equality_multipliers(),
//          y = qpalm.get_inequality_multipliers();
//     //// check with combined solution from all branches
//     auto filename = std::format("python/cmpc/ocp_data{}_combined_constr.mat", N);

//     cyqlone::LinearOCPStorage ocp_combined;
//     auto matfp = cyqlone::open_mat(filename);
//     cyqlone::read_from_mat(matfp.get(), "ocp", ocp_combined);
//     auto cocp_combined = cyqlone::CyqloneStorage<>::build(ocp_combined);
//     auto &&backend_combined =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>>(
//             cocp_combined, {},
//             {
//                 .processors      = cyq_get_num_proc(),
//                 .print_residuals = verbose,
//                 .print_precision = 17,
//                 .tricyqle_params = {.solve_method = cyqlone::SolveMethod::PCR},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>> *>
//         qpalm_combined{
//             backend_combined.get(),
//             {.max_outer_iter       = 1,
//              .max_total_inner_iter = 1,
//              .tolerance            = 1e-6,
//              .verbose              = verbose,
//              .detailed_stats       = verbose},
//         };

//     auto status_combined = qpalm_combined();

//     std::cout << "inner:   " << qpalm_combined.stats->inner_iter << "\n"
//               << "outer:   " << qpalm_combined.stats->outer_iter << "\n"
//               << "timings: " << qpalm_combined.stats->timings.total << "\n";

//     auto x_combined = qpalm_combined.get_solution(),
//          λ_combined = qpalm_combined.get_equality_multipliers(),
//          y_combined = qpalm_combined.get_inequality_multipliers();
//     std::vector<std::size_t> nx;
//     nx.reserve(ocps.size());

//     for (const auto &ocp : ocps) {
//         nx.push_back(ocp.dim.nx);
//     }
//     compare_combined_normal(x_combined, x, N, ocps[0].dim.nu, nx, 1e-5);
//     compare_combined_normal(λ_combined, λ, N, 0, nx, 1e-5);
//     guanaqo::print_csv(solution, std::span{y_combined});
//     guanaqo::print_csv(solution, std::span{y});
// }

// TEST(QPALM, with_inequality_2iter) {
//     index_t num_branches = 2;
//     index_t N            = 32;
//     std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);
//     for (index_t i = 0; i < num_branches; ++i) {
//         auto filename = std::format("python/cmpc/ocp_data_constr{}_{}.mat", N, i);

//         cyqlone::LinearOCPStorage ocp_fan;
//         auto matfp = cyqlone::open_mat(filename);
//         cyqlone::read_from_mat(matfp.get(), "ocp", ocp_fan);

//         ocps[i] = ocp_fan;
//         guanaqo::print_python(std::cout << "x(0) = ", ocp_fan.b(0), "\n");
//         std::cout << "Loaded OCP data from " << filename << " with N=" << ocp_fan.dim.N_horiz
//                   << ", nu=" << ocp_fan.dim.nu << ", ny=" << ocp_fan.dim.ny << "\n";
//     }
//     std::cout << cyq_get_num_proc() << " processors detected\n";
//     cyqlone::FanOCPStorage fan_ocp{.ocps    = ocps,
//                                    .R0      = ocps[0].R(0),
//                                    .r0      = ocps[0].r(0),
//                                    .D0      = ocps[0].D(0),
//                                    .b_min_0 = ocps[0].b_min(0),
//                                    .b_max_0 = ocps[0].b_max(0)};
//     auto cocp          = cyqlone::FanCyqloneStorage<>::build(fan_ocp, ocps[0].D(0).cols);
//     const bool verbose = true;
//     auto &&backend =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>>(
//             cocp, {},
//             {
//                 .processors             = 2,
//                 .print_residuals        = verbose,
//                 .print_precision        = 17,
//                 .changing_constr_factor = 0,
//                 .max_update_count       = 0,
//                 .tricyqle_params        = {.solve_method = cyqlone::SolveMethod::None},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>> *> qpalm{
//         backend.get(),
//         {.max_outer_iter = 10, .max_total_inner_iter = 2, .tolerance = 1e-6, .verbose = verbose},
//     };

//     auto status = qpalm();
//     std::cout << "inner:   " << qpalm.stats->inner_iter << "\n"
//               << "outer:   " << qpalm.stats->outer_iter << "\n"
//               << "timings: " << qpalm.stats->timings.total << "\n";

//     std::ofstream solution{"solution-fan-cyqpalm.csv"};
//     auto x = qpalm.get_solution(), λ = qpalm.get_equality_multipliers(),
//          y = qpalm.get_inequality_multipliers();
//     //// check with combined solution from all branches
//     auto filename = std::format("python/cmpc/ocp_data{}_combined_constr.mat", N);

//     cyqlone::LinearOCPStorage ocp_combined;
//     auto matfp = cyqlone::open_mat(filename);
//     cyqlone::read_from_mat(matfp.get(), "ocp", ocp_combined);
//     auto cocp_combined = cyqlone::CyqloneStorage<>::build(ocp_combined);
//     auto &&backend_combined =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>>(
//             cocp_combined, {},
//             {
//                 .processors      = 1,
//                 .print_residuals = verbose,
//                 .print_precision = 17,
//                 .tricyqle_params = {.solve_method = cyqlone::SolveMethod::PCR},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>> *>
//         qpalm_combined{
//             backend_combined.get(),
//             {.max_outer_iter       = 10,
//              .max_total_inner_iter = 2,
//              .tolerance            = 1e-6,
//              .verbose              = verbose,
//              .detailed_stats       = verbose},
//         };

//     auto status_combined = qpalm_combined();
//     std::cout << "inner:   " << qpalm_combined.stats->inner_iter << "\n"
//               << "outer:   " << qpalm_combined.stats->outer_iter << "\n"
//               << "timings: " << qpalm_combined.stats->timings.total << "\n";

//     auto x_combined = qpalm_combined.get_solution(),
//          λ_combined = qpalm_combined.get_equality_multipliers(),
//          y_combined = qpalm_combined.get_inequality_multipliers();
//     std::vector<std::size_t> nx;
//     nx.reserve(ocps.size());

//     for (const auto &ocp : ocps) {
//         nx.push_back(ocp.dim.nx);
//     }
//     // compare_combined_normal(x_combined, x, N, ocps[0].dim.nu, nx, 1e-5);
//     // compare_combined_normal(λ_combined, λ, N, 0, nx, 1e-5);
// }
// TEST(QPALM, with_inequality) {
//     index_t num_branches = 2;
//     index_t N            = 32;
//     std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);
//     for (index_t i = 0; i < num_branches; ++i) {
//         auto filename = std::format("python/cmpc/ocp_data_constr{}_{}.mat", N, i);

//         cyqlone::LinearOCPStorage ocp_fan;
//         auto matfp = cyqlone::open_mat(filename);
//         cyqlone::read_from_mat(matfp.get(), "ocp", ocp_fan);

//         ocps[i] = ocp_fan;
//         guanaqo::print_python(std::cout << "x(0) = ", ocp_fan.b(0), "\n");
//         std::cout << "Loaded OCP data from " << filename << " with N=" << ocp_fan.dim.N_horiz
//                   << ", nu=" << ocp_fan.dim.nu << ", ny=" << ocp_fan.dim.ny << "\n";
//     }
//     std::cout << cyq_get_num_proc() << " processors detected\n";
//     cyqlone::FanOCPStorage fan_ocp{.ocps    = ocps,
//                                    .R0      = ocps[0].R(0),
//                                    .r0      = ocps[0].r(0),
//                                    .D0      = ocps[0].D(0),
//                                    .b_min_0 = ocps[0].b_min(0),
//                                    .b_max_0 = ocps[0].b_max(0)};
//     auto cocp          = cyqlone::FanCyqloneStorage<>::build(fan_ocp, ocps[0].D(0).cols);
//     const bool verbose = false;
//     auto &&backend =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>>(
//             cocp, {},
//             {
//                 .processors             = cyq_get_num_proc(),
//                 .print_residuals        = verbose,
//                 .print_precision        = 17,
//                 .changing_constr_factor = 0,
//                 .max_update_count       = 0,
//                 .tricyqle_params        = {.solve_method = cyqlone::SolveMethod::None},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>> *> qpalm{
//         backend.get(),
//         {.max_outer_iter       = 200,
//          .max_total_inner_iter = 1000,
//          .tolerance            = 1e-6,
//          .verbose              = verbose},
//     };

// #if GUANAQO_WITH_TRACING
//     for (index_t i = 0; !verbose && i < 50; ++i)
//         qpalm(); // warm up
//     init_trace();
// #endif

//     auto status = qpalm();
//     EXPECT_EQ(status, qp::SolverStatus::Converged);

// #if GUANAQO_WITH_TRACING
//     std::cout << save_trace("test-FanCyQpalm.csv") << "\n\n";
// #endif

//     std::cout << "inner:   " << qpalm.stats->inner_iter << "\n"
//               << "outer:   " << qpalm.stats->outer_iter << "\n"
//               << "timings: " << qpalm.stats->timings.total << "\n";

//     std::ofstream solution{"solution-fan-cyqpalm.csv"};
//     auto x = qpalm.get_solution(), λ = qpalm.get_equality_multipliers(),
//          y = qpalm.get_inequality_multipliers();
//     guanaqo::print_csv(solution, std::span{x});
//     guanaqo::print_csv(solution, std::span{λ});
//     guanaqo::print_csv(solution, std::span{y});

//     //// check with combined solution from all branches
//     auto filename = std::format("python/cmpc/ocp_data{}_combined_constr.mat", N);

//     cyqlone::LinearOCPStorage ocp_combined;
//     auto matfp = cyqlone::open_mat(filename);
//     cyqlone::read_from_mat(matfp.get(), "ocp", ocp_combined);
//     auto cocp_combined = cyqlone::CyqloneStorage<>::build(ocp_combined);
//     auto &&backend_combined =
//         qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>>(
//             cocp_combined, {},
//             {
//                 .processors      = cyq_get_num_proc(),
//                 .print_residuals = verbose,
//                 .print_precision = 17,
//                 .tricyqle_params = {.solve_method = cyqlone::SolveMethod::PCR},
//             });
//     qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::CyqloneSolver<4>> *>
//         qpalm_combined{
//             backend_combined.get(),
//             {.max_outer_iter       = 200,
//              .max_total_inner_iter = 1000,
//              .tolerance            = 1e-6,
//              .verbose              = verbose,
//              .detailed_stats       = verbose},
//         };

//     auto status_combined = qpalm_combined();
//     EXPECT_EQ(status_combined, qp::SolverStatus::Converged);

//     std::cout << "inner:   " << qpalm_combined.stats->inner_iter << "\n"
//               << "outer:   " << qpalm_combined.stats->outer_iter << "\n"
//               << "timings: " << qpalm_combined.stats->timings.total << "\n";

//     auto x_combined = qpalm_combined.get_solution(),
//          λ_combined = qpalm_combined.get_equality_multipliers(),
//          y_combined = qpalm_combined.get_inequality_multipliers();
//     std::vector<std::size_t> nx;
//     nx.reserve(ocps.size());

//     for (const auto &ocp : ocps) {
//         nx.push_back(ocp.dim.nx);
//     }
//     compare_combined_normal(x_combined, x, N, ocps[0].dim.nu, nx, 1e-12);
//     compare_combined_normal(λ_combined, λ, N, 0, nx, 1e-12);
// }

cyqlone::LinearOCPStorage combine_branches_0(std::span<const cyqlone::LinearOCPStorage> ocps) {
    BATMAT_ASSERT(!ocps.empty());
    auto fld_max = [](index_t(cyqlone::OCPDim::*m)) {
        return [m](index_t acc, const auto &ocp) { return std::max(acc, ocp.dim.*m); };
    };
    auto fld_sum = [](index_t(cyqlone::OCPDim::*m)) {
        return [m](index_t acc, const auto &ocp) { return acc + ocp.dim.*m; };
    };
    cyqlone::OCPDim dim{
        .N_horiz = std::ranges::fold_left(ocps, index_t{0}, fld_max(&cyqlone::OCPDim::N_horiz)),
        .nx      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::nx)),
        .nu      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::nu)),
        .ny      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::ny)),
        .ny_N    = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&cyqlone::OCPDim::ny_N)),
    }; // TODO: this is a bit redundant, since x(0) and u(0) need to have consistent dimensions
    cyqlone::LinearOCPStorage combined_ocp(dim);

    index_t nx_offset = 0, nu_offset = 0, ny_offset = 0, ny_N_offset = 0;
    { // Take cost of the first stage from the first OCP (there is only one x(0) and one u(0))
        const auto &ocp = ocps.front();
        // combined_ocp.b(0).top_rows(ocp.dim.nx) = ocp.b(0); // x0
        combined_ocp.Q(0).block(0, 0, ocp.dim.nx, ocp.dim.nx) += ocp.Q(0);
        combined_ocp.R(0).block(0, 0, ocp.dim.nu, ocp.dim.nu) += ocp.R(0);
        combined_ocp.S(0).block(0, 0, ocp.dim.nu, ocp.dim.nx) += ocp.S(0);
        combined_ocp.S_trans(0).block(0, 0, ocp.dim.nx, ocp.dim.nu) += ocp.S_trans(0);
        combined_ocp.q(0).block(0, 0, ocp.dim.nx, 1) += ocp.q(0);
        combined_ocp.r(0).block(0, 0, ocp.dim.nu, 1) += ocp.r(0);
    }
    // Later stages can diverge for the different OCPs, so these all become diagonal matrices,
    // except for the coupling from the first stage
    for (const auto &ocp : ocps) {
        const index_t N = ocp.dim.N_horiz;
        // Copy dynamics
        combined_ocp.A(0).block(nx_offset, nx_offset, ocp.dim.nx, ocp.dim.nx) = ocp.A(0);
        combined_ocp.B(0).block(nx_offset, 0, ocp.dim.nx, ocp.dim.nu)         = ocp.B(0);
        for (index_t i = 1; i < N; ++i) {
            combined_ocp.A(i).block(nx_offset, nx_offset, ocp.dim.nx, ocp.dim.nx) = ocp.A(i);
            combined_ocp.B(i).block(nx_offset, nu_offset, ocp.dim.nx, ocp.dim.nu) = ocp.B(i);
            combined_ocp.b(i).block(nx_offset, 0, ocp.dim.nx, 1)                  = ocp.b(i);
        }
        combined_ocp.b(N).block(nx_offset, 0, ocp.dim.nx, 1) = ocp.b(N);
        combined_ocp.b(0).block(nx_offset, 0, ocp.dim.nx, 1) = ocp.b(0); // x0

        // Copy constraints
        combined_ocp.C(0).block(ny_offset, 0, ocp.dim.ny, ocp.dim.nx) = ocp.C(0);
        combined_ocp.D(0).block(ny_offset, 0, ocp.dim.ny, ocp.dim.nu) = ocp.D(0);
        combined_ocp.b_min(0).block(ny_offset, 0, ocp.dim.ny, 1)      = ocp.b_min(0);
        combined_ocp.b_max(0).block(ny_offset, 0, ocp.dim.ny, 1)      = ocp.b_max(0);
        for (index_t i = 1; i < N; ++i) {
            combined_ocp.C(i).block(ny_offset, nx_offset, ocp.dim.ny, ocp.dim.nx) = ocp.C(i);
            combined_ocp.D(i).block(ny_offset, nu_offset, ocp.dim.ny, ocp.dim.nu) = ocp.D(i);
            combined_ocp.b_min(i).block(ny_offset, 0, ocp.dim.ny, 1)              = ocp.b_min(i);
            combined_ocp.b_max(i).block(ny_offset, 0, ocp.dim.ny, 1)              = ocp.b_max(i);
        }
        combined_ocp.C(N).block(ny_N_offset, nx_offset, ocp.dim.ny_N, ocp.dim.nx) = ocp.C(N);
        combined_ocp.b_min(N).block(ny_N_offset, 0, ocp.dim.ny_N, 1)              = ocp.b_min(N);
        combined_ocp.b_max(N).block(ny_N_offset, 0, ocp.dim.ny_N, 1)              = ocp.b_max(N);
        // Copy cost
        for (index_t i = 1; i < N; ++i) {
            combined_ocp.Q(i).block(nx_offset, nx_offset, ocp.dim.nx, ocp.dim.nx) = ocp.Q(i);
            combined_ocp.R(i).block(nu_offset, nu_offset, ocp.dim.nu, ocp.dim.nu) = ocp.R(i);
            combined_ocp.S(i).block(nu_offset, nx_offset, ocp.dim.nu, ocp.dim.nx) = ocp.S(i);
            combined_ocp.S_trans(i).block(nx_offset, nu_offset, ocp.dim.nx, ocp.dim.nu) =
                ocp.S_trans(i);
            combined_ocp.q(i).block(nx_offset, 0, ocp.dim.nx, 1) = ocp.q(i);
            combined_ocp.r(i).block(nu_offset, 0, ocp.dim.nu, 1) = ocp.r(i);
        }
        combined_ocp.Q(N).block(nx_offset, nx_offset, ocp.dim.nx, ocp.dim.nx) = ocp.Q(N);
        combined_ocp.q(N).block(nx_offset, 0, ocp.dim.nx, 1)                  = ocp.q(N);

        nx_offset += ocp.dim.nx;
        nu_offset += ocp.dim.nu;
        ny_offset += ocp.dim.ny;
        ny_N_offset += ocp.dim.ny_N;
    }

    const index_t nx_max = std::ranges::fold_left(ocps, index_t{0}, fld_max(&cyqlone::OCPDim::nx)),
                  nu_max = std::ranges::fold_left(ocps, index_t{0}, fld_max(&cyqlone::OCPDim::nu));
    for (index_t i = nx_max; i < combined_ocp.dim.nx; ++i)
        combined_ocp.Q(0)(i, i) = 1; // regularize unused state variables in the cost
    for (index_t i = nu_max; i < combined_ocp.dim.nu; ++i)
        combined_ocp.R(0)(i, i) = 1; // regularize unused control variables in the cost
    std::cout << "Combined OCP has N=" << combined_ocp.dim.N_horiz << ", nx=" << combined_ocp.dim.nx
              << ", nu=" << combined_ocp.dim.nu << ", ny=" << combined_ocp.dim.ny
              << ", ny_N=" << combined_ocp.dim.ny_N << "\n";
    // guanaqo::print_python(std::cout << "x(0) = ", combined_ocp.b(0), "\n");
    return combined_ocp;
}
#include <cyqlone/random-ocp.hpp>

TEST(QPALM, random_fan) {
    using cyqlone::index_t;
    using cyqlone::real_t;
    namespace qp = cyqlone::qpalm;
    namespace la = cyqlone::linalg;

    constexpr index_t VL       = 4;
    const index_t num_branches = 2;

#if GUANAQO_WITH_TRACING
    guanaqo::trace_logger_set_default_size(1'048'576);
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reserve(1'048'576); });

    auto save_traces = [&](const std::string &name) {
        namespace fs = std::filesystem;
        fs::path out_dir{"traces"};
        out_dir /= *cyqlone_commit_hash ? cyqlone_commit_hash : "unknown";
        fs::create_directories(out_dir);
        std::ofstream csv{out_dir / name};
        guanaqo::TraceLogger::write_column_headings(csv) << '\n';
        std::vector<std::span<const guanaqo::TraceLogger::Log>> all_logs;
        guanaqo::for_each_trace_logger([&](auto &logger) {
            std::span logs = logger.get_logs();
            all_logs.push_back(logs);
            for (const auto &log : logs)
                csv << log << '\n';
        });
        std::cout << fs::absolute(out_dir / name) << std::endl;
        cyqlone::write_chrome_trace((out_dir / name).replace_extension("json.gz"), all_logs);
        std::cout << fs::absolute((out_dir / name).replace_extension("json.gz")) << std::endl;
    };
#else
    auto save_traces = [](const std::string &) {};
#endif
    cyqlone::OCPDim dim{
        .N_horiz = 64,
        .nx      = 8,
        .nu      = 5,
        .ny      = 0,
        .ny_N    = 0,
    };

    const index_t N  = dim.N_horiz;
    const index_t nx = dim.nx;
    const index_t nu = dim.nu;

    std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);

    // Same initial condition for all branches.
    batmat::matrix::Matrix<real_t, index_t> x0{{.rows = nx, .cols = 1}};
    std::mt19937 rng(12345);
    std::uniform_real_distribution<real_t> dist(-1.0, 1.0);

    for (auto &v : x0) {
        v = dist(rng);
    }

    for (index_t i = 0; i < num_branches; ++i) {
        ocps[i] = cyqlone::generate_random_ocp(dim, static_cast<uint32_t>(1000 + i));
        std::cout << "Fan OCP" << i << " has N=" << ocps[i].dim.N_horiz << ", nx=" << ocps[i].dim.nx
                  << ", nu=" << ocps[i].dim.nu << ", ny=" << ocps[i].dim.ny
                  << ", ny_N=" << ocps[i].dim.ny_N << "\n";
        ocps[i].C(0).set_constant(0); // no constraints on x(0) and u(0)
        // guanaqo::print_python(std::cout << "x(0) = ", ocps[i].b(0), "\n");
        // guanaqo::print_python(std::cout << "r(0) = ", ocps[i].r(0), "\n");
        // Force the same initial state in every branch.
        // la::copy(x0, ocps[i].b(0));
    }

    const bool verbose = true;

    // -------------------------------------------------------------------------
    // Fan solver
    // -------------------------------------------------------------------------
    cyqlone::FanOCPStorage fan_ocp{
        .ocps    = ocps,
        .R0      = ocps[0].R(0),
        .r0      = ocps[0].r(0),
        .D0      = ocps[0].D(0),
        .b_min_0 = ocps[0].b_min(0),
        .b_max_0 = ocps[0].b_max(0),
    };

    auto fan_cocp = cyqlone::FanCyqloneStorage<>::build(fan_ocp, dim.ny);
    std::cout << "Running on " << cyq_get_num_proc() << " processors\n";
    auto &&fan_backend =
        qp::make_cyqpalm_backend<VL, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<VL>>(
            fan_cocp, {},
            {
                .processors             = 2,
                .print_residuals        = verbose,
                .print_precision        = 17,
                .changing_constr_factor = 0,
                .max_update_count       = 0,

                // Fan solver handles the shared/root part itself.
                .tricyqle_params =
                    {
                        .solve_method = cyqlone::SolveMethod::None,
                    },
            });

    qp::Solver<qp::CyQPALMBackend<VL, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<VL>> *>
        fan_qpalm{
            fan_backend.get(),
            {
                .max_outer_iter       = 1000,
                .max_total_inner_iter = 10000,
                .tolerance            = 1e-9,
                .verbose              = verbose,
                .detailed_stats       = verbose,
            },
        };

    auto fan_status = fan_qpalm();
    save_traces("fanout-fan-qpalm.csv");

    EXPECT_EQ(fan_status, qp::SolverStatus::Converged);
    std::cout << "inner:   " << fan_qpalm.stats->inner_iter << "\n"
              << "outer:   " << fan_qpalm.stats->outer_iter << "\n"
              << "timings: " << fan_qpalm.stats->timings.total << "\n";
    auto x_fan = fan_qpalm.get_solution();
    auto λ_fan = fan_qpalm.get_equality_multipliers();

    // -------------------------------------------------------------------------
    // Combined solver
    // -------------------------------------------------------------------------
    auto combined_ocp  = combine_branches_0(ocps);
    auto combined_cocp = cyqlone::CyqloneStorage<>::build(combined_ocp);

    auto &&combined_backend =
        qp::make_cyqpalm_backend<VL, StorageOrder::ColMajor, cyqlone::CyqloneSolver<VL>>(
            combined_cocp, {},
            {
                .processors             = 8,
                .print_residuals        = verbose,
                .print_precision        = 17,
                .changing_constr_factor = 0,
                .max_update_count       = 0,
                .tricyqle_params        = {.solve_method = cyqlone::SolveMethod::PCR},
            });

    qp::Solver<qp::CyQPALMBackend<VL, StorageOrder::ColMajor, cyqlone::CyqloneSolver<VL>> *>
        combined_qpalm{
            combined_backend.get(),
            {
                .max_outer_iter       = 1000,
                .max_total_inner_iter = 10000,
                .tolerance            = 1e-9,

                .verbose        = verbose,
                .detailed_stats = verbose,
            },
        };

    auto combined_status = combined_qpalm();
    EXPECT_EQ(combined_status, qp::SolverStatus::Converged);

    auto x_combined = combined_qpalm.get_solution();
    auto λ_combined = combined_qpalm.get_equality_multipliers();

    // -------------------------------------------------------------------------
    // Layout-aware comparison
    // -------------------------------------------------------------------------
    std::vector<std::size_t> nx_per_branch;
    nx_per_branch.reserve(ocps.size());
    std::cout << "inner:   " << combined_qpalm.stats->inner_iter << "\n"
              << "outer:   " << combined_qpalm.stats->outer_iter << "\n"
              << "timings: " << combined_qpalm.stats->timings.total << "\n";
    for (const auto &ocp : ocps) {
        nx_per_branch.push_back(static_cast<std::size_t>(ocp.dim.nx));
    }

    compare_combined_normal(std::span<const double>(x_combined), std::span<const double>(x_fan),
                            static_cast<std::size_t>(N), static_cast<std::size_t>(nu),
                            std::span<const std::size_t>(nx_per_branch), 1e-7);

    compare_combined_normal(std::span<const double>(λ_combined), std::span<const double>(λ_fan),
                            static_cast<std::size_t>(N), 0,
                            std::span<const std::size_t>(nx_per_branch), 1e-7);
}
TEST(QPALM, random_fan_input_constr) {
    using cyqlone::index_t;
    using cyqlone::real_t;
    namespace qp = cyqlone::qpalm;
    namespace la = cyqlone::linalg;

    constexpr index_t VL       = 4;
    const index_t num_branches = 2;

#if GUANAQO_WITH_TRACING
    guanaqo::trace_logger_set_default_size(1'048'576);
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reserve(1'048'576); });

    auto save_traces = [&](const std::string &name) {
        namespace fs = std::filesystem;
        fs::path out_dir{"traces"};
        out_dir /= *cyqlone_commit_hash ? cyqlone_commit_hash : "unknown";
        fs::create_directories(out_dir);
        std::ofstream csv{out_dir / name};
        guanaqo::TraceLogger::write_column_headings(csv) << '\n';
        std::vector<std::span<const guanaqo::TraceLogger::Log>> all_logs;
        guanaqo::for_each_trace_logger([&](auto &logger) {
            std::span logs = logger.get_logs();
            all_logs.push_back(logs);
            for (const auto &log : logs)
                csv << log << '\n';
        });
        std::cout << fs::absolute(out_dir / name) << std::endl;
        cyqlone::write_chrome_trace((out_dir / name).replace_extension("json.gz"), all_logs);
        std::cout << fs::absolute((out_dir / name).replace_extension("json.gz")) << std::endl;
    };
#else
    auto save_traces = [](const std::string &) {};
#endif
    cyqlone::OCPDim dim{
        .N_horiz = 16,
        .nx      = 6,
        .nu      = 2,
        .ny      = 1,
        .ny_N    = 0,
    };

    const index_t N  = dim.N_horiz;
    const index_t nx = dim.nx;
    const index_t nu = dim.nu;

    std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);

    // Same initial condition for all branches.
    batmat::matrix::Matrix<real_t, index_t> x0{{.rows = nx, .cols = 1}};
    std::mt19937 rng(12345);
    std::uniform_real_distribution<real_t> dist(-1.0, 1.0);

    for (auto &v : x0) {
        v = dist(rng);
    }

    for (index_t i = 0; i < num_branches; ++i) {
        ocps[i] = cyqlone::generate_random_ocp_input_constr(dim, static_cast<uint32_t>(1000 + i));
        std::cout << "Fan OCP" << i << " has N=" << ocps[i].dim.N_horiz << ", nx=" << ocps[i].dim.nx
                  << ", nu=" << ocps[i].dim.nu << ", ny=" << ocps[i].dim.ny
                  << ", ny_N=" << ocps[i].dim.ny_N << "\n";
        if (i != 0) {
            ocps[i].b_max(0).set_constant(
                std::numeric_limits<real_t>::
                    infinity()); // no constraints on u(0) in the other branches, to test that the coupling is handled correctly
            ocps[i].b_min(0).set_constant(
                -std::numeric_limits<real_t>::
                    infinity()); // no constraints on u(0) in the other branches, to test that the coupling is handled correctly
        }
        // guanaqo::print_python(std::cout << "x(0) = ", ocps[i].b(0), "\n");
        // guanaqo::print_python(std::cout << "r(0) = ", ocps[i].r(0), "\n");
        // Force the same initial state in every branch.
        // la::copy(x0, ocps[i].b(0));
    }

    const bool verbose = true;

    // -------------------------------------------------------------------------
    // Fan solver
    // -------------------------------------------------------------------------
    cyqlone::FanOCPStorage fan_ocp{
        .ocps    = ocps,
        .R0      = ocps[0].R(0),
        .r0      = ocps[0].r(0),
        .D0      = ocps[0].D(0),
        .b_min_0 = ocps[0].b_min(0),
        .b_max_0 = ocps[0].b_max(0),
    };

    auto fan_cocp    = cyqlone::FanCyqloneStorage<>::build(fan_ocp, dim.ny);
    index_t num_proc = 8;
    std::cout << "Running on " << num_proc << " processors\n";
    auto &&fan_backend =
        qp::make_cyqpalm_backend<VL, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<VL>>(
            fan_cocp, {},
            {
                .processors             = num_proc,
                .print_residuals        = verbose,
                .print_precision        = 17,
                .changing_constr_factor = 0,
                .max_update_count       = 0,

                // Fan solver handles the shared/root part itself.
                .tricyqle_params =
                    {
                        .solve_method = cyqlone::SolveMethod::None,
                    },
                .spin_count = std::numeric_limits<uint32_t>::max(), // disable spin count limit, since the fan solver can have a long first iteration due to the coupling

            });

    qp::Solver<qp::CyQPALMBackend<VL, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<VL>> *>
        fan_qpalm{
            fan_backend.get(),
            {
                .max_outer_iter       = 100,
                .max_total_inner_iter = 1,
                .tolerance            = 1e-7,
                .verbose              = verbose,
                .detailed_stats       = verbose,
            },
        };
    for (index_t i = 0; !verbose && i < 50; ++i) {
        fan_qpalm(); // warm up
    }
#if GUANAQO_WITH_TRACING
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reset(); });
#endif
    auto fan_status = fan_qpalm();
    save_traces("fanout-fan-qpalm.csv");

    EXPECT_EQ(fan_status, qp::SolverStatus::Converged);
    std::cout << "inner:   " << fan_qpalm.stats->inner_iter << "\n"
              << "outer:   " << fan_qpalm.stats->outer_iter << "\n"
              << "timings: " << fan_qpalm.stats->timings.total << "\n";
    auto x_fan = fan_qpalm.get_solution();
    auto λ_fan = fan_qpalm.get_equality_multipliers();

    // -------------------------------------------------------------------------
    // Combined solver
    // -------------------------------------------------------------------------
    auto combined_ocp  = combine_branches_0(ocps);
    auto combined_cocp = cyqlone::CyqloneStorage<>::build(combined_ocp);

    auto &&combined_backend =
        qp::make_cyqpalm_backend<VL, StorageOrder::ColMajor, cyqlone::CyqloneSolver<VL>>(
            combined_cocp, {},
            {
                .processors             = num_proc,
                .print_residuals        = verbose,
                .print_precision        = 17,
                .changing_constr_factor = 0,
                .max_update_count       = 0,
                .tricyqle_params        = {.solve_method = cyqlone::SolveMethod::PCR},
            });

    qp::Solver<qp::CyQPALMBackend<VL, StorageOrder::ColMajor, cyqlone::CyqloneSolver<VL>> *>
        combined_qpalm{
            combined_backend.get(),
            {
                .max_outer_iter       = 100,
                .max_total_inner_iter = 1,
                .tolerance            = 1e-7,

                .verbose        = verbose,
                .detailed_stats = verbose,
            },
        };
    for (index_t i = 0; !verbose && i < 50; ++i)
        combined_qpalm(); // warm up
#if GUANAQO_WITH_TRACING
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reset(); });
#endif
    auto combined_status = combined_qpalm();
    EXPECT_EQ(combined_status, qp::SolverStatus::Converged);
    save_traces("fanout-combined.csv");

    auto x_combined = combined_qpalm.get_solution();
    auto λ_combined = combined_qpalm.get_equality_multipliers();

    // -------------------------------------------------------------------------
    // Layout-aware comparison
    // -------------------------------------------------------------------------
    std::vector<std::size_t> nx_per_branch;
    nx_per_branch.reserve(ocps.size());
    std::cout << "inner:   " << combined_qpalm.stats->inner_iter << "\n"
              << "outer:   " << combined_qpalm.stats->outer_iter << "\n"
              << "timings: " << combined_qpalm.stats->timings.total << "\n";
    std::cout << "speedup: " << static_cast<double>(combined_qpalm.stats->timings.total.wall_time.count()) / static_cast<double>(fan_qpalm.stats->timings.total.wall_time.count())  << "\n";
    for (const auto &ocp : ocps) {
        nx_per_branch.push_back(static_cast<std::size_t>(ocp.dim.nx));
    }

    compare_combined_normal(std::span<const double>(x_combined), std::span<const double>(x_fan),
                            static_cast<std::size_t>(N), static_cast<std::size_t>(nu),
                            std::span<const std::size_t>(nx_per_branch), 1e-7);

    compare_combined_normal(std::span<const double>(λ_combined), std::span<const double>(λ_fan),
                            static_cast<std::size_t>(N), 0,
                            std::span<const std::size_t>(nx_per_branch), 1e-7);
}