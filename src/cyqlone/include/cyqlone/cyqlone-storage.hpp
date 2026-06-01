#pragma once

/// @file
/// Data structure for optimal control problems where the initial states are eliminated.
/// @ingroup topic-ocp-formulations

#include <cyqlone/config.hpp>
#include <cyqlone/linalg.hpp>
#include <cyqlone/ocp.hpp>

#include <batmat/linalg/simdify.hpp>
#include <batmat/matrix/matrix.hpp>
#include <span>
#include <vector>

namespace cyqlone {

/// Storage for a linear-quadratic OCP with the initial states x₀ eliminated.
/// ~~~
///                ₙ₋₁
///     minimize    ∑ [½ uᵢᵀ Rᵢ uᵢ + uᵢᵀ Sᵢ xᵢ + ½ xᵢᵀ Qᵢ xᵢ + rᵢᵀuᵢ + qᵢᵀxᵢ]
///                ⁱ⁼¹
///                + ½ u₀ᵀ R₀ u₀ + (r₀ + S₀ xᵢₙᵢₜ)ᵀ u₀
///                + ½ xₙᵀ Qₙ xₙ + qₙᵀ xₙ
///     s.t.        xᵢ₊₁ = Aᵢ xᵢ + Bᵢ uᵢ + cᵢ
///                 lᵢ   ≤ Cᵢ xᵢ + Dᵢ uᵢ ≤ uᵢ
///                 l₀ - C₀ xᵢₙᵢₜ ≤ D₀ U₀ ≤ u₀ - C₀ xᵢₙᵢₜ
///                 lₙ   ≤ Cₙ xₙ ≤ uₙ
/// ~~~
/// The matrices are combined per stage, with inputs ordered first.
/// The first and last stage are special because of the lack of x₀ and uₙ.
/// ~~~
/// Hᵢ = [ Rᵢ  Sᵢ ],    H₀ = [ R₀  0  ],    Fᵢ = [ Bᵢ  Aᵢ ],    Gᵢ = [ Dᵢ  Cᵢ ],    G₀ = [ D₀ Cₙ ]
///      [ Sᵢᵀ Qᵢ ]          [ 0   Qₙ ]
/// ~~~
/// Due to the elimination of x₀, there may be fewer constraints for the first stage, which is
/// tracked by the Ju0 mask. When reconstructing the solution, the multipliers for eliminated
/// constraints are set to zero (we assume that the initial state is feasible w.r.t. the state
/// constraints).
/// @ingroup topic-ocp-formulations
template <class T = real_t>
struct CyqloneStorage {
    using value_type = T;
    index_t N_horiz;
    index_t nx, nu, ny, ny_0, ny_N;
    std::vector<bool> Ju0;
    using matrix  = batmat::matrix::Matrix<value_type, index_t>;
    matrix data_H = [this] {
        return matrix{{.depth = N_horiz, .rows = nu + nx, .cols = nu + nx}};
    }();
    matrix data_F = [this] { return matrix{{.depth = N_horiz, .rows = nx, .cols = nu + nx}}; }();
    matrix data_G = [this] {
        return matrix{{.depth = N_horiz - 1, .rows = ny, .cols = nu + nx}};
    }();
    matrix data_G0N = [this] {
        return matrix{{.depth = 1, .rows = ny_0 + ny_N, .cols = nu + nx}};
    }();
    matrix data_rq   = [this] { return matrix{{.depth = N_horiz, .rows = nu + nx, .cols = 1}}; }();
    matrix data_c    = [this] { return matrix{{.depth = N_horiz, .rows = nx, .cols = 1}}; }();
    matrix data_lb   = [this] { return matrix{{.depth = N_horiz - 1, .rows = ny, .cols = 1}}; }();
    matrix data_lb0N = [this] { return matrix{{.depth = 1, .rows = ny_0 + ny_N, .cols = 1}}; }();
    matrix data_ub   = [this] { return matrix{{.depth = N_horiz - 1, .rows = ny, .cols = 1}}; }();
    matrix data_ub0N = [this] { return matrix{{.depth = 1, .rows = ny_0 + ny_N, .cols = 1}}; }();
    std::vector<index_t> indices_G0 = std::vector<index_t>(ny_0);

    void update_impl(const LinearOCPStorage &ocp);
    void update(const LinearOCPStorage &ocp);
    static CyqloneStorage build(const LinearOCPStorage &ocp, index_t ny_0 = -1);
    void reconstruct_ineq_multipliers(std::span<const value_type> y_compressed,
                                      std::span<value_type> y) const;
    std::vector<value_type>
    reconstruct_ineq_multipliers(std::span<const value_type> y_compressed) const;
    static index_t count_constr_0(const LinearOCPStorage &ocp, std::vector<bool> &Ju0);

    using Solution = LinearOCPStorage::Solution;
    using KKTError = LinearOCPStorage::KKTError;

    Solution reconstruct_solution(const LinearOCPStorage &ocp,
                                  std::span<const value_type> ux_compressed,
                                  std::span<const value_type> y_compressed,
                                  std::span<const value_type> λ_compressed) const;

    KKTError compute_kkt_error(const LinearOCPStorage &ocp,
                               std::span<const value_type> ux_compressed,
                               std::span<const value_type> y_compressed,
                               std::span<const value_type> λ_compressed) const;
};
template <class T = real_t>
struct FanCyqloneStorage {
    using value_type = T;
    using vl_t       = std::integral_constant<index_t, 1>;
    using matrix     = batmat::matrix::Matrix<value_type, index_t>;

    // One CyqloneStorage per branch, and introduce unused variable u(0) in each Cyqlone block
    //B(0) = 0 and R(0) = I r(0) = 0
    index_t num_branches;
    index_t nu;
    index_t ny_0; ///< Number of general constraints at stage 0, D(0) u(0).
    std::vector<CyqloneStorage<value_type>> branches;

    // B(0) for each branch
    std::vector<matrix> Bs;
    // r(0)
    matrix r0;
    // R(0)
    matrix R0;

    void update_impl(const FanOCPStorage &focp);
    void update(const FanOCPStorage &focp);
    // u(0) is dummy so no constraints on it
    static FanCyqloneStorage build(const FanOCPStorage &focp, index_t ny_0 = 0);
};
} // namespace cyqlone
