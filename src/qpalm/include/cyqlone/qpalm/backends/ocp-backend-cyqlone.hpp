#pragma once

#include <cyqlone/config.hpp>
#include <cyqlone/cyqlone.hpp>

#include <cyqlone/cyqlone-params.hpp>
#include <cyqlone/cyqlone-storage.hpp>
#include <cyqlone/qpalm/solver.hpp>
#include <guanaqo/mat-view.hpp>

#include <cstdint>
#include <limits>
#include <memory>
#include <span>

namespace cyqlone::qpalm {

/// @addtogroup topic-optimization-solvers-ocp
/// @{

struct CyqloneData {
    std::span<const real_t> initial_variables = {}, initial_inequality_multipliers = {},
                            initial_equality_multipliers = {};
};

enum class WarmStartingStrategy {
    Zeros,
    Copy,
    Shift,
    ShiftNoInequality,
};

struct CyQPALMBackendSettings {
    index_t processors   = 8;
    bool print_residuals = false;
    int print_precision  = 3;
    // bool init_x0               = false; // TODO
    double changing_constr_factor = 0.05;
    index_t max_update_count      = 5;
    bool detailed_timings         = false;
    cyqlone::TricyqleParams<real_t> tricyqle_params{};
    uint32_t spin_count           = std::numeric_limits<uint32_t>::max();
    WarmStartingStrategy strategy = WarmStartingStrategy::Copy;
};

struct CyQPALMBackendStats {
    index_t num_updates  = 0;
    index_t rank_updates = 0;
    index_t num_factor   = 0;
};

/// @}

} // namespace cyqlone::qpalm

namespace CYQLONE_NS(cyqlone::qpalm) {

using guanaqo::StorageOrder;

template <index_t VL, StorageOrder DefaultOrder = StorageOrder::ColMajor, class LinearSolver = cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>>
struct CyQPALMBackend;
template <class>
struct CycloneBackendTraits;
template <index_t VL, StorageOrder DefaultOrder>
struct CycloneBackendTraits<cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>> {
    using OCP_t    = cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>;
    using simd     = typename OCP_t::simd;
    using CStorage = CyqloneStorage<>;
    using OCPStorage = LinearOCPStorage;
    using store_t  = typename OCP_t::template matrix<>;
    template <class Tag>
    struct storage_t : store_t {
        friend CyQPALMBackend<VL, DefaultOrder, OCP_t>;
        storage_t() = default;

      private:
        storage_t(store_t &&o) : store_t{std::move(o)} {}
    };
};

namespace detail {

    
template <index_t VL, StorageOrder DefaultOrder>
struct backend_stats_type<CyQPALMBackend<VL, DefaultOrder>> {
    using type = CyQPALMBackendStats;
};

} // namespace detail

/// @addtogroup topic-optimization-solvers-ocp
/// @{

template <index_t VL, StorageOrder DefaultOrder = StorageOrder::ColMajor, class LinearSolver = cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>>
struct unique_CyQPALMBackend : std::unique_ptr<CyQPALMBackend<VL, DefaultOrder, LinearSolver>> {
    unique_CyQPALMBackend()                                             = default;
    unique_CyQPALMBackend(unique_CyQPALMBackend &&) noexcept            = default;
    unique_CyQPALMBackend &operator=(unique_CyQPALMBackend &&) noexcept = default;
    ~unique_CyQPALMBackend();
    unique_CyQPALMBackend(std::unique_ptr<CyQPALMBackend<VL, DefaultOrder, LinearSolver>> &&o) noexcept
        : std::unique_ptr<CyQPALMBackend<VL, DefaultOrder, LinearSolver>>{std::move(o)} {}
};

template <index_t VL, StorageOrder DefaultOrder = StorageOrder::ColMajor, class LinearSolver = cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>>
unique_CyQPALMBackend<VL, DefaultOrder, LinearSolver>
make_cyqpalm_backend(const typename CycloneBackendTraits<LinearSolver>::CStorage &ocp, CyqloneData data,
                     const CyQPALMBackendSettings &settings);

template <index_t VL, StorageOrder DefaultOrder = StorageOrder::ColMajor, class LinearSolver = cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>>
void update_cyqpalm_backend(CyQPALMBackend<VL, DefaultOrder, LinearSolver> &backend,
                            const typename CycloneBackendTraits<LinearSolver>::CStorage &ocp);

template <index_t VL, StorageOrder DefaultOrder = StorageOrder::ColMajor, class LinearSolver = cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>>
void update_cyqpalm_backend(CyQPALMBackend<VL, DefaultOrder, LinearSolver> &backend, const typename CycloneBackendTraits<LinearSolver>::OCPStorage &ocp);

/// @}

template <index_t VL, StorageOrder DefaultOrder>
struct detail::backend_type<unique_CyQPALMBackend<VL, DefaultOrder>> {
    using type = CyQPALMBackend<VL, DefaultOrder>;
};

} // namespace CYQLONE_NS(cyqlone::qpalm)
