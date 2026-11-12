#include <benchmark/benchmark.h>

#include <fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.hpp>
#include <fancyqlone/fancyqpalm/example-problems/centroidal-quadruped.hpp>
#include <fancyqlone/fancyqpalm/settings.hpp>
#include <fancyqlone/fancyqpalm/solver.hpp>
#include <fancyqlone/fancyqpalm/status.hpp>
#include <CLI/CLI.hpp>
#include <batmat/dtypes.hpp>
#include <batmat/openmp.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unistd.h>
#include <utility>
#include <vector>

#if WITH_HPIPM
#include "hpipm.hpp"
#endif

namespace qp = fancyqlone::qpalm;
using fancyqlone::index_t;
using fancyqlone::real_t;
using qp::problems::CentroidalQuadrupedParams;
using seconds = std::chrono::duration<double>;

#if defined(__ARM_NEON)
constexpr auto native_vector_length = std::is_same_v<real_t, double> ? 2 : 4;
#else
constexpr auto native_vector_length = std::is_same_v<real_t, double> ? 4 : 8;
#endif
constexpr auto vector_length = batmat::types::vl_at_most<real_t, native_vector_length>;

auto counter(auto value) {
    return benchmark::Counter{static_cast<double>(value), benchmark::Counter::kDefaults};
}

struct Options {
    std::vector<int> parallelism{8};
    std::vector<int> horizon{32};
    real_t mu            = 0.5;
#if WITH_HPIPM
    bool hpipm = true;
#else
    bool hpipm = false;
#endif
    bool custom_reporter = true;
    bool print_extra     = false;
    bool use_color       = false;
};

template <index_t VL>
void run_benchmark(benchmark::State &state, CentroidalQuadrupedParams params,
                   index_t processors) try {
    if (processors < 1)
        return state.SkipWithMessage("Number of processors must be at least 1");

    auto problem = qp::problems::centroidal_quadruped(std::move(params));
    auto ocp     = fancyqlone::CyqloneStorage<>::build(problem.ocp);
    qp::CyQPALMBackendSettings backend_settings{
        .processors             = processors,
        .print_residuals                = false,
        .changing_constr_factor = 0.01,
        .max_update_count       = 20,
        .tricyqle_params        = {.solve_method = fancyqlone::SolveMethod::PCR},
    };
    auto backend = qp::make_cyqpalm_backend<VL, qp::StorageOrder::ColMajor>(ocp, {},
                                                                            backend_settings);
    qp::Settings settings{
        .tolerance         = 1e-8,
        .dual_tolerance    = 1e-8,
        .Δy = 10,
        .initial_penalty_y = 0.01,
        .verbose           = false,
        .print_linesearch_inputs = false,
    };
    qp::Solver<qp::CyQPALMBackend<VL, qp::StorageOrder::ColMajor> *> solver{backend.get(),
                                                                            settings};

    auto status = solver();
    for (auto _ : state) {
        status = solver();
        state.SetIterationTime(seconds(solver.stats->timings.total.wall_time).count());
    }

    const auto solution = ocp.reconstruct_solution(problem.ocp, solver.get_solution(),
                                                    solver.get_inequality_multipliers(),
                                                    solver.get_equality_multipliers());
    const auto error = problem.ocp.compute_kkt_error(solution);
    state.counters["status"]     = counter(status);
    state.counters["success"]    = counter(status == qp::SolverStatus::Converged);
    state.counters["iter"]       = counter(solver.stats->inner_iter);
    state.counters["outer_iter"] = counter(solver.stats->outer_iter);
    state.counters["num_factor"] = counter(solver.stats_backend->num_factor);
    state.counters["num_upd"]    = counter(solver.stats_backend->num_updates);
    state.counters["rank_upd"]   = counter(solver.stats_backend->rank_updates);
    state.counters["res_dual"]   = counter(error.stationarity);
    state.counters["res_eq"]     = counter(error.equality_residual);
    state.counters["res_ineq"]   = counter(error.inequality_residual);
    state.counters["compl"]      = counter(error.complementarity);
} catch (const std::exception &e) {
    state.SkipWithError(e.what());
}

#if WITH_HPIPM
void run_benchmark_hpipm(benchmark::State &state, CentroidalQuadrupedParams params) try {
    auto problem     = qp::problems::centroidal_quadruped(std::move(params));
    auto qp_data     = build_hpipm_qp(problem.ocp);
    auto solver_data = create_hpipm_solver(qp_data);

    solve_hpipm(*qp_data, *solver_data);
    for (auto _ : state) {
        const auto solve_time = solve_hpipm(*qp_data, *solver_data);
        state.SetIterationTime(seconds(solve_time).count());
    }

    const auto solution = get_solution_hpipm(*solver_data);
    const auto error    = problem.ocp.compute_kkt_error(solution);
    const auto stats    = get_stats_hpipm(*solver_data);
    state.counters["status"]       = counter(stats.status);
    state.counters["success"]      = counter(stats.status == 0);
    state.counters["iter"]         = counter(stats.iter);
    state.counters["max_res_stat"] = counter(stats.max_res_stat);
    state.counters["max_res_eq"]   = counter(stats.max_res_eq);
    state.counters["max_res_ineq"] = counter(stats.max_res_ineq);
    state.counters["max_res_comp"] = counter(stats.max_res_comp);
    state.counters["res_dual"]     = counter(error.stationarity);
    state.counters["res_eq"]       = counter(error.equality_residual);
    state.counters["res_ineq"]     = counter(error.inequality_residual);
    state.counters["compl"]        = counter(error.complementarity);
} catch (const std::exception &e) {
    state.SkipWithError(e.what());
}
#endif

std::unique_ptr<benchmark::BenchmarkReporter> make_custom_reporter(size_t problem_name_width,
                                                                    size_t solver_name_width,
                                                                    bool print_extra,
                                                                    bool with_color);

void register_options(const char *program, CLI::App &app, Options &opts) {
    if (std::getenv("NO_COLOR"))
        opts.use_color = false;
    else if (std::getenv("CLICOLOR_FORCE"))
        opts.use_color = true;
    else
        opts.use_color = ::isatty(::fileno(stdout)) == 1;
#if BATMAT_WITH_OPENMP
    opts.parallelism = {omp_get_max_threads()};
#endif
    app.usage(std::string(program) + " [options] -- [benchmark options]");
    app.allow_extras();
    app.add_option("--mu", opts.mu, "Nominal friction coefficient");
    app.add_option("--horizon,-N", opts.horizon,
                   "Number of samples over 0.64 s (positive multiple of 4)");
    app.add_option("--parallelism,-p", opts.parallelism,
                   "Number of threads used by the Cyqlone backend");
    app.add_flag("--hpipm,!--no-hpipm", opts.hpipm, "Use HPIPM for comparison");
    app.add_flag("--custom-reporter,!--no-custom-reporter", opts.custom_reporter,
                 "Use the custom benchmark reporter");
    app.add_flag("--print-extra,!--no-print-extra", opts.print_extra,
                 "Print additional benchmark counters");
    app.add_flag("--color,!--no-color", opts.use_color, "Enable colored output");
}

int initialize_google_benchmark(char *program, std::vector<std::string> args) {
    if (!args.empty() && args.front() == "--")
        args.erase(args.begin());
    std::vector<char *> argv(args.size() + 2);
    std::ranges::transform(args, argv.begin() + 1, [](auto &arg) { return arg.data(); });
    argv[0]   = program;
    auto argc = static_cast<int>(args.size()) + 1;
    benchmark::Initialize(&argc, argv.data());
    return benchmark::ReportUnrecognizedArguments(argc, argv.data()) ? 1 : 0;
}

int main(int argc, char **argv) try {
    char *const program = argv[0];
    CLI::App app{"CyQPALM and Cyqlone Centroidal Quadruped Benchmark"};
    Options opts;
    register_options(program, app, opts);
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    CentroidalQuadrupedParams params;
    params.mu = opts.mu;
    params.force_weights.fill(5e-5);
    
    size_t problem_name_width = 0;
    size_t solver_name_width  = 0;
    for (const auto horizon : opts.horizon) {
        if (horizon <= 0 || horizon % 4 != 0)
            throw std::invalid_argument("Prediction horizon must be a positive multiple of 4");
        // Resample QUADCMPC1's four 0.16 s gait phases over a fixed 0.64 s horizon.
        params.N_horiz = horizon;
        params.dt      = real_t{0.64} / static_cast<real_t>(horizon);
        for (auto &phase : params.gait)
            phase.duration = horizon / 4;
        const auto problem_name =
            std::format("centroidal-quadruped(N={},mu={:.3g})", params.N_horiz, params.mu);
        problem_name_width = std::max(problem_name_width, problem_name.size());
#if WITH_HPIPM
        if (opts.hpipm) {
            constexpr std::string_view solver_name = "hpipm";
            solver_name_width = std::max(solver_name_width, solver_name.size());
            benchmark::RegisterBenchmark(std::format("{}@{}", problem_name, solver_name),
                                         [=](benchmark::State &state) {
                                             run_benchmark_hpipm(state, params);
                                         })
                ->MeasureProcessCPUTime()
                ->UseManualTime()
                ->Unit(benchmark::kMillisecond)
                ->ComputeStatistics("max", [](auto &values) {
                    return *std::ranges::max_element(values);
                })
                ->ComputeStatistics("min", [](auto &values) {
                    return *std::ranges::min_element(values);
                });
        }
#else
        if (opts.hpipm)
            throw std::invalid_argument("HPIPM support not enabled in this build");
#endif
        for (const auto processors : opts.parallelism) {
            const auto solver_name =
                std::format("cyqlone(p={},v={},cm,zero)", processors, vector_length);
            solver_name_width = std::max(solver_name_width, solver_name.size());
            benchmark::RegisterBenchmark(std::format("{}@{}", problem_name, solver_name),
                                         [=](benchmark::State &state) {
                                             run_benchmark<vector_length>(state, params, processors);
                                         })
                ->MeasureProcessCPUTime()
                ->UseManualTime()
                ->Unit(benchmark::kMillisecond)
                ->ComputeStatistics("max", [](auto &values) {
                    return *std::ranges::max_element(values);
                })
                ->ComputeStatistics("min", [](auto &values) {
                    return *std::ranges::min_element(values);
                });
        }
    }

    if (const auto error = initialize_google_benchmark(program, app.remaining(true)); error != 0)
        return error;
    auto reporter = opts.custom_reporter
                        ? make_custom_reporter(problem_name_width, solver_name_width + 2,
                                               opts.print_extra, opts.use_color)
                        : nullptr;
    benchmark::RunSpecifiedBenchmarks(reporter.get());
    benchmark::Shutdown();
} catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
