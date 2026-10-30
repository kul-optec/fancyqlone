

#include <benchmark/benchmark.h>

#include <cyqlone/matio.hpp>
#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.hpp>
#include <cyqlone/qpalm/example-problems/centroidal-quadruped.hpp>
#include <cyqlone/qpalm/settings.hpp>
#include <cyqlone/qpalm/solver.hpp>
#include <cyqlone/qpalm/status.hpp>
#include <cyqlone/tracing.hpp>
#include <CLI/CLI.hpp>
#include <batmat/dtypes.hpp>
#include <batmat/lut.hpp>
#include <batmat/openmp.h>
#include <guanaqo/demangled-typename.hpp>
#include <guanaqo/pcm/counters.hpp>
#include <guanaqo/perfetto/trace.hpp>
#include <guanaqo/string-util.hpp>
#include <guanaqo/stringify.h>
#include <guanaqo/trace.hpp>
#include <batmat-version.h>
#include <cyqlone-version.h>
#include <unistd.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <generator>
#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <stdexcept>
#include <utility>
namespace fs = std::filesystem;

#if GUANAQO_WITH_MKL
#include <mkl.h>
#elif GUANAQO_WITH_OPENBLAS
#include <openblas_config.h>
#endif
#if WITH_HPIPM
#include "treehpipm.hpp"
#endif
#if WITH_PIQP
#include "mspiqp.hpp"
#endif
#if WITH_TREEQP
#include "treeqp.hpp"
#endif
#if defined(__ARM_NEON)
constexpr auto v_native = std::is_same_v<batmat::real_t, double> ? 2 : 4;
#else
constexpr auto v_native = std::is_same_v<batmat::real_t, double> ? 4 : 8; // assuming AVX2
#endif
constexpr auto v = batmat::types::vl_at_most<batmat::real_t, v_native>;

auto counter(auto x) {
    return benchmark::Counter{static_cast<double>(x), benchmark::Counter::kDefaults};
}
auto counter_avg(auto x) {
    return benchmark::Counter{static_cast<double>(x), benchmark::Counter::kAvgIterations};
}
;


struct Options {
    bool cold                      = true;
    bool warm_shift                = false;
    bool warm_copy                 = false;
    bool no_updates                = true;
    std::vector<int> parallelism   = {8};
    std::vector<int> vector_length = {v};
    bool rm                        = false;
    bool cm                        = true;
    bool pcr                       = true;
#if WITH_HPIPM
    bool hpipm = true;
#else
    bool hpipm = false;
#endif
#if WITH_PIQP
    bool piqp = true;
#else
    bool piqp = false;
#endif
#if WITH_TREEQP
    bool treeqp = true;
#else
    bool treeqp = false;
#endif
    std::vector<int> horizon{32, 64, 96, 128, 192, 256};
    uint64_t num_instances            = 50;
    std::vector<int> num_branches{4};
    uint64_t seed                     = 0;
    bool custom_reporter              = true;
    bool print_extra                  = false;
    bool use_color                    = false;
    bool trace                        = false;
    bool serial                       = false;
    std::string export_problem{};
};

namespace qp = cyqlone::qpalm;
using cyqlone::index_t;
using cyqlone::real_t;
using qp::problems::CentroidalQuadrupedParams;
using seconds = std::chrono::duration<double>;

qp::problems::FanCentroidalQuadrupedProblem
create_problem(const CentroidalQuadrupedParams &params, index_t num_branches, real_t mu_diff = 0.2) {
    auto problem = qp::problems::fan_centroidal_quadruped(params, num_branches, mu_diff);
    // Add a random disturbance to the initial position of the masses but make sure they are the same for all branches
    std::seed_seq seed{params.seed, params.seed >> 32};
    std::mt19937 rng{seed};
    using dist_t = std::uniform_real_distribution<real_t>;
    auto dist    =  dist_t{-0.1, +0.1};
    for (index_t r = 0; r < static_cast<index_t>(3); ++r) {
        auto disturbance = dist(rng);
        for (index_t j = 0; j < num_branches; ++j)
            problem.ocp.ocps[j].b(0)(r, 0) += disturbance;
    }
    return problem;
}

#if GUANAQO_WITH_TRACING
std::map<std::string, fs::path> traces;
void disable_tracing() {
    guanaqo::trace_logger_set_default_size(0);
    guanaqo::for_each_trace_logger([](auto &logger) { logger.clear(); });
}
void trace_run(auto &&fun, const auto &name) {
    std::filesystem::path out_dir{"traces"};
    out_dir /= *cyqlone_commit_hash ? cyqlone_commit_hash : "unknown";
    std::filesystem::path out_file = out_dir / name;
    if (auto [_, ins] = traces.try_emplace(name, out_file); !ins)
        return;
#if GUANAQO_WITH_PERFETTO
#if GUANAQO_WITH_PCM_TRACING
    guanaqo::pcm::enable_counters();
#endif
    fun(); // warmup
    auto trace = guanaqo::trace::start_tracing(2 * 1024 * 1024);
    fun();
#if GUANAQO_WITH_PCM_TRACING
    guanaqo::pcm::disable_counters();
#endif
    guanaqo::trace::stop_tracing(std::move(trace), out_file.replace_extension(".pftrace"));
#else
    guanaqo::for_each_trace_logger([](auto &logger) { logger.clear(); });
    fun(); // warmup
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reset(); });
    guanaqo::trace_logger_set_default_size(1'048'576);
    guanaqo::for_each_trace_logger([](auto &logger) { logger.reserve(1'048'576); });
    fun();
    std::filesystem::create_directories(out_dir);
    std::ofstream csv{out_file.replace_extension(".csv")};
    guanaqo::TraceLogger::write_column_headings(csv) << '\n';
    std::vector<std::span<const guanaqo::TraceLogger::Log>> all_logs;
    guanaqo::for_each_trace_logger([&](auto &logger) {
        std::span logs = logger.get_logs();
        all_logs.push_back(logs);
        for (const auto &log : logs)
            csv << log << '\n';
    });
#if CYQLONE_WITH_ZLIB
    cyqlone::write_chrome_trace(out_file.replace_extension(".json.gz"), all_logs);
#endif
#endif
}
void print_traces(std::ostream &os) {
    for (const auto &[_, pth] : traces)
        os << pth << '\n';
}
#else
void disable_tracing() {}
void trace_run(auto &&, const auto &) {}
void print_traces(std::ostream &) {}
#endif

template <index_t VL, qp::StorageOrder Order>
void run_benchmark(benchmark::State &state, [[maybe_unused]] const std::string &param_name,
                   const CentroidalQuadrupedParams &params, qp::CyQPALMBackendSettings backend_settings,
                   qp::Settings settings, index_t num_branches, bool warm = false, bool trace = false) try {
    disable_tracing(); // No tracing during the actual benchmark
    if (backend_settings.processors < 1)
        return state.SkipWithMessage("Number of processors must be at least 1.");
    auto problem = create_problem(params,num_branches);
    // Build a QPALM Cyqlone solver
    auto ocp     = cyqlone::FanCyqloneStorage<>::build(problem.ocp);
    auto backend = qp::make_cyqpalm_backend<VL, Order, cyqlone::FanCyqloneSolver<VL>>(ocp, {}, backend_settings);
    qp::Solver<qp::CyQPALMBackend<VL, Order, cyqlone::FanCyqloneSolver<VL>> *> qpalm{backend.get(), settings};
    // Main benchmark
    qp::SolverStatus status;
    double time_solve = 0, time_active_set_change = 0, time_line_search = 0,
           time_recompute_outer = 0, time_recompute_inner = 0, time_mat_vec = 0;
    qpalm(); // Warm up
    if (warm) {
        // std::cout << "Warm starting FanCyqlone" << std::endl;
        const auto nx = problem.ocp.ocps.front().dim.nx, nu = problem.ocp.ocps.front().dim.nu;
        // std::cout << "Warm starting with nx = " << nx << ", nu = " << nu << std::endl;
        qpalm.warm_start_solution();
        // std::cout << "Warm starting done" << std::endl;
        auto x = qpalm.get_solution();
        index_t offset = num_branches/2 * ((nu + nx)*problem.ocp.ocps.front().dim.N_horiz-nu);
        
        for (index_t j = 0; j < num_branches; ++j) {
            std::copy_n(x.data() + nu+ offset, nx, problem.ocp.ocps[j].b(0).data);
        }
        // std::copy_n(x.data() + nu, nx, problem.ocp.ocps.front().b(0).data);
        // std::cout << "Updating ocp and backend for warm start" << std::endl;
        ocp.update(problem.ocp);
        update_cyqpalm_backend(*qpalm.backend, ocp);
    }
    for (auto _ : state) {
        status = qpalm();
        state.SetIterationTime(seconds(qpalm.stats->timings.total.wall_time).count());
        time_solve += seconds(qpalm.stats->timings.solve.wall_time).count();
        time_active_set_change += seconds(qpalm.stats->timings.active_set_change.wall_time).count();
        time_line_search += seconds(qpalm.stats->timings.line_search.wall_time).count();
        time_recompute_outer += seconds(qpalm.stats->timings.recompute_outer.wall_time).count();
        time_recompute_inner += seconds(qpalm.stats->timings.recompute_inner.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_A.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_AT.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_M.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_MT.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_Q.wall_time).count();
    }
    if (trace)
        trace_run([&] { qpalm(); }, param_name);
    auto sol       = ocp.reconstruct_solution(problem.ocp, qpalm.get_solution(),
                                              qpalm.get_inequality_multipliers(),
                                              qpalm.get_equality_multipliers());
    std::vector<cyqlone::OCPDim> OCPdims;
    for (const auto &ocp : problem.ocp.ocps) {
        OCPdims.push_back(ocp.dim);
    }
    // sol.print(OCPdims);
    auto kkt_error = problem.ocp.compute_kkt_error(sol);
    // std::cout << "kkt_error: " << kkt_error.stationarity << ", " << kkt_error.equality_residual << ", "
    //           << kkt_error.inequality_residual << ", " << kkt_error.complementarity << std::endl;
    state.counters["status"]              = counter(status);
    state.counters["success"]             = counter(status == qp::SolverStatus::Converged);
    state.counters["iter"]                = counter(qpalm.stats->inner_iter);
    state.counters["outer_iter"]          = counter(qpalm.stats->outer_iter);
    state.counters["num_factor"]          = counter(qpalm.stats_backend->num_factor);
    state.counters["num_upd"]             = counter(qpalm.stats_backend->num_updates);
    state.counters["rank_upd"]            = counter(qpalm.stats_backend->rank_updates);
    state.counters["t_solve"]             = counter_avg(time_solve);
    state.counters["t_active_set_change"] = counter_avg(time_active_set_change);
    state.counters["t_line_search"]       = counter_avg(time_line_search);
    state.counters["t_recompute_outer"]   = counter_avg(time_recompute_outer);
    state.counters["t_recompute_inner"]   = counter_avg(time_recompute_inner);
    state.counters["t_mat_vec"]           = counter_avg(time_mat_vec);
    state.counters["res_dual"]            = counter(kkt_error.stationarity);
    state.counters["res_eq"]              = counter(kkt_error.equality_residual);
    state.counters["res_ineq"]            = counter(kkt_error.inequality_residual);
    state.counters["compl"]               = counter(kkt_error.complementarity);
} catch (const std::exception &e) {
    state.SkipWithError(e.what());
}
template <index_t VL, qp::StorageOrder Order>
void run_benchmark_serial(benchmark::State &state, [[maybe_unused]] const std::string &param_name,
                   const CentroidalQuadrupedParams &params, qp::CyQPALMBackendSettings backend_settings,
                   qp::Settings settings, index_t num_branches, bool warm = false, bool trace = false) try {
    disable_tracing(); // No tracing during the actual benchmark
    if (backend_settings.processors < 1)
        return state.SkipWithMessage("Number of processors must be at least 1.");
    auto problem = create_problem(params,num_branches);
    // Build a QPALM Cyqlone solver
    auto ocp     = cyqlone::FanCyqloneStorage<>::build(problem.ocp);
    auto backend = qp::make_cyqpalm_backend<VL, Order, cyqlone::SerialFanCyqloneSolver<VL>>(ocp, {}, backend_settings);
    qp::Solver<qp::CyQPALMBackend<VL, Order, cyqlone::SerialFanCyqloneSolver<VL>> *> qpalm{backend.get(), settings};
    // Main benchmark
    qp::SolverStatus status;
    double time_solve = 0, time_active_set_change = 0, time_line_search = 0,
           time_recompute_outer = 0, time_recompute_inner = 0, time_mat_vec = 0;
    qpalm(); // Warm up

    if (warm) {
        // std::cout << "Warm starting SerialFanCyqlone" << std::endl;
        const auto nx = problem.ocp.ocps.front().dim.nx, nu = problem.ocp.ocps.front().dim.nu;
        // std::cout << "Warm starting with nx = " << nx << ", nu = " << nu << std::endl;
        qpalm.warm_start_solution();
        // std::cout << "Warm starting done" << std::endl;
        auto x = qpalm.get_solution();
        index_t offset = num_branches/2 * ((nu + nx)*problem.ocp.ocps.front().dim.N_horiz-nu);
        
        for (index_t j = 0; j < num_branches; ++j) {
            std::copy_n(x.data() + nu+ offset, nx, problem.ocp.ocps[j].b(0).data);
        }
        // std::copy_n(x.data() + nu, nx, problem.ocp.ocps.front().b(0).data);
        // std::cout << "Updating ocp and backend for warm start" << std::endl;
        ocp.update(problem.ocp);
        update_cyqpalm_backend(*qpalm.backend, ocp);
    }
    for (auto _ : state) {
        status = qpalm();
        state.SetIterationTime(seconds(qpalm.stats->timings.total.wall_time).count());
        time_solve += seconds(qpalm.stats->timings.solve.wall_time).count();
        time_active_set_change += seconds(qpalm.stats->timings.active_set_change.wall_time).count();
        time_line_search += seconds(qpalm.stats->timings.line_search.wall_time).count();
        time_recompute_outer += seconds(qpalm.stats->timings.recompute_outer.wall_time).count();
        time_recompute_inner += seconds(qpalm.stats->timings.recompute_inner.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_A.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_AT.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_M.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_MT.wall_time).count();
        time_mat_vec += seconds(qpalm.stats->timings.mat_vec_Q.wall_time).count();
    }
    if (trace)
        trace_run([&] { qpalm(); }, param_name);
    auto sol       = ocp.reconstruct_solution(problem.ocp, qpalm.get_solution(),
                                              qpalm.get_inequality_multipliers(),
                                              qpalm.get_equality_multipliers());
    std::vector<cyqlone::OCPDim> OCPdims;
    for (const auto &ocp : problem.ocp.ocps) {
        OCPdims.push_back(ocp.dim);
    }
    // sol.print(OCPdims);
    auto kkt_error = problem.ocp.compute_kkt_error(sol);
    // std::cout << "kkt_error: " << kkt_error.stationarity << ", " << kkt_error.equality_residual << ", "
    //           << kkt_error.inequality_residual << ", " << kkt_error.complementarity << std::endl;
    state.counters["status"]              = counter(status);
    state.counters["success"]             = counter(status == qp::SolverStatus::Converged);
    state.counters["iter"]                = counter(qpalm.stats->inner_iter);
    state.counters["outer_iter"]          = counter(qpalm.stats->outer_iter);
    state.counters["num_factor"]          = counter(qpalm.stats_backend->num_factor);
    state.counters["num_upd"]             = counter(qpalm.stats_backend->num_updates);
    state.counters["rank_upd"]            = counter(qpalm.stats_backend->rank_updates);
    state.counters["t_solve"]             = counter_avg(time_solve);
    state.counters["t_active_set_change"] = counter_avg(time_active_set_change);
    state.counters["t_line_search"]       = counter_avg(time_line_search);
    state.counters["t_recompute_outer"]   = counter_avg(time_recompute_outer);
    state.counters["t_recompute_inner"]   = counter_avg(time_recompute_inner);
    state.counters["t_mat_vec"]           = counter_avg(time_mat_vec);
    state.counters["res_dual"]            = counter(kkt_error.stationarity);
    state.counters["res_eq"]              = counter(kkt_error.equality_residual);
    state.counters["res_ineq"]            = counter(kkt_error.inequality_residual);
    state.counters["compl"]               = counter(kkt_error.complementarity);
} catch (const std::exception &e) {
    state.SkipWithError(e.what());
}
enum class WarmStartHPIPM {
    NoWarmStart,
    WarmZero,
    WarmCopy,
    WarmShift,
};

#if WITH_HPIPM
void run_benchmark_hpipm(benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches,
                             WarmStartHPIPM warm = WarmStartHPIPM::NoWarmStart, int mode = 0) {
        // std::cout << "Running HPIPM benchmark with " << num_branches << " branches" << std::endl;
    auto problem     = create_problem(params,num_branches);
    // std::cout << "Building HPIPM QP with stages" << std::endl;
    const bool cold = warm == WarmStartHPIPM::NoWarmStart || warm == WarmStartHPIPM::WarmZero;
    auto qp_data     = build_hpipm_tree_qp(problem.ocp, 1, 1);
    auto solver_data = create_hpipm_tree_solver(qp_data, (warm != WarmStartHPIPM::NoWarmStart&&warm != WarmStartHPIPM::WarmZero) ? 2 : 0, mode, 1e-8, 0);
    // Main benchmark
    solve_hpipm_tree(*qp_data, *solver_data); // Warm up
    std::optional<cyqlone::FanOCPStorage::Solution> prev_sol;
    if (warm == WarmStartHPIPM::WarmCopy) {
        prev_sol = get_solution_hpipm_tree(*solver_data);
        update_x0_hpipm_tree(problem.ocp, *qp_data, prev_sol->solutions, num_branches/2);
        // std::cout << "Warm starting with solution from previous solve" << std::endl;
    }
    if (warm == WarmStartHPIPM::WarmShift) {
        shift_hpipm_tree_solution(*solver_data);
        prev_sol = get_solution_hpipm_tree(*solver_data);
        update_x0_hpipm_tree(problem.ocp, *qp_data, prev_sol->solutions, num_branches/2);
        // std::cout << "Warm starting with solution from previous solve" << std::endl;
    }
    for (auto _ : state) {
        auto time_solve = solve_hpipm_tree(*qp_data, *solver_data);

        state.SetIterationTime(seconds(time_solve).count());
    }
    auto sol                       = get_solution_hpipm_tree(*solver_data);
    // std::vector<cyqlone::OCPDim> OCPdims;
    // for (const auto &ocp : problem.ocp.ocps) {
    //     OCPdims.push_back(ocp.dim);
    // }
    // sol.print(OCPdims);

    auto kkt_error                 = problem.ocp.compute_kkt_error(sol,true);
    auto stats                     = get_stats_hpipm_tree(*solver_data);
    state.counters["status"]       = counter(stats.status);
    state.counters["success"]      = counter(stats.status == 0);
    state.counters["iter"]         = counter(stats.iter);
    state.counters["max_res_stat"] = counter(stats.max_res_stat);
    state.counters["max_res_eq"]   = counter(stats.max_res_eq);
    state.counters["max_res_ineq"] = counter(stats.max_res_ineq);
    state.counters["max_res_comp"] = counter(stats.max_res_comp);
    state.counters["res_dual"]     = counter(kkt_error.stationarity);
    state.counters["res_eq"]       = counter(kkt_error.equality_residual);
    state.counters["res_ineq"]     = counter(kkt_error.inequality_residual);
    state.counters["compl"]        = counter(kkt_error.complementarity);
}
#endif
#if WITH_TREEQP

void run_benchmark_treeqp(
    benchmark::State &state,
    const CentroidalQuadrupedParams &params,
    index_t num_branches,
    bool cold_start,
    bool clipping =false
)
{
    auto problem = create_problem(params, num_branches);

    auto qp_data = build_tree_qp(problem.ocp,clipping);
       
    auto solver_data = create_tree_qp_solver(
        qp_data,
        200,   // Maximum number of iterations
        1e-8); // Stationarity tolerance

    // Warm-up solve.
    solve_tree_qp(*qp_data, *solver_data);
    const auto prev_solution =
            get_solution_tree_qp(*solver_data);
   
    for (auto _ : state) {
        if (!cold_start) {
        
            update_x0_tree_qp(
                problem.ocp,
                *qp_data,
                prev_solution.solutions,
                num_branches / 2);
        
            shift_treeqp_solution(*solver_data,prev_solution);
            }
        else {
            // Reset the solver to a cold start.
            reset_treeqp_solution(*solver_data);
        }
        const auto time_solve =
            solve_tree_qp(*qp_data, *solver_data, cold_start);

        state.SetIterationTime(
            seconds(time_solve).count());
    }

    const auto solution =
        get_solution_tree_qp(*solver_data);
    std::vector<cyqlone::OCPDim> OCPdims;
    for (const auto &ocp : problem.ocp.ocps) {
        OCPdims.push_back(ocp.dim);
    }
    // solution.print(OCPdims);
    const auto stats =
        get_stats_tree_qp(*solver_data);

    state.counters["status"] =
        counter(stats.status);

    state.counters["success"] =
        counter(stats.status == 0);

    state.counters["iter"] =
        counter(stats.iterations);

    const auto kkt_error =
        problem.ocp.compute_kkt_error(
            solution,
            true);
    state.counters["res_dual"] =
        counter(kkt_error.stationarity);
    state.counters["res_eq"] =
        counter(kkt_error.equality_residual);
    state.counters["res_ineq"] =
        counter(kkt_error.inequality_residual);
    state.counters["compl"] =
        counter(kkt_error.complementarity);
}

#endif
#if WITH_PIQP

void run_benchmark_piqp(
    benchmark::State &state,
    const CentroidalQuadrupedParams &params,
    index_t num_branches)
{
    auto problem =
        create_problem(params, num_branches);

    auto qp_data =
        build_piqp_fan_qp(problem.ocp);

    auto solver_data =
        create_piqp_fan_solver(qp_data);

    // Initial unmeasured solve, consistent with the HPIPM benchmark.
    solve_piqp_fan(*solver_data);

    for (auto _ : state) {
        const auto time_solve =
            solve_piqp_fan(*solver_data);

        state.SetIterationTime(
            seconds(time_solve).count());
    }

    const auto solution =
        get_solution_piqp_fan(*solver_data);

    const auto kkt_error =
        problem.ocp.compute_kkt_error(
            solution,
            true);
    // std::vector<cyqlone::OCPDim> OCPdims;
    // for (const auto &ocp : problem.ocp.ocps) {
    //     OCPdims.push_back(ocp.dim);
    // }
    // solution.print(OCPdims);
    const auto stats =
        get_stats_piqp_fan(*solver_data);

    state.counters["status"] =
        counter(static_cast<int>(stats.status));

    state.counters["success"] =
        counter(
            stats.status ==
            piqp::Status::PIQP_SOLVED);

    state.counters["iter"] =
        counter(stats.iter);

    state.counters["res_dual"] =
        counter(kkt_error.stationarity);

    state.counters["res_eq"] =
        counter(kkt_error.equality_residual);

    state.counters["res_ineq"] =
        counter(kkt_error.inequality_residual);

    state.counters["compl"] =
        counter(kkt_error.complementarity);
}

#endif
struct Problem {
    std::string name;
    CentroidalQuadrupedParams params;
    index_t num_branches;
};

std::generator<Problem> get_quad_params(const Options &opts) {
    using std::format;
        for (auto N : opts.horizon)
            for (uint64_t seed = opts.seed; seed < opts.seed + opts.num_instances; ++seed)
                for(auto J : opts.num_branches)
                        co_yield {
                                .name   = format("centroidal-quadruped(N={},J={},seed={})", N, J, seed),
                                .params = CentroidalQuadrupedParams(N, seed, 0.64/N, 5e-5, 1e-8),
                                .num_branches = J
                        };                        
    }

// void export_problem(const Options &opts ) {
//     if (opts.export_problem.empty())
//         return;
//     for (const auto &params : get_spring_mass_params(opts)) {
//         auto problem      = create_problem(params.params,params.num_branches);
//         fs::path filename = opts.export_problem;
//         if (fs::is_directory(filename))
//             filename /= params.name + ".mat";
//         auto mat = cyqlone::create_mat(filename);
//         cyqlone::add_to_mat(mat.get(), "ocp", problem.ocp);
//         std::cout << "Exported problem " << params.name << " to " << filename << std::endl;
//         break;
//     }
// }

struct Solver {
    std::string name;
    std::function<void(benchmark::State &, CentroidalQuadrupedParams, index_t)> run;
};

std::string_view order(qp::StorageOrder o) { return o == qp::StorageOrder::RowMajor ? "rm" : "cm"; }

template <index_t VL, qp::StorageOrder O>
std::generator<Solver> get_cyqlone_solvers(const Options &opts) {
    const auto cyqlone_solver = [trace{opts.trace}](std::string_view name,
                                                    const qp::CyQPALMBackendSettings &backend,
                                                    const qp::Settings &settings) {
        const auto param_name =
            std::format("fancyqlone(p={},v={},{},{})", backend.processors, VL, order(O), name);
        return Solver{param_name, [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                          run_benchmark<VL, O>(state, param_name, params, backend, settings, num_branches, backend.strategy!= qp::WarmStartingStrategy::Zeros ? true : false,
                                               trace);
                      }};
    };
    const auto serial_cyqlone_solver = [trace{opts.trace}](std::string_view name,
                                                    const qp::CyQPALMBackendSettings &backend,
                                                    const qp::Settings &settings) {
        const auto param_name =
            std::format("serial-fancyqlone(p={},v={},{},{})", backend.processors, VL, order(O), name);
        return Solver{param_name, [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                          run_benchmark_serial<VL, O>(state, param_name, params, backend, settings, num_branches, backend.strategy!= qp::WarmStartingStrategy::Zeros ? true : false,
                                               trace);
                      }};
    };
    bool verbose = false;
    for (auto p : opts.parallelism) {
        qp::CyQPALMBackendSettings backend{
            .processors             = p,
            .print_residuals        = verbose,
            .print_precision        = 17,
            .changing_constr_factor = 0,
            .max_update_count       = 0,
            .tricyqle_params =
                {
                    .solve_method = cyqlone::SolveMethod::None,

                },
            .spin_count = std::numeric_limits<uint32_t>::max(), // disable spin count limit, since the fan solver can have a long first iteration due to the coupling

        };
        qp::Settings settings{
            .tolerance = 1e-8,
            .dual_tolerance = 1e-8,
            .eq_constr_tolerance = 1e-8,
            .initial_inner_tolerance = 1e-4,
            .initial_penalty_y = 20,
            .verbose           = verbose,
            .detailed_stats       = verbose,

        };
        qp::CyQPALMBackendSettings backend_no_upd = backend;

        qp::Settings settings_warm                = settings;
        settings_warm.initial_penalty_y           = 1e4;
        settings_warm.initial_inner_tolerance     = 1e-4;
        if (opts.cold) {
            std::cout << "Running cold start solver with " << p << " processors" << std::endl;
            backend.strategy = backend_no_upd.strategy = qp::WarmStartingStrategy::Zeros;

            co_yield cyqlone_solver("zero", backend, settings);
            if (opts.serial)
                co_yield serial_cyqlone_solver("zero", backend, settings);  
    
        }
        if (opts.warm_shift) {
            backend.strategy = backend_no_upd.strategy = qp::WarmStartingStrategy::Shift;
            std::cout << "Running warm start (shift) solver with " << p << " processors" << std::endl;
            co_yield cyqlone_solver("shift", backend, settings_warm);
            // if (opts.no_updates)
            //     co_yield cyqlone_solver("shift,upd=0", backend_no_upd, settings_warm);
            // if (opts.serial)
            //     co_yield serial_cyqlone_solver("shift", backend, settings_warm);
        }
        if (opts.warm_copy) {
            std::cout << "Running warm start (copy) solver with " << p << " processors" << std::endl;
            backend.strategy = backend_no_upd.strategy = qp::WarmStartingStrategy::Copy;
            co_yield cyqlone_solver("copy", backend, settings_warm);
            // if (opts.serial)
            //     co_yield serial_cyqlone_solver("copy", backend, settings_warm);
            // if (opts.no_updates)
            //     co_yield cyqlone_solver("copy,upd=0", backend_no_upd, settings_warm);
        }
    }
}

std::generator<Solver> get_hpipm_solvers(const Options &opts) {
    if (opts.hpipm) {
#if WITH_HPIPM
        if (opts.cold){
            co_yield {"hpipm(zero)", [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                          run_benchmark_hpipm(state, params, num_branches, WarmStartHPIPM::WarmZero, 0);
                      }};
            co_yield {"hpipm(zero,balance)", [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                          run_benchmark_hpipm(state, params, num_branches, WarmStartHPIPM::NoWarmStart, 1);
                      }};
}
        if (opts.warm_shift)
        {
            co_yield {"hpipm(shift)", [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                          run_benchmark_hpipm(state, params, num_branches, WarmStartHPIPM::WarmShift, 0);
                      }};
            co_yield {"hpipm(shift,balance)", [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                          run_benchmark_hpipm(state, params, num_branches, WarmStartHPIPM::WarmShift, 1);
                      }};
        }
        if (opts.warm_copy){
            co_yield {"hpipm(copy)", [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                          run_benchmark_hpipm(state, params, num_branches, WarmStartHPIPM::WarmCopy, 0);
                      }};
            // co_yield {"hpipm(copy,balance)", [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
            //               run_benchmark_hpipm(state, params, num_branches, WarmStartHPIPM::WarmCopy, 1);
            //           }}; 
            }
#else
        throw std::invalid_argument("HPIPM support not enabled in this build");
#endif
    }
}
std::generator<Solver> get_treeqp_solvers(const Options &opts)
{
    if (opts.treeqp) {
#if WITH_TREEQP
        co_yield {
            "treeqp(qpOasis)",
            [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                run_benchmark_treeqp(
                    state,
                    params,
                    num_branches,
                    opts.cold,
                    false
                );
            }};
        if (opts.warm_shift) {
        co_yield {
            "treeqp(qpOasis,shift)",
            [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                run_benchmark_treeqp(
                    state,
                    params,
                    num_branches,
                    false,
                    false
                );
            }};
        }
            //    co_yield {
            // "treeqp(QPOasis)",
            // [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
            //     run_benchmark_treeqp(
            //         state,
            //         params,
            //         num_branches,
            //         opts.cold,
            //         false
            //     );
            // }};
#else
        throw std::invalid_argument(
            "TREEQP support not enabled in this build");
#endif
    }
}
std::generator<Solver> get_piqp_solvers(const Options &opts)
{
    if (opts.piqp) {
#if WITH_PIQP
        co_yield {
            "piqp(multistage)",
            [=](benchmark::State &state, const CentroidalQuadrupedParams &params, index_t num_branches) {
                run_benchmark_piqp(
                    state,
                    params,
                    num_branches);
            }};
#else
        throw std::invalid_argument(
            "PIQP support not enabled in this build");
#endif
    }
}

using std::ranges::elements_of;

template <qp::StorageOrder Order>
std::generator<Solver> get_cyqlone_solvers_vl(const Options &opts) {
    static constexpr auto VLs       = batmat::types::vl_for_real_t;
    static constexpr auto to_string = [](auto vl) { return std::to_string(vl); };
    static constexpr auto lut = guanaqo::make_lut<VLs>([]<index_t VL>(batmat::index_constant<VL>) {
        return std::make_pair(VL, get_cyqlone_solvers<VL, Order>);
    });
    for (auto v : opts.vector_length) {
        auto dispatch = std::ranges::find(lut, v, &decltype(lut)::value_type::first);
        if (dispatch == lut.end())
            throw std::invalid_argument("Unsupported vector length. Supported lengths: " +
                                        guanaqo::join(std::views::transform(VLs, to_string)));
        co_yield elements_of(dispatch->second(opts));
    }
}

std::generator<Solver> get_solvers(const Options &opts) {
#if WITH_HPIPM
    co_yield elements_of(get_hpipm_solvers(opts));
#endif
#if WITH_PIQP
    co_yield elements_of(get_piqp_solvers(opts));
#endif
#if WITH_TREEQP
    co_yield elements_of(get_treeqp_solvers(opts));
#endif
    // if (opts.rm)
    //     co_yield elements_of(get_cyqlone_solvers_vl<qp::StorageOrder::ColMajor>(opts));
    // if (opts.cm)
    co_yield elements_of(get_cyqlone_solvers_vl<qp::StorageOrder::ColMajor>(opts));

}

auto register_benchmarks(const Options &opts) {
    size_t max_problem_name_len = 0;
    size_t max_solver_name_len  = 0;
    for (auto problem : get_quad_params(opts)) {

        max_problem_name_len = std::max(max_problem_name_len, problem.name.size());
        for (auto solver : get_solvers(opts)) {
            max_solver_name_len = std::max(max_solver_name_len, solver.name.size());
            benchmark::RegisterBenchmark(std::format("{}@{}", problem.name, solver.name),
                                         [params = problem.params, run = std::move(solver.run), num_branches = problem.num_branches](
                                             benchmark::State &state) { run(state, params, num_branches); })
                ->MeasureProcessCPUTime()
                ->UseManualTime()
                ->Unit(benchmark::kMillisecond)
                ->ComputeStatistics("max", [](auto &v) { return *std::ranges::max_element(v); })
                ->ComputeStatistics("min", [](auto &v) { return *std::ranges::min_element(v); })
                ->GetName();
        }
    }
    return std::make_pair(max_problem_name_len, max_solver_name_len);
}

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
    app.footer(std::format("Benchmark options are passed to the Google Benchmark framework. "
                           "Use {} -- --help or see "
                           "https://google.github.io/benchmark/user_guide.html for details.",
                           program));
    app.allow_extras();
    app.add_flag("--cold,!--no-cold", opts.cold, "Benchmark with cold starting");
    app.add_flag("--warm-shift,!--no-warm-shift", opts.warm_shift,
                 "Benchmark with warm starting (shift)");
    app.add_flag("--warm-copy,!--no-warm-copy", opts.warm_copy,
                 "Benchmark with warm starting (copy)");
    app.add_option("--horizon,-N", opts.horizon, "Specify a horizon length to benchmark");
    app.add_option("--num-branches,-J", opts.num_branches, "Specify the number of branches to benchmark");
    app.add_option("--num-instances,-I", opts.num_instances,
                   "Number of random problem instances to generate for each (M,N) pair");
    app.add_option("--seed,-s", opts.seed, "Random seed for problem instance generation");
    app.add_flag("--no-updates", opts.no_updates, "Compare to the Cyqlone backend without updates");
    app.add_option("--parallelism,-p", opts.parallelism,
                   "The number of threads to use in the Cyqlone backend");
    app.add_option("--vector-length,-v", opts.vector_length,
                   "The vector length to use in the Cyqlone backend");
    app.add_flag("--rm,!--no-rm", opts.rm, "Use row-major (default) storage");
    app.add_flag("--cm,!--no-cm", opts.cm, "Use column-major storage");
    app.add_flag("--pcr,!--pcg", opts.pcr, "Use parallel cyclic reduction in the Cyqlone backend");
    app.add_flag("--hpipm,!--no-hpipm", opts.hpipm, "Use HPIPM solver for comparison");
    app.add_option("--export-problem", opts.export_problem,
                   "Export a single problem instance to a .mat file");
    app.add_flag("--trace,!--no-trace", opts.trace, "Enable tracing of CyQPALM solver runs");
    app.add_flag("--custom-reporter,!--no-custom-reporter", opts.custom_reporter,
                 "Use custom benchmark reporter");
    app.add_flag("--print-extra,!--no-print-extra", opts.print_extra,
                 "Print additional counters in the benchmark report");
    app.add_flag("--color,!--no-color", opts.use_color, "Enable/disable colored output");
    app.add_flag("--serial,!--no-serial", opts.serial, "Use serial implementation");

}

int initialize_google_benchmark(char *program, auto bm_args) {
    if (!bm_args.empty() && bm_args.front() == "--")
        bm_args.erase(bm_args.begin());
    std::vector<char *> bm_argv(bm_args.size() + 2);
    std::ranges::transform(bm_args, bm_argv.begin() + 1, [](auto &s) { return s.data(); });
    bm_argv[0]   = program;
    auto bm_argc = static_cast<int>(bm_args.size()) + 1;
    benchmark::Initialize(&bm_argc, bm_argv.data());
    if (benchmark::ReportUnrecognizedArguments(bm_argc, bm_argv.data()))
        return 1;
    return 0;
}

void register_context() {
#if BATMAT_WITH_OPENMP
    auto places = std::getenv("OMP_PLACES");
    benchmark::AddCustomContext("OMP_NUM_THREADS", std::to_string(omp_get_max_threads()));
    benchmark::AddCustomContext("OMP_PLACES", places ? places : "");
#endif
    benchmark::AddCustomContext("batmat_build_time", batmat_build_time);
    benchmark::AddCustomContext("batmat_commit_hash", batmat_commit_hash);
    benchmark::AddCustomContext("cyqlone_build_time", cyqlone_build_time);
    benchmark::AddCustomContext("cyqlone_commit_hash", cyqlone_commit_hash);
    benchmark::AddCustomContext("real_t", guanaqo::demangled_typename(typeid(real_t)));
    benchmark::AddCustomContext("index_t", guanaqo::demangled_typename(typeid(index_t)));
#if GUANAQO_WITH_MKL
    MKLVersion Version;
    mkl_get_version(&Version);
    benchmark::AddCustomContext("blas_library", "MKL");
    benchmark::AddCustomContext("blas_version",
                                std::format("{}.{}.{} ({}) for {}: {}", Version.MajorVersion,
                                            Version.MinorVersion, Version.UpdateVersion,
                                            Version.Build, Version.Platform, Version.Processor));
#elif GUANAQO_WITH_OPENBLAS
    benchmark::AddCustomContext("blas_library", "OpenBLAS");
    benchmark::AddCustomContext("blas_version", OPENBLAS_VERSION);
#endif
#if defined(__INTEL_LLVM_COMPILER)
    benchmark::AddCustomContext("compiler", "intel-llvm");
    benchmark::AddCustomContext("compiler_version", __VERSION__);
#elif defined(__clang__)
    benchmark::AddCustomContext("compiler", "clang");
    benchmark::AddCustomContext("compiler_version", __VERSION__);
#elif defined(__GNUC__)
    benchmark::AddCustomContext("compiler", "gcc");
    benchmark::AddCustomContext("compiler_version", __VERSION__);
#elif defined(_MSC_VER)
    benchmark::AddCustomContext("compiler", "msvc");
    benchmark::AddCustomContext("compiler_version", GUANAQO_STRINGIFY(_MSC_FULL_VER));
#endif
#if defined(__AVX512F__)
    benchmark::AddCustomContext("arch", "avx512f");
#elif defined(__AVX2__)
    benchmark::AddCustomContext("arch", "avx2");
#elif defined(__AVX__)
    benchmark::AddCustomContext("arch", "avx");
#elif defined(__SSE3__)
    benchmark::AddCustomContext("arch", "sse3");
#elif defined(__ARM_NEON)
    benchmark::AddCustomContext("arch", "neon");
#endif
#if BATMAT_WITH_GSI_HPC_SIMD
    benchmark::AddCustomContext("simd_library", "GSI-HPC/simd");
#else
    benchmark::AddCustomContext("simd_library", "libstdc++ <experimental/simd>");
#endif
}

int main(int argc, char **argv) try {
#if GUANAQO_WITH_PERFETTO
    guanaqo::trace::initialize_tracing();
#endif
    char *const program = argv[0];
    CLI::App app{"CyQPALM and Cyqlone Spring-Mass Benchmarks"};
    Options opts;
    register_options(program, app, opts);
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }
    // export_problem(opts);
    auto [problem_name_width, solver_name_width] = register_benchmarks(opts);
    if (auto err = initialize_google_benchmark(program, app.remaining(true)); err != 0)
        return err;
    register_context();
    auto reporter = opts.custom_reporter
                        ? make_custom_reporter(problem_name_width, solver_name_width + 2,
                                               opts.print_extra, opts.use_color)
                        : nullptr;
    benchmark::RunSpecifiedBenchmarks(reporter.get());
    print_traces(std::cout);
    benchmark::Shutdown();
} catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
}
