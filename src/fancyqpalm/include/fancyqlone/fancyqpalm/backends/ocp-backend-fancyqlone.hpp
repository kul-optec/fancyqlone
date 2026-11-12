#pragma once

#include <fancyqlone/config.hpp>
#include <fancyqlone/cyqlone/cyqlone.hpp>
#include <fancyqlone/fancyqlone/fancyqlone.hpp>
#include <fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp>

#include <fancyqlone/cyqlone/cyqlone-params.hpp>
#include <fancyqlone/cyqlone/cyqlone-storage.hpp>
#include <fancyqlone/fancyqpalm/solver.hpp>
#include <guanaqo/mat-view.hpp>

#include <cstdint>
#include <limits>
#include <memory>
#include <span>
#include <vector>

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

enum class FanWarmStartingStrategy {
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
    /// Maximum number of factorization updates before refactorization.
    /// Fan backends do not support updates and use an effective value of zero.
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

template <class LinearSolver>
struct CycloneBackendTraits;
// Traits for the CyqloneSolver
template <index_t VL, StorageOrder DefaultOrder>
struct CycloneBackendTraits<cyqlone::CyqloneSolver<VL, real_t, DefaultOrder>> {
    static constexpr bool supports_factorization_updates = true;
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
        void check_dimensions_col(const storage_t &other, const index_t &dim_col) const {
            BATMAT_ASSERT(this->cols() == dim_col);
            BATMAT_ASSERT(other.cols() == dim_col);
            BATMAT_ASSERT(this->rows() == other.rows());
            BATMAT_ASSERT(this->depth() == other.depth());     
        }
    
    };
    using warm_start_t = WarmStartingStrategy;

};
// Traits for FanCyqloneSolver
template <index_t VL, StorageOrder DefaultOrder>
struct CycloneBackendTraits<cyqlone::FanCyqloneSolver<VL, real_t, DefaultOrder>> {
    static constexpr bool supports_factorization_updates = false;
    using OCP_t    = cyqlone::FanCyqloneSolver<VL, real_t, DefaultOrder>;
    using simd     = typename OCP_t::simd;
    using CStorage = FanCyqloneStorage<>;
    using OCPStorage = FanOCPStorage;
    using store_t  = FanStorage_t<typename OCP_t::template matrix<>>;
    template <class Tag>
    struct storage_t : store_t {
        friend CyQPALMBackend<VL, DefaultOrder, OCP_t>;
        storage_t() = default;
        
        storage_t(storage_t&&) = default;
        storage_t& operator=(storage_t&&) = default;

        storage_t(const storage_t&) = delete;
        storage_t& operator=(const storage_t&) = delete;


      private:
        storage_t(store_t &&o) : store_t{std::move(o)} {}
        void check_dimensions_col(const storage_t &other, const index_t &dim_col) const {
            for (index_t c = 0; c < static_cast<index_t>(this->branches.size()); ++c) {
                BATMAT_ASSERT(this->branches[c].cols() == dim_col);
                BATMAT_ASSERT(other.branches[c].cols() == dim_col);
                BATMAT_ASSERT(this->branches[c].rows() == other.branches[c].rows());
                BATMAT_ASSERT(this->branches[c].depth() == other.branches[c].depth());
            }  
            BATMAT_ASSERT(this->first.cols() == dim_col);
            BATMAT_ASSERT(other.first.cols() == dim_col);
            BATMAT_ASSERT(this->first.rows() == other.first.rows());
            BATMAT_ASSERT(this->first.depth() == other.first.depth()); 
        }
        index_t size() const {
            index_t total_size = static_cast<index_t>(this->branches.size());

            return total_size;
        }
    public:
        storage_t clone() const {
            return storage_t(store_t::clone());
}

    };
    using warm_start_t = FanWarmStartingStrategy;
};
// Traits for SerialFanCyqloneSolver
template <index_t VL, StorageOrder DefaultOrder>
struct CycloneBackendTraits<cyqlone::SerialFanCyqloneSolver<VL, real_t, DefaultOrder>> {
    static constexpr bool supports_factorization_updates = false;
    using OCP_t    = cyqlone::SerialFanCyqloneSolver<VL, real_t, DefaultOrder>;
    using simd     = typename OCP_t::simd;
    using CStorage = FanCyqloneStorage<>;
    using OCPStorage = FanOCPStorage;
    using store_t  = FanStorage_t<typename OCP_t::template matrix<>>;
    template <class Tag>
    struct storage_t : store_t {
        friend CyQPALMBackend<VL, DefaultOrder, OCP_t>;
        storage_t() = default;
        
        storage_t(storage_t&&) = default;
        storage_t& operator=(storage_t&&) = default;

        storage_t(const storage_t&) = delete;
        storage_t& operator=(const storage_t&) = delete;


      private:
        storage_t(store_t &&o) : store_t{std::move(o)} {}
        void check_dimensions_col(const storage_t &other, const index_t &dim_col) const {
            for (index_t c = 0; c < static_cast<index_t>(this->branches.size()); ++c) {
                BATMAT_ASSERT(this->branches[c].cols() == dim_col);
                BATMAT_ASSERT(other.branches[c].cols() == dim_col);
                BATMAT_ASSERT(this->branches[c].rows() == other.branches[c].rows());
                BATMAT_ASSERT(this->branches[c].depth() == other.branches[c].depth());
            }  
            BATMAT_ASSERT(this->first.cols() == dim_col);
            BATMAT_ASSERT(other.first.cols() == dim_col);
            BATMAT_ASSERT(this->first.rows() == other.first.rows());
            BATMAT_ASSERT(this->first.depth() == other.first.depth()); 
        }
        index_t size() const {
            index_t total_size = static_cast<index_t>(this->branches.size());

            return total_size;
        }
    public:
        storage_t clone() const {
            return storage_t(store_t::clone());
}

    };
    using warm_start_t = FanWarmStartingStrategy;
};
namespace detail {

    
template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
struct backend_stats_type<CyQPALMBackend<VL, DefaultOrder, LinearSolver>> {
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

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
struct detail::backend_type<unique_CyQPALMBackend<VL, DefaultOrder, LinearSolver>> {
    using type = CyQPALMBackend<VL, DefaultOrder, LinearSolver>;
};

} // namespace CYQLONE_NS(cyqlone::qpalm)
