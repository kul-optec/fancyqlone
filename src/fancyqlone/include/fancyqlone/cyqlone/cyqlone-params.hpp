#pragma once

#include <fancyqlone/config.hpp>
#include <limits>
#include <stdexcept>

namespace fancyqlone {

/// Defines how to solve the small linear system that remains after cyclic reduction.
/// @ingroup topic-block-tridiag-solvers
enum class SolveMethod {
    /// Preconditioned Conjugate Gradient with staircase preconditioner (iterative).
    StairPCG,
    /// Preconditioned Conjugate Gradient with Jacobi preconditioner (iterative).
    JacobiPCG,
    /// Parallel Cyclic Reduction (direct).
    PCR,
    /// The final Schur complement is not solved, so it should be handled manually by the user.
    /// This is useful when Tricyqle is used to solve a block of a larger system and additional
    /// coupling to other blocks is present.
    None,
};

inline const char *enum_name(SolveMethod s) {
    switch (s) {
        case SolveMethod::StairPCG: return "StairPCG";
        case SolveMethod::JacobiPCG: return "JacobiPCG";
        case SolveMethod::PCR: return "PCR";
        case SolveMethod::None: return "None";
        default:;
    }
    throw std::out_of_range("invalid value for fancyqlone::SolveMethod");
}

/// Parameters and settings for the Tricyqle block-tridiagonal solver.
/// @ingroup topic-block-tridiag-solvers
template <class T = real_t>
struct TricyqleParams {
    using value_type = T;

    /// Use prefetching during the reverse CR solve phase.
    bool enable_prefetching = true;
    /// Maximum number of preconditioned conjugate gradient iterations.
    index_t pcg_max_iter = 100;
    /// Tolerance for the preconditioned conjugate gradient solver.
    value_type pcg_tolerance = std::numeric_limits<value_type>::epsilon() / 10;
    /// Enable printing of the residuals during PCG.
    bool pcg_print_resid = false;
    /// Algorithm to use for solving the final reduced block tridiagonal system.
    SolveMethod solve_method = SolveMethod::StairPCG;
    /// Tuning parameter for deciding when to update or re-factor the PCR factorization.
    /// If the update rank exceeds this fraction of nx, the PCR factorization is recomputed
    double pcr_max_update_fraction = 0.6;
    /// Tuning parameter for deciding when to update or re-factor the last subdiagonal blocks in the
    /// CR factorization.
    /// If the update rank exceeds this fraction of nx, the last subdiagonal blocks are
    /// recomputed.
    /// @todo Add option to switch at any level of CR, not just the last one.
    double cr_max_update_fraction_Y0 = 0.9;
    /// Threshold on nx for switching to a serial implementation of the reverse CR solve.
    index_t parallel_solve_cr_threshold = 10;
    /// Threshold on nx for switching to a serial implementation of the PCR factorization.
    index_t parallel_factor_pcr_threshold = 20;
};

/// Parameters and settings for the Cyqlone solver.
/// @ingroup topic-ocp-solvers
template <class T = real_t>
struct CyqloneParams {
    using value_type = T;

    /// Whether to eliminate the first control input u(0) in the very first iteration of the
    /// modified Riccati recursion. When set to true, this matches the derivation in the Cyqlone
    /// paper @cite pas_cyqlone_2025. When set to false, all stage indices are shifted by n-1, and
    /// u(0) is elimenated in the last iteration of the modified Riccati recursion instead of the
    /// first. This means that the remaining Schur complement also corresponds to different
    /// equations, but this is useful in the case of nonlinear dynamics, where during the
    /// simulation, it is beneficial to have the u(0) at the beginning of the first window instead
    /// of at the end. Setting this setting to false leads to more fill-in in the first interval,
    /// but the structure is otherwise the same. It can be seen as a simple relabeling of all
    /// variables (shifted by n-1). This additional fill-in in the first interval does not actually
    /// affect the run time, since it is present in all other intervals anyway.
    /// @todo Is it necessary to isolate the update of x(N) if eliminate_u0_first=false, similar to
    //        what we do for u(0) when eliminate_u0_first=true?
    bool eliminate_u0_first = true;
};

} // namespace fancyqlone
