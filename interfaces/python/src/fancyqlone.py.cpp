#include <cyqlone/cyqlone-storage.hpp>
#include <cyqlone/fan-cyqlone.hpp>
#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.hpp>
#include <cyqlone/qpalm/solver.hpp>

#include <batmat/config.hpp>

#include <limits>
#include <mutex>
#include <stdexcept>
#include <utility>
#include <vector>

#include "common.py.hpp"
#include "fancyqlone.py.hpp"

namespace CYQLONE_NS(cyqlone) {

namespace qp = cyqlone::qpalm;

static FanOCPStorage copy_fan_ocp(const nb::list &branches) {
    if (branches.size() == 0)
        throw std::invalid_argument("FanOCP must contain at least one branch");

    FanOCPStorage result;
    result.ocps.reserve(branches.size());
    for (nb::handle branch : branches)
        result.ocps.push_back(nb::cast<const PythonOCP &>(branch).ocp);

    const OCPDim expected = result.ocps.front().dim;
    if (expected.N_horiz < 2)
        throw std::invalid_argument("FanOCP branches must have a horizon length of at least two");
    for (const auto &branch : result.ocps) {
        if (branch.dim.N_horiz < 2)
            throw std::invalid_argument(
                "FanOCP branches must have a horizon length of at least two");
        if (branch.dim != expected)
            throw std::invalid_argument("All FanOCP branches must have identical dimensions");
    }
    return result;
}

template <index_t VL>
struct PythonFanCyQPALM {
    using LinearSolver = FanCyqloneSolver<VL>;
    using Backend = qp::unique_CyQPALMBackend<VL, StorageOrder::ColMajor, LinearSolver>;
    using Solver  = qp::Solver<Backend>;

    FanOCPStorage fan_ocp;
    FanCyqloneStorage<> packed_ocp;
    Solver solver;
    mutable std::mutex mutex;
    bool result_valid = false;

    static Backend make_backend(const FanCyqloneStorage<> &ocp, index_t num_branches,
                                index_t processors_per_branch,
                                qp::CyQPALMBackendSettings settings) {
        if (processors_per_branch <= 0)
            throw std::invalid_argument("processors_per_branch must be positive");
        if constexpr (VL > 1) {
            if (!is_pow_2(processors_per_branch))
                throw std::invalid_argument(
                    "processors_per_branch must be a power of two for the selected SIMD backend");
        }
        if (num_branches > std::numeric_limits<index_t>::max() / processors_per_branch)
            throw std::invalid_argument("Total processor count is too large");
        if (settings.strategy == qp::WarmStartingStrategy::ShiftNoInequality)
            throw std::invalid_argument(
                "ShiftNoInequality warm starting is not supported by FanCyQPALM");

        settings.processors = num_branches * processors_per_branch;
        settings.tricyqle_params.solve_method = SolveMethod::None;
        return qp::make_cyqpalm_backend<VL, StorageOrder::ColMajor, LinearSolver>(ocp, {}, settings);
    }

    PythonFanCyQPALM(const nb::list &branches, index_t processors_per_branch,
                     qp::CyQPALMBackendSettings backend_settings, qp::Settings settings)
        : fan_ocp{copy_fan_ocp(branches)},
          packed_ocp{FanCyqloneStorage<>::build(fan_ocp)},
          solver{make_backend(packed_ocp, fan_ocp.num_branches(), processors_per_branch,
                              backend_settings),
                 settings} {}

    qp::SolverStatus solve() {
        std::scoped_lock lock{mutex};
        result_valid = false;
        auto status  = solver();
        result_valid = solver.has_result();
        return status;
    }

    void require_result() const {
        if (!result_valid)
            throw std::runtime_error("No current result available. Please solve first.");
    }

    void update_data(const nb::list &branches) {
        std::scoped_lock lock{mutex};
        if (static_cast<index_t>(branches.size()) != fan_ocp.num_branches())
            throw std::invalid_argument("Cannot change the number of FanOCP branches");

        std::vector<const PythonOCP *> updates;
        updates.reserve(branches.size());
        for (index_t i = 0; i < fan_ocp.num_branches(); ++i) {
            nb::handle branch_handle = branches[static_cast<size_t>(i)];
            const auto &branch       = nb::cast<const PythonOCP &>(branch_handle);
            if (branch.ocp.dim != fan_ocp.ocps[static_cast<size_t>(i)].dim)
                throw std::invalid_argument("Cannot change FanOCP branch dimensions");
            updates.push_back(&branch);
        }

        for (index_t i = 0; i < fan_ocp.num_branches(); ++i)
            fan_ocp.ocps[static_cast<size_t>(i)] = updates[static_cast<size_t>(i)]->ocp;
        packed_ocp.update(fan_ocp);
        qp::update_cyqpalm_backend(*solver.backend, packed_ocp);
        result_valid = false;
    }

    nb::tuple get_result() {
        std::scoped_lock lock{mutex};
        require_result();
        auto x      = solver.get_solution();
        auto y      = solver.get_inequality_multipliers();
        auto lambda = solver.get_equality_multipliers();
        auto reconstructed = packed_ocp.reconstruct_solution(fan_ocp, x, y, lambda);
        auto kkt_error      = fan_ocp.compute_kkt_error(reconstructed);

        nb::list branches;
        for (auto &branch : reconstructed.solutions) {
            branches.append(nb::make_tuple(np_copy(std::move(branch.solution)),
                                           np_copy(std::move(branch.inequality_multipliers)),
                                           np_copy(std::move(branch.equality_multipliers))));
        }

        return nb::make_tuple(np_copy(std::move(x)), np_copy(std::move(y)),
                              np_copy(std::move(lambda)), std::move(branches),
                              kkt_error.stationarity, kkt_error.inequality_residual,
                              kkt_error.equality_residual, kkt_error.complementarity);
    }

    nb::object get_backend_stats() const {
        std::scoped_lock lock{mutex};
        if (!solver.stats_backend)
            return nb::none();
        const auto &stats = *solver.stats_backend;
        return nb::make_tuple(stats.num_factor, stats.num_updates, stats.rank_updates);
    }

    nb::object get_stats() const {
        std::scoped_lock lock{mutex};
        if (!solver.stats)
            return nb::none();
        return nb::cast(*solver.stats, nb::rv_policy::copy);
    }

    bool has_result() const {
        std::scoped_lock lock{mutex};
        return result_valid;
    }

    void warm_start_solution() {
        std::scoped_lock lock{mutex};
        require_result();
        solver.warm_start_solution();
    }

    auto get_equality_constraints() {
        std::scoped_lock lock{mutex};
        require_result();
        return np_copy(solver.get_equality_constraints());
    }

    auto get_inequality_constraints() {
        std::scoped_lock lock{mutex};
        require_result();
        return np_copy(solver.get_inequality_constraints());
    }
};

template <index_t VL>
void register_fancyqlone_solver(nb::module_ &m) {
    using Wrapper = PythonFanCyQPALM<VL>;
    nb::class_<Wrapper>(m, "_FanCyQPALM")
        .def(nb::init<const nb::list &, index_t, qp::CyQPALMBackendSettings, qp::Settings>(),
             "branches"_a, "processors_per_branch"_a, "backend_settings"_a, "settings"_a)
        .def("__call__", &Wrapper::solve, nb::call_guard<nb::gil_scoped_release>())
        .def("solve", &Wrapper::solve, nb::call_guard<nb::gil_scoped_release>())
        .def("update_data", &Wrapper::update_data, "branches"_a)
        .def("warm_start_solution", &Wrapper::warm_start_solution)
        .def("stop", [](Wrapper &self) { self.solver.stop(); })
        .def_prop_ro("has_result", &Wrapper::has_result)
        .def_prop_ro("num_variables", [](const Wrapper &self) {
            return self.solver.get_num_variables();
        })
        .def_prop_ro("num_equality_constraints", [](const Wrapper &self) {
            return self.solver.get_num_equality_constraints();
        })
        .def_prop_ro("num_inequality_constraints", [](const Wrapper &self) {
            return self.solver.get_num_inequality_constraints();
        })
        .def_prop_ro("result", &Wrapper::get_result)
        .def_prop_ro("equality_constraints", &Wrapper::get_equality_constraints,
                     nb::rv_policy::move)
        .def_prop_ro("inequality_constraints", &Wrapper::get_inequality_constraints,
                     nb::rv_policy::move)
        .def_prop_ro("stats", &Wrapper::get_stats)
        .def_prop_ro("backend_stats", &Wrapper::get_backend_stats);
}

#define FANCYQLONE_INSTANTIATE_PYTHON(VL)                                                          \
    template void register_fancyqlone_solver<VL>(nb::module_ &);
BATMAT_FOREACH_VL_DEFAULT(FANCYQLONE_INSTANTIATE_PYTHON)

} // namespace CYQLONE_NS(cyqlone)
