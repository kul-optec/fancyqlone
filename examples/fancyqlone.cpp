#include "fancyqlone/fancyqlone/fancyqlone.hpp"
#include "fancyqlone/cyqlone/cyqlone-storage.hpp"
#include <fancyqlone/conversion.hpp>
#include <fancyqlone/cyqlone/cyqlone.hpp>
#include <fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.hpp>
#include <fancyqlone/fancyqpalm/solver.hpp>
#include <fancyqlone/random-ocp.hpp>
#include <fancyqlone/tracing.hpp>

#include "fancyqlone/matio.hpp"
#include "fancyqlone/ocp.hpp"
#include <cyqlone-version.h>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <span>
#include <string>
#include <vector>
using fancyqlone::index_t;
using fancyqlone::real_t;
using fancyqlone::StorageOrder;
// Include whatever header contains these helpers:
//   combine_branches_0
//   compare_combined_normal, if you still want comparison
// #include "test-helpers.hpp"
fancyqlone::LinearOCPStorage
combine_branches_0(std::span<const fancyqlone::LinearOCPStorage> ocps) {
    BATMAT_ASSERT(!ocps.empty());
    auto fld_max = [](index_t(fancyqlone::OCPDim::*m)) {
        return [m](index_t acc, const auto &ocp) { return std::max(acc, ocp.dim.*m); };
    };
    auto fld_sum = [](index_t(fancyqlone::OCPDim::*m)) {
        return [m](index_t acc, const auto &ocp) { return acc + ocp.dim.*m; };
    };
    fancyqlone::OCPDim dim{
        .N_horiz = std::ranges::fold_left(ocps, index_t{0}, fld_max(&fancyqlone::OCPDim::N_horiz)),
        .nx      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&fancyqlone::OCPDim::nx)),
        .nu      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&fancyqlone::OCPDim::nu)),
        .ny      = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&fancyqlone::OCPDim::ny)),
        .ny_N    = std::ranges::fold_left(ocps, index_t{0}, fld_sum(&fancyqlone::OCPDim::ny_N)),
    }; // TODO: this is a bit redundant, since x(0) and u(0) need to have consistent dimensions
    fancyqlone::LinearOCPStorage combined_ocp(dim);

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

    const index_t nx_max =
                      std::ranges::fold_left(ocps, index_t{0}, fld_max(&fancyqlone::OCPDim::nx)),
                  nu_max =
                      std::ranges::fold_left(ocps, index_t{0}, fld_max(&fancyqlone::OCPDim::nu));
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
struct BenchConfig {
    fancyqlone::index_t N            = 256;
    fancyqlone::index_t nx           = 18;
    fancyqlone::index_t nu           = 9;
    fancyqlone::index_t ny           = 5;
    fancyqlone::index_t ny_N         = 0;
    fancyqlone::index_t num_branches = 2;
    fancyqlone::index_t processors   = 8;
    fancyqlone::index_t warmup       = 50;
    double tolerance                 = 1e-7;
    std::uint32_t seed_base          = 1000;
    std::string out_file             = "fan_qpalm_timings.csv";
    bool verbose                     = false;
    bool check_solution              = true;
};

static bool get_arg(int argc, char **argv, const std::string &name, std::string &value) {
    for (int i = 1; i + 1 < argc; ++i) {
        if (argv[i] == name) {
            value = argv[i + 1];
            return true;
        }
    }
    return false;
}

template <class T>
static void parse_arg(int argc, char **argv, const std::string &name, T &value) {
    std::string s;
    if (!get_arg(argc, argv, name, s))
        return;

    if constexpr (std::is_integral_v<T>) {
        value = static_cast<T>(std::stoll(s));
    } else if constexpr (std::is_floating_point_v<T>) {
        value = static_cast<T>(std::stod(s));
    } else {
        value = s;
    }
}

static BenchConfig parse_config(int argc, char **argv) {
    BenchConfig cfg;

    parse_arg(argc, argv, "--N", cfg.N);
    parse_arg(argc, argv, "--nx", cfg.nx);
    parse_arg(argc, argv, "--nu", cfg.nu);
    parse_arg(argc, argv, "--ny", cfg.ny);
    parse_arg(argc, argv, "--ny-N", cfg.ny_N);
    parse_arg(argc, argv, "--branches", cfg.num_branches);
    parse_arg(argc, argv, "--processors", cfg.processors);
    parse_arg(argc, argv, "--warmup", cfg.warmup);
    parse_arg(argc, argv, "--tol", cfg.tolerance);
    parse_arg(argc, argv, "--seed-base", cfg.seed_base);
    parse_arg(argc, argv, "--out", cfg.out_file);

    std::string verbose;
    if (get_arg(argc, argv, "--verbose", verbose))
        cfg.verbose = verbose == "1" || verbose == "true";

    std::string check;
    if (get_arg(argc, argv, "--check", check))
        cfg.check_solution = check == "1" || check == "true";

    return cfg;
}

template <class DurationLike>
static double seconds_from_duration(const DurationLike &duration) {
    return std::chrono::duration<double>(duration).count();
}

static void write_csv_header_if_needed(const std::filesystem::path &file) {
    const bool write_header =
        !std::filesystem::exists(file) || std::filesystem::file_size(file) == 0;

    if (!write_header)
        return;

    std::ofstream csv(file, std::ios::app);

    csv << "N,nx,nu,ny,ny_N,num_branches,num_proc,"
        << "fan_status,sfan_status, combined_status,"
        << "fan_inner,fan_outer,sfan_inner,sfan_outer, combined_inner,combined_outer,"
        << "fan_time_s,combined_time_s,speedup, speedup_serial\n";
}

static std::string status_to_string(fancyqlone::qpalm::SolverStatus status) {
    using fancyqlone::qpalm::SolverStatus;

    switch (status) {
        case SolverStatus::Converged: return "Converged";
        case SolverStatus::MaxIter: return "MaxIter";
        default: return "Other";
    }
}

template <fancyqlone::index_t VL>
static int run_benchmark(const BenchConfig &cfg) {
    using fancyqlone::index_t;
    using fancyqlone::real_t;
    namespace qp = fancyqlone::qpalm;

    constexpr auto Order = StorageOrder::ColMajor;

    fancyqlone::OCPDim dim{
        .N_horiz = cfg.N,
        .nx      = cfg.nx,
        .nu      = cfg.nu,
        .ny      = cfg.ny,
        .ny_N    = cfg.ny_N,
    };

    std::vector<fancyqlone::LinearOCPStorage> ocps(cfg.num_branches);

    for (index_t i = 0; i < cfg.num_branches; ++i) {
        ocps[i] =
            fancyqlone::generate_random_ocp_input_constr(dim, static_cast<std::uint32_t>(1000 + i));
        std::cout << "Fan OCP" << i << " has N=" << ocps[i].dim.N_horiz << ", nx=" << ocps[i].dim.nx
                  << ", nu=" << ocps[i].dim.nu << ", ny=" << ocps[i].dim.ny
                  << ", ny_N=" << ocps[i].dim.ny_N << "\n";
        ;

        if (i != 0) {
            ocps[i].b_max(0).set_constant(std::numeric_limits<real_t>::infinity());
            ocps[i].b_min(0).set_constant(-std::numeric_limits<real_t>::infinity());
        }
    }

    // -------------------------------------------------------------------------
    // Fan solver
    // -------------------------------------------------------------------------
    fancyqlone::FanOCPStorage fan_ocp{
        .ocps = ocps,
    };

    auto fan_cocp = fancyqlone::FanCyqloneStorage<>::build(fan_ocp, dim.ny);

    auto &&fan_backend =
        qp::make_cyqpalm_backend<VL, StorageOrder::ColMajor, fancyqlone::FanCyqloneSolver<VL>>(
            fan_cocp, {},
            {
                .processors             = cfg.processors,
                .print_residuals        = cfg.verbose,
                .print_precision        = 17,
                .changing_constr_factor = 0,
                .max_update_count       = 0,
                .tricyqle_params =
                    {
                        .solve_method = fancyqlone::SolveMethod::None,
                    },
                .spin_count = std::numeric_limits<std::uint32_t>::max(),
            });

    qp::Solver<qp::CyQPALMBackend<VL, Order, fancyqlone::FanCyqloneSolver<VL>> *> fan_qpalm{
        fan_backend.get(),
        {
            .max_outer_iter       = 100,
            .max_total_inner_iter = 1000,
            .tolerance            = cfg.tolerance,
            .verbose              = cfg.verbose,
            .detailed_stats       = cfg.verbose,
        },
    };

    for (index_t i = 0; !cfg.verbose && i < cfg.warmup; ++i)
        fan_qpalm();

    auto fan_status = fan_qpalm();

    auto x_fan          = fan_qpalm.get_solution();
    auto lambda_fan     = fan_qpalm.get_equality_multipliers();
    auto &&sfan_backend = qp::make_cyqpalm_backend<VL, StorageOrder::ColMajor,
                                                   fancyqlone::SerialFanCyqloneSolver<VL>>(
        fan_cocp, {},
        {
            .processors             = cfg.processors,
            .print_residuals        = cfg.verbose,
            .print_precision        = 17,
            .changing_constr_factor = 0,
            .max_update_count       = 0,
            .tricyqle_params =
                {
                    .solve_method = fancyqlone::SolveMethod::None,
                },
            .spin_count = std::numeric_limits<std::uint32_t>::max(),
        });

    qp::Solver<qp::CyQPALMBackend<VL, Order, fancyqlone::SerialFanCyqloneSolver<VL>> *> sfan_qpalm{
        sfan_backend.get(),
        {
            .max_outer_iter       = 100,
            .max_total_inner_iter = 1000,
            .tolerance            = cfg.tolerance,
            .verbose              = cfg.verbose,
            .detailed_stats       = cfg.verbose,
        },
    };

    for (index_t i = 0; !cfg.verbose && i < cfg.warmup; ++i)
        sfan_qpalm();

    auto sfan_status = sfan_qpalm();

    auto x_sfan      = sfan_qpalm.get_solution();
    auto lambda_sfan = sfan_qpalm.get_equality_multipliers();
    // -------------------------------------------------------------------------
    // Combined solver
    // -------------------------------------------------------------------------
    auto combined_ocp  = combine_branches_0(ocps);
    auto combined_cocp = fancyqlone::CyqloneStorage<>::build(combined_ocp);

    auto &&combined_backend = qp::make_cyqpalm_backend<VL, Order, fancyqlone::CyqloneSolver<VL>>(
        combined_cocp, {},
        {
            .processors             = cfg.processors,
            .print_residuals        = cfg.verbose,
            .print_precision        = 17,
            .changing_constr_factor = 0,
            .max_update_count       = 0,
            .tricyqle_params =
                {
                    .solve_method = fancyqlone::SolveMethod::PCR,
                },
        });

    qp::Solver<qp::CyQPALMBackend<VL, Order, fancyqlone::CyqloneSolver<VL>> *> combined_qpalm{
        combined_backend.get(),
        {
            .max_outer_iter       = 100,
            .max_total_inner_iter = 1000,
            .tolerance            = cfg.tolerance,
            .verbose              = cfg.verbose,
            .detailed_stats       = cfg.verbose,
        },
    };

    for (index_t i = 0; !cfg.verbose && i < cfg.warmup; ++i)
        combined_qpalm();

    auto combined_status = combined_qpalm();

    auto x_combined      = combined_qpalm.get_solution();
    auto lambda_combined = combined_qpalm.get_equality_multipliers();

    // -------------------------------------------------------------------------
    // Optional correctness comparison
    // -------------------------------------------------------------------------
    if (cfg.check_solution) {
        std::vector<std::size_t> nx_per_branch;
        nx_per_branch.reserve(ocps.size());

        for (const auto &ocp : ocps) {
            nx_per_branch.push_back(static_cast<std::size_t>(ocp.dim.nx));
        }

        // compare_combined_normal(
        //     std::span<const double>(x_combined),
        //     std::span<const double>(x_fan),
        //     static_cast<std::size_t>(cfg.N),
        //     static_cast<std::size_t>(cfg.nu),
        //     std::span<const std::size_t>(nx_per_branch),
        //     1e-7
        // );

        // compare_combined_normal(
        //     std::span<const double>(lambda_combined),
        //     std::span<const double>(lambda_fan),
        //     static_cast<std::size_t>(cfg.N),
        //     0,
        //     std::span<const std::size_t>(nx_per_branch),
        //     1e-7
        // );
    }

    // -------------------------------------------------------------------------
    // Timings
    // -------------------------------------------------------------------------
    const double fan_time_s  = seconds_from_duration(fan_qpalm.stats->timings.total.wall_time);
    const double sfan_time_s = seconds_from_duration(sfan_qpalm.stats->timings.total.wall_time);

    const double combined_time_s =
        seconds_from_duration(combined_qpalm.stats->timings.total.wall_time);

    const double speedup        = combined_time_s / fan_time_s;
    const double speedup_serial = sfan_time_s / fan_time_s;

    std::cout << "N=" << cfg.N << ", nx=" << cfg.nx << ", nu=" << cfg.nu
              << ", branches=" << cfg.num_branches << ", processors=" << cfg.processors << '\n';

    std::cout << "fan status:      " << status_to_string(fan_status) << '\n';
    std::cout << "combined status: " << status_to_string(combined_status) << '\n';
    std::cout << "serial fan status:      " << status_to_string(sfan_status) << '\n';
    std::cout << "fan inner:       " << fan_qpalm.stats->inner_iter << '\n';
    std::cout << "fan outer:       " << fan_qpalm.stats->outer_iter << '\n';
    std::cout << "serial fan inner:       " << sfan_qpalm.stats->inner_iter << '\n';
    std::cout << "serial fan outer:       " << sfan_qpalm.stats->outer_iter << '\n';
    std::cout << "combined inner:  " << combined_qpalm.stats->inner_iter << '\n';
    std::cout << "combined outer:  " << combined_qpalm.stats->outer_iter << '\n';
    std::cout << "fan time:        " << fan_time_s << " s\n";
    std::cout << "serial fan time: " << sfan_time_s << " s\n";
    std::cout << "combined time:   " << combined_time_s << " s\n";
    std::cout << "speedup:         " << speedup << '\n';
    std::cout << "speedup serial:  " << speedup_serial << '\n';

    // -------------------------------------------------------------------------
    // CSV output
    // -------------------------------------------------------------------------
    const std::filesystem::path out_path{cfg.out_file};
    write_csv_header_if_needed(out_path);

    std::ofstream csv(out_path, std::ios::app);

    csv << cfg.N << ',' << cfg.nx << ',' << cfg.nu << ',' << cfg.ny << ',' << cfg.ny_N << ','
        << cfg.num_branches << ',' << cfg.processors << ',' << status_to_string(fan_status) << ','
        << status_to_string(sfan_status) << ',' << status_to_string(combined_status) << ','

        << fan_qpalm.stats->inner_iter << ',' << fan_qpalm.stats->outer_iter << ','
        << sfan_qpalm.stats->inner_iter << ',' << sfan_qpalm.stats->outer_iter << ','
        << combined_qpalm.stats->inner_iter << ',' << combined_qpalm.stats->outer_iter << ','
        << fan_time_s << ',' << sfan_time_s << ',' << combined_time_s << ',' << speedup << ','
        << speedup_serial << '\n';

    return 0;
}

int main(int argc, char **argv) {
    BenchConfig cfg = parse_config(argc, argv);

    std::cout << "Writing benchmark result to: " << cfg.out_file << '\n';

    constexpr fancyqlone::index_t VL = 4;
    return run_benchmark<VL>(cfg);
}
