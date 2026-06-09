#include <cyqlone/conversion.hpp>
#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.hpp>
#include <cyqlone/qpalm/example-problems/csv.hpp>
#include <cyqlone/qpalm/example-problems/platooning.hpp>
#include <cyqlone/qpalm/solver.hpp>
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
#if GUANAQO_WITH_TRACING
static void init_trace() {
    guanaqo::get_trace_logger().reset();
    guanaqo::get_trace_logger().logs.resize(65565);
    GUANAQO_TRACE("init", 0);
}
static std::filesystem::path save_trace(const char *name) {
    std::optional tr = guanaqo::get_trace_logger().trace("end", 0);
    std::filesystem::path out_dir{"traces"};
    out_dir /= *cyqlone_commit_hash ? cyqlone_commit_hash : "unknown";
    std::filesystem::path out_file = out_dir / name;
    std::filesystem::create_directories(out_dir);
    std::ofstream csv{out_file};
    guanaqo::TraceLogger::write_column_headings(csv) << '\n';
    tr.reset();
    for (const auto &log : guanaqo::get_trace_logger().get_logs())
        csv << log << '\n';
    return out_file;
}
#endif

#include <fstream>
TEST(QPALM, cyqlonefan) {
    index_t num_branches = 2;
    index_t N            = 32;
    std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);
    for (index_t i = 0; i < num_branches; ++i) {
        auto filename = std::format("python/cmpc/ocp_data{}_{}.mat", N, i);

        cyqlone::LinearOCPStorage ocp_fan;
        auto matfp = cyqlone::open_mat(filename);
        cyqlone::read_from_mat(matfp.get(), "ocp", ocp_fan);

        ocps[i] = ocp_fan;
        guanaqo::print_python(std::cout << "x(0) = ", ocp_fan.b(0), "\n");
        std::cout << "Loaded OCP data from " << filename << " with N=" << ocp_fan.dim.N_horiz
                  << ", nu=" << ocp_fan.dim.nu << ", ny=" << ocp_fan.dim.ny << "\n";
    }
    std::cout << cyq_get_num_proc() << " processors detected\n";
    cyqlone::FanOCPStorage fan_ocp{
        .ocps = ocps, .R0 = ocps[0].R(0), .r0 = ocps[0].r(0), .D0 = ocps[0].D(0)};
    auto cocp          = cyqlone::FanCyqloneStorage<>::build(fan_ocp, 0);
    const bool verbose = false;
    auto &&backend =
        qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>>(
            cocp, {},
            {
                .processors      = cyq_get_num_proc(),
                .print_residuals = verbose,
                .print_precision = 17,
                .tricyqle_params = {.solve_method = cyqlone::SolveMethod::None},
            });
    qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>> *> qpalm{
        backend.get(),
        {.max_outer_iter       = 1,
         .max_total_inner_iter = 1,
         .tolerance            = 1e-6,
         .verbose              = verbose,
         .detailed_stats       = verbose},
    };

    for (index_t i = 0; !verbose && i < 50; ++i) {
        std::cout << "Warmup iteration " << i + 1 << "\n";
        auto status = qpalm(); // warm up
        EXPECT_EQ(status, qp::SolverStatus::Converged);
    }

    auto status = qpalm();
    EXPECT_EQ(status, qp::SolverStatus::Converged);

#if GUANAQO_WITH_TRACING
    std::cout << save_trace("test-FanCyQpalm.csv") << "\n\n";
#endif

    std::cout << "inner:   " << qpalm.stats->inner_iter << "\n"
              << "outer:   " << qpalm.stats->outer_iter << "\n"
              << "timings: " << qpalm.stats->timings.total << "\n";

    std::ofstream solution{"solution-fan-cyqpalm.csv"};
    auto x = qpalm.get_solution(), λ = qpalm.get_equality_multipliers(),
         y = qpalm.get_inequality_multipliers();
    guanaqo::print_csv(solution, std::span{x});
    guanaqo::print_csv(solution, std::span{λ});
    guanaqo::print_csv(solution, std::span{y});
}
TEST(QPALM, with_inequality) {
    index_t num_branches = 2;
    index_t N            = 32;
    std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);
    for (index_t i = 0; i < num_branches; ++i) {
        auto filename = std::format("python/cmpc/ocp_data_constr{}_{}.mat", N, i);

        cyqlone::LinearOCPStorage ocp_fan;
        auto matfp = cyqlone::open_mat(filename);
        cyqlone::read_from_mat(matfp.get(), "ocp", ocp_fan);

        ocps[i] = ocp_fan;
        guanaqo::print_python(std::cout << "x(0) = ", ocp_fan.b(0), "\n");
        std::cout << "Loaded OCP data from " << filename << " with N=" << ocp_fan.dim.N_horiz
                  << ", nu=" << ocp_fan.dim.nu << ", ny=" << ocp_fan.dim.ny << "\n";
    }
    std::cout << cyq_get_num_proc() << " processors detected\n";
    cyqlone::FanOCPStorage fan_ocp{
        .ocps = ocps, .R0 = ocps[0].R(0), .r0 = ocps[0].r(0), .D0 = ocps[0].D(0)};
    auto cocp          = cyqlone::FanCyqloneStorage<>::build(fan_ocp, ocps[0].D(0).cols);
    const bool verbose = true;
    auto &&backend =
        qp::make_cyqpalm_backend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>>(
            cocp, {},
            {
                .processors      = 2,
                .print_residuals = verbose,
                .print_precision = 17,
                .changing_constr_factor       = 0,
                .max_update_count             = 0, 
                .tricyqle_params = {.solve_method = cyqlone::SolveMethod::None},
            });
    qp::Solver<qp::CyQPALMBackend<4, StorageOrder::ColMajor, cyqlone::FanCyqloneSolver<4>> *> qpalm{
        backend.get(),
        {.max_outer_iter       = 200,
         .max_total_inner_iter = 1000,
         .tolerance            = 1e-6,
         .verbose              = verbose},
    };

#if GUANAQO_WITH_TRACING
    for (index_t i = 0; !verbose && i < 50; ++i)
        qpalm(); // warm up
    init_trace();
#endif

    auto status = qpalm();
    EXPECT_EQ(status, qp::SolverStatus::Converged);

#if GUANAQO_WITH_TRACING
    std::cout << save_trace("test-FanCyQpalm.csv") << "\n\n";
#endif

    std::cout << "inner:   " << qpalm.stats->inner_iter << "\n"
              << "outer:   " << qpalm.stats->outer_iter << "\n"
              << "timings: " << qpalm.stats->timings.total << "\n";

    std::ofstream solution{"solution-fan-cyqpalm.csv"};
    auto x = qpalm.get_solution(), λ = qpalm.get_equality_multipliers(),
         y = qpalm.get_inequality_multipliers();
    guanaqo::print_csv(solution, std::span{x});
    guanaqo::print_csv(solution, std::span{λ});
    guanaqo::print_csv(solution, std::span{y});
}