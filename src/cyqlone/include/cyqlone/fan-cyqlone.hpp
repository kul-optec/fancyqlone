#pragma once

/// @file
/// The main header for the FanCyqlone linear solvers.
/// @ingroup topic-lin-solvers
#include <cyqlone/cyqlone.hpp>
#include <cyqlone/tridiagonal-solver.hpp>
#include <batmat/matrix/storage.hpp>
#include <vector>
namespace CYQLONE_NS(cyqlone) {

using batmat::matrix::StorageOrder;

/// Linear solver for systems with optimal control structure with multiple horizons.
/// @tparam VL              Vector length.
/// @tparam T               Scalar type.
/// @tparam DefaultOrder    Storage order for the matrix workspaces (row/column major).
/// @tparam Ctx             Parallel execution context type, see @ref parallel::Context.
/// @ingroup topic-ocp-solvers
template <index_t VL = 4, class T = real_t, StorageOrder DefaultOrder = StorageOrder::ColMajor,
          class Ctx = parallel::Context<>>
struct SolverStorage {
    using value_type    = T;
    using tricyqle_t    = TricyqleSolver<VL, T, DefaultOrder, Ctx>;
    using SolverLast    = TridiagonalSolver<value_type>;
    using one_t         = std::integral_constant<index_t, 1>;
    using matrix        = batmat::matrix::Matrix<value_type, index_t, one_t, one_t, DefaultOrder>;
    using SharedContext = tricyqle_t::SharedContext;

    CyqloneSolver<VL, value_type, DefaultOrder, Ctx> cyqlone_solver;
    SolverLast tridiagonal_solver;
    matrix B0 = [this] {
        return matrix{{.rows = cyqlone_solver.nx, .cols = cyqlone_solver.nu},
                               batmat::matrix::uninitialized};
    }(); // B(0) for each branch
    matrix LB = [this] {
        return matrix{{.rows = cyqlone_solver.nu, .cols = cyqlone_solver.nx},
                                batmat::matrix::uninitialized};
    }(); // B(0) for each branch
};
template <class matrix, class T = real_t>
struct FanStorage_t {
    using value_type = T;
    using matrix_f   = TridiagonalSolver<value_type>::matrix;

    std::vector<matrix> branches;
    matrix_f first;
};
template <index_t VL = 4, class T = real_t, StorageOrder DefaultOrder = StorageOrder::ColMajor,
          class Ctx = parallel::FanContext<>>
struct FanCyqloneSolver {
    using value_type    = T;
    using tricyqle_t    = TricyqleSolver<VL, T, DefaultOrder, Ctx>;
    using Context       = Ctx;
    using SolverLast    = TridiagonalSolver<value_type>;
    using SharedContext = tricyqle_t::SharedContext;
    /// @}
    /// @name  Cyqlone and tridiag solver + workspaces
    /// @{
    index_t num_branches;
    // sizes of the problems
    index_t nu;
    index_t ny_0; ///< Number of general constraints at stage 0, D(0) u(0).

    // total shared context
    std::unique_ptr<parallel::FanSharedContext> create_parallel_context() const {
        std::vector<parallel::SharedContext> branch_contexts;
        branch_contexts.reserve(num_branches);
        for (index_t i = 0; i < num_branches; ++i) {
            branch_contexts.emplace_back(
                std::move(*solver_storages[i].cyqlone_solver.create_parallel_context()));
        }
        return std::make_unique<parallel::FanSharedContext>(num_branches,
                                                            std::move(branch_contexts));
    }
    std::vector<SolverStorage<VL, value_type, DefaultOrder, parallel::Context<>>> solver_storages;

    /// Get the total number of primal variables in the OCP.
    /// @note The actual number of variable stored in Cyqlone's internal data structures may be
    ///       larger.
    [[nodiscard]] index_t num_variables() const {
        index_t num_var = 0;
        for (const SolverStorage<VL, value_type, DefaultOrder, parallel::Context<>> &s :
             solver_storages) {
            num_var += nu * (s.cyqlone_solver.N_horiz - 1) +
                       s.cyqlone_solver.nx * s.cyqlone_solver.N_horiz;
        }
        return num_var + nu; // for u(0)
    }
    /// Get the total number of dynamics constraints in the OCP.
    /// @note The actual number of constraints stored in Cyqlone's internal data structures may be
    ///       larger.
    [[nodiscard]] index_t num_dynamics_constraints() const {
        index_t num_dyn_con = 0;
        for (const SolverStorage<VL, value_type, DefaultOrder, parallel::Context<>> &s :
             solver_storages) {
            num_dyn_con += s.cyqlone_solver.nx * s.cyqlone_solver.N_horiz;
        }
        return num_dyn_con;
    }
    /// Get the total number of general constraints in the OCP.
    /// @note The actual number of constraints stored in Cyqlone's internal data structures may be
    ///       larger.
    [[nodiscard]] index_t num_general_constraints() const {
        index_t num_gen_con = 0;
        for (const SolverStorage<VL, value_type, DefaultOrder, parallel::Context<>> &s :
             solver_storages) {
            num_gen_con +=
                s.cyqlone_solver.ny * (s.cyqlone_solver.N_horiz - 1) + s.cyqlone_solver.ny_N;
        }
        return num_gen_con + ny_0; // for D(0) u(0)
    }
    [[nodiscard]] index_t nx() const {
        index_t nx_tot = 0;
        for (const SolverStorage<VL, value_type, DefaultOrder, parallel::Context<>> &s :
             solver_storages) {
            nx_tot += s.cyqlone_solver.nx;
        }
        return nx_tot; // for D(0) u(0)
    }
    // Workspaces for contribution u(0)
    SolverLast::matrix SBs = [this] {
        return typename SolverLast::matrix{{.depth = num_branches, .rows = nu, .cols = nu},
                           batmat::matrix::uninitialized};
                        }();
    SolverLast::matrix rs = [this] {
        return typename SolverLast::matrix{{.depth = num_branches, .rows = nu, .cols = 1},
                           batmat::matrix::uninitialized};
    }();
    SolverLast::matrix R0 = [this] {
        return typename SolverLast::matrix{{.rows = nu, .cols = nu}, batmat::matrix::uninitialized};
    }();
    SolverLast::matrix r0 = [this] {
        return typename SolverLast::matrix{{.rows = nu, .cols = 1}, batmat::matrix::uninitialized};
    }();
    
    /// Vector length.
    static constexpr index_t v = VL;
    /// Number of stages per thread per vector lane (rounded up).
    ///@todo: check how to implement here

    /// @name Matrix data structures
    /// @{

    /// Default storage order for most matrices.
    static constexpr auto default_order = DefaultOrder;
    /// Column-major storage order for column vectors and update matrices.
    static constexpr auto column_major = StorageOrder::ColMajor;

    /// Represents a SIMD vector of width @ref v storing values of type @ref value_type.
    using simd = batmat::datapar::deduced_simd<value_type, v>;
    /// Integral constant type for the vector length.
    using vl_t = std::integral_constant<index_t, v>;
    /// Integral constant type for the alignment of the batched matrix data structures.
    using align_t = std::integral_constant<index_t, v * alignof(value_type)>;
    /// Owning type for a batch of matrices (with batch size v).
    template <StorageOrder O = column_major>
    using matrix     = batmat::matrix::Matrix<value_type, index_t, vl_t, index_t, O, align_t>;
    using FanStorage = FanStorage_t<matrix<>, value_type>;

    /// Get the current Cyqlone solver parameters.
    [[nodiscard]] CyqloneParams<value_type> get_params() const {
        return solver_storages[0].cyqlone_solver.get_params();
    }
    /// Update the Cyqlone solver parameters.
    void update_params(const CyqloneParams<value_type> &new_params) {
        for (auto &s : solver_storages) {
            s.cyqlone_solver.update_params(new_params);
        }
    }

    /// Get the current Tricyqle solver parameters.
    [[nodiscard]] TricyqleParams<value_type> get_tricyqle_params() const {
        return solver_storages[0].cyqlone_solver.get_tricyqle_params();
    }

    /// Update the Tricyqle solver parameters.
    void update_tricyqle_params(const TricyqleParams<value_type> &new_params) {
        for (auto &s : solver_storages) {
            s.cyqlone_solver.update_tricyqle_params(new_params);
        }
    }

    /// Call a function for each stage in the horizon, passing the stage index, the data batch
    /// index, and optionally the corresponding batches of the given arrays.
    /// Iterates backwards in time (decreasing stage index j).
    void foreach_stage(Context &ctx, auto &&func, auto &&...xs) const {
        index_t i = ctx.total_context().index();
        solver_storages[i].foreach_stage(ctx.branch_context(), func, xs.branches[i]...);
        /// @todo: Handle u0 separately, since it is shared between branches
    }
    /// Call a function for each stage in the horizon, passing the stage index, the data batch
    /// index, and optionally the corresponding batches of the given arrays.
    /// Iterates backwards in time (decreasing stage index j).
    void foreach_batch(Context &ctx, auto &&func, auto &&...xs) const {
        index_t i = ctx.total_context().index();
        solver_storages[i].foreach_stage(ctx.branch_context(), func, xs.branches[i]...);
        func(xs.first...);
        /// @todo: Handle u0 separately, since it is shared between branches
    }
    /// Call a function for each stage in the horizon, passing the stage index, the data batch
    /// index, and optionally the corresponding batches of the given arrays.
    /// Iterates forward in time (increasing stage index j).
    void foreach_stage_fwd(Context &ctx, auto &&func, auto &&...xs) const {
        index_t i = ctx.total_context().index();
        solver_storages[i].foreach_stage_fwd(ctx.branch_context(), func, xs.branches[i]...);

        /// @todo: Handle u0 separately, since it is shared between branches
    }
    void foreach_batch_fwd(Context &ctx, auto &&func, auto &&...xs) const {
        index_t i = ctx.total_context().index();
        solver_storages[i].foreach_stage_fwd(ctx.branch_context(), func, xs.branches[i]...);
        func(xs.first...);
    }
    /// Build a new FanCyqloneSolver instance.
    static FanCyqloneSolver build(const FanCyqloneStorage<value_type> &ocp, std::vector<index_t> p,
                                  CyqloneParams<value_type> params = {});
    /// Update the internal data structures to reflect changes in the OCP data (without changing
    /// the problem size).
    void update_data(const FanCyqloneStorage<value_type> &ocp, const std::vector<index_t> &p);
    /// Initialize the right-hand side vector for the dynamics constraints of the OCP, using the
    /// custom Cyqlone storage format.
    void initialize_rhs(const FanCyqloneStorage<value_type> &ocp, FanStorage rhs) const;
    /// @copydoc initialize_rhs
    FanStorage initialize_rhs(const FanCyqloneStorage<value_type> &ocp) const;
    /// Initialize the gradient vector for the OCP cost function, using the custom Cyqlone storage
    /// format.
    void initialize_gradient(const FanCyqloneStorage<value_type> &ocp, FanStorage grad) const;
    /// @copydoc initialize_gradient
    FanStorage initialize_gradient(const FanCyqloneStorage<value_type> &ocp) const;
    /// Initialize the lower and upper bounds for the general constraints of the OCP, using the
    /// custom Cyqlone storage format.
    void initialize_bounds(const FanCyqloneStorage<value_type> &ocp, FanStorage b_min,
                           FanStorage b_max) const;
    /// @copydoc initialize_bounds
    std::pair<FanStorage, FanStorage>
    initialize_bounds(const FanCyqloneStorage<value_type> &ocp) const;

    /// @todo check and document behavior when `N_horiz != ceil_N()`.
    void pack_variables(std::span<const value_type> ux_lin, FanStorage ux) const;
    FanStorage pack_variables(std::span<const value_type> ux_lin) const;
    void unpack_variables(FanStorage ux, std::span<value_type> ux_lin) const;
    std::vector<value_type> unpack_variables(FanStorage ux) const;
    void pack_dynamics(std::span<const value_type> λ_lin, FanStorage λ) const;
    FanStorage pack_dynamics(std::span<const value_type> λ_lin) const;
    void unpack_dynamics(FanStorage λ, std::span<value_type> λ_lin) const;
    std::vector<value_type> unpack_dynamics(FanStorage λ) const;
    void pack_constraints(std::span<const value_type> y_lin, FanStorage y,
                          value_type fill = 0) const;
    FanStorage pack_constraints(std::span<const value_type> y_lin, value_type fill = 0) const;
    void unpack_constraints(FanStorage y, std::span<value_type> y_lin) const;
    std::vector<value_type> unpack_constraints(FanStorage y) const;

    /// Get a zero-initialized matrix for the primal variables u and x.
    FanStorage initialize_variables() const;
    /// Get a zero-initialized matrix for the dynamics constraints (or their multipliers).
    FanStorage initialize_dynamics_constraints() const;
    /// Get a zero-initialized matrix for the general constraints (or their multipliers).
    FanStorage initialize_general_constraints() const;

    /// @}

    /// @name OCP cost gradient and constraints evaluation
    /// @{

    /// Compute Mx + b, where M is the dynamics constraint Jacobian matrix of the OCP.
    /// In other words, evaluate the residuals for all stages, i.e.,
    /// @f$ A_j x^j + B_j u^j - x^{j+1} + b^j @f$.
    void residual_dynamics_constr(Context &ctx, FanStorage x, FanStorage b, FanStorage Mxb) const;
    /// Compute Mᵀλ, where M is the dynamics constraint Jacobian matrix of the OCP.
    /// Optionally add the result to the existing contents of Mᵀλ by setting @p accum to true.
    void transposed_dynamics_constr(Context &ctx, FanStorage λ, FanStorage Mᵀλ,
                                    bool accum = false) const;
    /// Compute the general constraints Gx, where G is the general constraint Jacobian matrix of the
    /// OCP. In other words, evaluate the constraints for all stages, i.e.,
    /// @f$ C_j x^j + D_j u^j @f$.
    void general_constr(Context &ctx, FanStorage ux, FanStorage DCux) const;
    /// Compute Gᵀy, where G is the general constraint Jacobian matrix of the OCP.
    void transposed_general_constr(Context &ctx, FanStorage y, FanStorage DCᵀy) const;
    /// @copydoc transposed_general_constr
    /// @todo Remove.
    void transposed_general_constr(FanStorage y, FanStorage DCᵀy) const;
    /// Compute the cost gradient, with optional scaling factors.
    /// grad_f ← Q ux + α q + β grad_f
    void cost_gradient(Context &ctx, FanStorage ux, value_type α, FanStorage q, value_type β,
                       FanStorage grad_f) const;
    /// Compute the regularized cost gradient, with regularization parameter γ⁻¹, with respect to
    /// the point @p ux0.
    void cost_gradient_regularized(Context &ctx, value_type γ, FanStorage ux, FanStorage ux0,
                                   FanStorage q, FanStorage grad_f) const;
    /// Subtract the regularization term from the cost gradient.
    void cost_gradient_remove_regularization(Context &ctx, value_type γ, FanStorage x,
                                             FanStorage x0, FanStorage grad_f) const;

    /// @}

    /// @name Factorization and solve routines
    /// @{

    /// Compute the Cyqlone factorization of the KKT matrix of the OCP and perform a forward solve
    /// (fused for improved locality).
    /// @param ctx Parallel context.
    /// @param γ Reciprocal primal regularization.
    /// @param ρ_inv Dual regularization.
    /// @param Σ ALM penalty factors.
    /// @param[in,out] ux Negative augmented Lagrangian gradient on entry; solution of forward solve
    ///                   on exit.
    /// @param[in,out] λ Constant term of the dynamics constraints on entry; solution of forward
    ///                  solve on exit.
    /// To obtain the solution of the KKT system, a reverse solve with the same factorization must
    /// be performed afterwards.
    /// @see @ref solve_reverse
    void factor_solve(Context &ctx, value_type γ, real_t ρ_inv, FanStorage Σ, FanStorage ux,
                      FanStorage λ);
    /// Compute the Cyqlone factorization of the KKT matrix of the OCP.
    /// @see @ref factor_solve
    void factor(Context &ctx, value_type γ, real_t ρ_inv, FanStorage Σ);
    /// Perform a forward solve with the Cyqlone factorization.
    /// @see @ref factor_solve
    void solve_forward(Context &ctx, FanStorage ux, FanStorage λ);
    /// Perform a reverse solve with the Cyqlone factorization.
    /// @param ctx Parallel context.
    /// @param ux On entry, the result of the forward solve; on exit the solution of the primal
    ///           variables of the KKT system.
    /// @param λ On entry, the result of the forward solve; on exit the solution of the dual
    ///          variables corresponding to the dynamics constraints of the KKT system.
    void solve_reverse(Context &ctx, FanStorage ux, FanStorage λ);
    /// Fused variant of @ref solve_reverse and @ref transposed_dynamics_constr (for improved
    /// locality of the dynamics Jacobians).
    void solve_reverse_mul(Context &ctx, FanStorage ux, FanStorage λ, FanStorage Mᵀλ);
    // using ddp_func_t = void(Context &ctx, index_t i, batch_view<default_order> F, batch_FanStorage ux,
    //                         batch_FanStorage b, mut_batch_FanStorage x_next);
    /// Perform a reverse solve with the Cyqlone factorization, using the given dynamics function,
    /// which can be used to implement differential dynamic programming (DDP).
    /// @param ctx Parallel context.
    /// @param ux On entry, the result of the forward solve; on exit the solution of the primal
    ///           variables of the KKT system.
    /// @param λ On entry, the result of the forward solve; on exit the solution of the dual
    ///          variables corresponding to the dynamics constraints of the KKT system.
    // void solve_reverse_ddp(Context &ctx, FanStorage ux, FanStorage λ, real_t α,
    //                        const std::function<ddp_func_t> &simulate);
    /// Fused variant of @ref solve_reverse_ddp and @ref transposed_dynamics_constr (for improved
    /// locality of the dynamics Jacobians).
    // void solve_reverse_mul_ddp(Context &ctx, FanStorage ux, FanStorage λ, real_t α,
    //                            const std::function<ddp_func_t> &simulate, FanStorage Mᵀλ);
    /// Perform factorization updates of the Cyqlone factorization as described by
    /// Algorithm 4 in the paper.
    /// @param ctx Parallel context.
    /// @param ΔΣ Changes to the ALM penalty factors Σ.
    void update(Context &ctx, FanStorage ΔΣ);
    /// Fused variant of @ref update and @ref solve_forward.
    void update_solve(Context &ctx, FanStorage ΔΣ, FanStorage ux, FanStorage λ);

    /// @}

    /// @name Low-level factorization and forward solve routines
    /// @{

    // index_t riccati_thread_assignment(Context &ctx) const { return add_wrap_p(ctx.index, 1); }
    template <bool Factor = true, bool Solve = true>
    void factor_riccati_solve(Context &ctx, value_type γ, FanStorage Σ, FanStorage ux,
                              FanStorage λ);
    template <bool Factor = true, bool Solve = true>
    void compute_schur(Context &ctx, real_t ρ_inv, FanStorage ux, FanStorage λ);

    /// @}

    /// @name Low-level factorization and forward solve routines for parallel cyclic reduction
    /// @{

    template <bool Factor = true, bool Solve = true>
    void factor_solve_impl(Context &ctx, value_type γ, real_t ρ_inv, FanStorage Σ, FanStorage ux,
                           FanStorage λ);

    /// @}
    template <bool Factor = true, bool Solve = true>
    void factor_solve_λ0(index_t branch, FanStorage λ);
    template <bool Factor = true, bool Solve = true>

    void factor_solve_u0(FanStorage ux);

    /// @name Low-level reverse solve routines
    /// @{

    void solve_reverse(Context &ctx, FanStorage ux, FanStorage λ,
                       std::optional<FanStorage> Mᵀλ = std::nullopt) const;
    void solve_reverse_u0(FanStorage ux) const;
    void solve_reverse_λ0(index_t branch, FanStorage λ) const;

    /// @}

    /// @name Low-level factorization update routines
    /// @{

    /// Update the modified Riccati factorization of a single block column as described by
    /// Algorithm 3 in the paper.
    template <bool Solve = true>
    void update_riccati_solve(Context &ctx, FanStorage ΔΣ, FanStorage ux, FanStorage λ);
    void update_riccati(Context &ctx, FanStorage ΔΣ) {
        update_riccati_solve<false>(ctx, ΔΣ, {}, {});
    }
    template <bool Solve = true>
    void update_solve_impl(Context &ctx, FanStorage ΔΣ, FanStorage ux, FanStorage λ);

    /// @}

    /// @name Build sparse representations for debugging and testing
    /// @{

    [[nodiscard]] SparseMatrix build_sparse(const FanCyqloneStorage<value_type> &ocp,
                                            std::span<const value_type> Σ) const;
    [[nodiscard]] SparseMatrix build_sparse_no_penalty() const;
    [[nodiscard]] std::vector<value_type>
    build_rhs(FanStorage rq, FanStorage b, value_type scale_rq = -1, value_type scale_b = -1) const;
    [[nodiscard]] std::vector<value_type> build_sol(FanStorage ux, FanStorage λ) const {
        return build_rhs(ux, λ, 1, 1);
    }
    [[nodiscard]] SparseMatrix build_sparse_factor() const;
    [[nodiscard]] SparseMatrix build_sparse_diag() const;
    [[nodiscard]] SparseMatrix build_sparse_reg(real_t γ, real_t ρ_inv_internal,
                                                real_t ρ_inv_windows) const;
};
} // namespace CYQLONE_NS(cyqlone)