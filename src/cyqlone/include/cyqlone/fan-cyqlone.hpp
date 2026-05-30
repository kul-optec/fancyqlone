#pragma once

/// @file
/// The main header for the FanCyqlone linear solvers.
/// @ingroup topic-lin-solvers

#include <cyqlone/cyqlone.hpp>
#include <cyqlone/tridiagonal-solver.hpp>
#include <batmat/matrix/storage.hpp>
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
    using matrix        = batmat::matrix::Matrix<value_type, index_t>;
    using SharedContext = tricyqle_t::SharedContext;

    CyqloneSolver<VL, value_type, DefaultOrder, Ctx> cyqlone_solver;
    SolverLast tridiagonal_solvers;
    matrix B0;
    matrix LB;
    std::unique_ptr<SharedContext> shared_ctx;
};
template <index_t VL = 4, class T = real_t, StorageOrder DefaultOrder = StorageOrder::ColMajor,
          class Ctx = parallel::Context<>>
struct FanCyqloneSolver {
    using value_type = T;
    using tricyqle_t = TricyqleSolver<VL, T, DefaultOrder, Ctx>;
    using Context    = Ctx;
    using SolverLast    = TridiagonalSolver<value_type>;
    using SharedContext = tricyqle_t::SharedContext;

    /// @}
    /// @name  Cyqlone and tridiag solver + workspaces
    /// @{
    index_t num_branches;

    // total shared context
    std::unique_ptr<SharedContext> create_parallel_context() const {
        return std::make_unique<SharedContext>(num_branches);
    }
    std::vector<SolverStorage<VL, value_type, DefaultOrder, Ctx>> solver_storage;

    // sizes of the problems
    index_t nu;
    index_t total_nx;
    index_t ny_0; ///< Number of general constraints at stage 0, D(0) u(0).
    /// Get the total number of primal variables in the OCP.
    /// @note The actual number of variable stored in Cyqlone's internal data structures may be
    ///       larger.
    [[nodiscard]] index_t num_variables() const {
        index_t num_var = 0;
        for (const auto &s : solver_storage) {
            num_var += nu * (s.solver_storage.N_horiz - 1) +
                       s.cyqlone_solver.nx * s.solver_storage.N_horiz;
        }
        return num_var + nu; // for u(0)
    }
    /// Get the total number of dynamics constraints in the OCP.
    /// @note The actual number of constraints stored in Cyqlone's internal data structures may be
    ///       larger.
    [[nodiscard]] index_t num_dynamics_constraints() const {
        index_t num_dyn_con = 0;
        for (const auto &s : solver_storage) {
            num_dyn_con += s.cyqlone_solver.nx * s.solver_storage.N_horiz;
        }
        return num_dyn_con;
    }
    /// Get the total number of general constraints in the OCP.
    /// @note The actual number of constraints stored in Cyqlone's internal data structures may be
    ///       larger.
    [[nodiscard]] index_t num_general_constraints() const {
        index_t num_gen_con = 0;
        for (const auto &s : solver_storage) {
            num_gen_con +=
                s.cyqlone_solver.ny * (s.solver_storage.N_horiz - 1) + s.cyqlone_solver.ny_N;
        }
        return num_gen_con + ny_0; // for D(0) u(0)
    }

    // Workspaces for contribution u(0)
    SolverLast::matrix SBs{{.depth = num_branches, .rows = nu, .cols = nu},
                           batmat::matrix::uninitialized};
    SolverLast::matrix rs{{.depth = num_branches, .rows = nu, .cols = 1},
                          batmat::matrix::uninitialized};
    SolverLast::matrix u0_sol{{.rows = nu, .cols = 1}};
    SolverLast::matrix λ0_sol{{.rows = total_nx, .cols = 1}};

    /// Number of processors/threads.
    const index_t p_fan;
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
    using matrix = batmat::matrix::Matrix<value_type, index_t, vl_t, index_t, O, align_t>;
    /// Non-owning immutable view type for @ref matrix.
    template <StorageOrder O = column_major>
    using view = batmat::matrix::View<const value_type, index_t, vl_t, index_t, index_t, O>;
    /// Non-owning mutable view type for @ref matrix.
    template <StorageOrder O = column_major>
    using mut_view     = batmat::matrix::View<value_type, index_t, vl_t, index_t, index_t, O>;
    using layer_stride = batmat::matrix::DefaultStride;
    /// Non-owning immutable view type for a single batch of v matrices.
    template <StorageOrder O = column_major>
    using batch_view = batmat::matrix::View<const value_type, index_t, vl_t, vl_t, layer_stride, O>;
    /// Non-owning mutable view type for a single batch of v matrices.
    template <StorageOrder O = column_major>
    using mut_batch_view = batmat::matrix::View<value_type, index_t, vl_t, vl_t, layer_stride, O>;



    /// Call a function for each stage in the horizon, passing the stage index, the data batch
    /// index, and optionally the corresponding batches of the given arrays.
    /// Iterates backwards in time (decreasing stage index j).
    void foreach_stage(Context &ctx, auto &&func, auto &&...xs) const {
        index_t i = ctx.total_context().index();
        solver_storage[i].foreach_stage(ctx.branch_context(), func, xs...);
        /// @todo: Handle u0 separately, since it is shared between branches
    }
    /// Call a function for each stage in the horizon, passing the stage index, the data batch
    /// index, and optionally the corresponding batches of the given arrays.
    /// Iterates forward in time (increasing stage index j).
    void foreach_stage_fwd(Context &ctx, auto &&func, auto &&...xs) const {
        index_t i = ctx.total_context().index();
        solver_storage[i].foreach_stage_fwd(ctx.branch_context(), func, xs...);
        /// @todo: Handle u0 separately, since it is shared between branches
    }
    static FanCyqloneSolver build(const CyqloneStorage<value_type> &ocp, index_t p,
                               CyqloneParams<value_type> params = {});
    /// Update the internal data structures to reflect changes in the OCP data (without changing
    /// the problem size).
    void update_data(const CyqloneStorage<value_type> &ocp);
    /// Initialize the right-hand side vector for the dynamics constraints of the OCP, using the
    /// custom Cyqlone storage format.
    void initialize_rhs(const CyqloneStorage<value_type> &ocp, mut_view<> rhs) const;
    /// @copydoc initialize_rhs
    matrix<> initialize_rhs(const CyqloneStorage<value_type> &ocp) const;
    /// Initialize the gradient vector for the OCP cost function, using the custom Cyqlone storage
    /// format.
    void initialize_gradient(const CyqloneStorage<value_type> &ocp, mut_view<> grad) const;
    /// @copydoc initialize_gradient
    matrix<> initialize_gradient(const CyqloneStorage<value_type> &ocp) const;
    /// Initialize the lower and upper bounds for the general constraints of the OCP, using the
    /// custom Cyqlone storage format.
    void initialize_bounds(const CyqloneStorage<value_type> &ocp, mut_view<> b_min,
                           mut_view<> b_max) const;
    /// @copydoc initialize_bounds
    std::pair<matrix<>, matrix<>> initialize_bounds(const CyqloneStorage<value_type> &ocp) const;

    /// @todo check and document behavior when `N_horiz != ceil_N()`.
    void pack_variables(std::span<const value_type> ux_lin, mut_view<> ux) const;
    matrix<> pack_variables(std::span<const value_type> ux_lin) const;
    void unpack_variables(view<> ux, std::span<value_type> ux_lin) const;
    std::vector<value_type> unpack_variables(view<> ux) const;
    void pack_dynamics(std::span<const value_type> λ_lin, mut_view<> λ) const;
    matrix<> pack_dynamics(std::span<const value_type> λ_lin) const;
    void unpack_dynamics(view<> λ, std::span<value_type> λ_lin) const;
    std::vector<value_type> unpack_dynamics(view<> λ) const;
    void pack_constraints(std::span<const value_type> y_lin, mut_view<> y,
                          value_type fill = 0) const;
    matrix<> pack_constraints(std::span<const value_type> y_lin, value_type fill = 0) const;
    void unpack_constraints(view<> y, std::span<value_type> y_lin) const;
    std::vector<value_type> unpack_constraints(view<> y) const;

    /// Get a zero-initialized matrix for the primal variables u and x.
    matrix<> initialize_variables() const;
    /// Get a zero-initialized matrix for the dynamics constraints (or their multipliers).
    matrix<> initialize_dynamics_constraints() const;
    /// Get a zero-initialized matrix for the general constraints (or their multipliers).
    matrix<> initialize_general_constraints() const;

    /// @}

    /// @name OCP cost gradient and constraints evaluation
    /// @{

    /// Compute Mx + b, where M is the dynamics constraint Jacobian matrix of the OCP.
    /// In other words, evaluate the residuals for all stages, i.e.,
    /// @f$ A_j x^j + B_j u^j - x^{j+1} + b^j @f$.
    void residual_dynamics_constr(Context &ctx, view<> x, view<> b, mut_view<> Mxb) const;
    /// Compute Mᵀλ, where M is the dynamics constraint Jacobian matrix of the OCP.
    /// Optionally add the result to the existing contents of Mᵀλ by setting @p accum to true.
    void transposed_dynamics_constr(Context &ctx, view<> λ, mut_view<> Mᵀλ,
                                    bool accum = false) const;
    /// Compute the general constraints Gx, where G is the general constraint Jacobian matrix of the
    /// OCP. In other words, evaluate the constraints for all stages, i.e.,
    /// @f$ C_j x^j + D_j u^j @f$.
    void general_constr(Context &ctx, view<> ux, mut_view<> DCux) const;
    /// Compute Gᵀy, where G is the general constraint Jacobian matrix of the OCP.
    void transposed_general_constr(Context &ctx, view<> y, mut_view<> DCᵀy) const;
    /// @copydoc transposed_general_constr
    /// @todo Remove.
    void transposed_general_constr(view<> y, mut_view<> DCᵀy) const;
    /// Compute the cost gradient, with optional scaling factors.
    /// grad_f ← Q ux + α q + β grad_f
    void cost_gradient(Context &ctx, view<> ux, value_type α, view<> q, value_type β,
                       mut_view<> grad_f) const;
    /// Compute the regularized cost gradient, with regularization parameter γ⁻¹, with respect to
    /// the point @p ux0.
    void cost_gradient_regularized(Context &ctx, value_type γ, view<> ux, view<> ux0, view<> q,
                                   mut_view<> grad_f) const;
    /// Subtract the regularization term from the cost gradient.
    void cost_gradient_remove_regularization(Context &ctx, value_type γ, view<> x, view<> x0,
                                             mut_view<> grad_f) const;

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
    void factor_solve(Context &ctx, value_type γ, real_t ρ_inv, view<> Σ, mut_view<> ux,
                      mut_view<> λ);
    /// Compute the Cyqlone factorization of the KKT matrix of the OCP.
    /// @see @ref factor_solve
    void factor(Context &ctx, value_type γ, real_t ρ_inv, view<> Σ);
    /// Perform a forward solve with the Cyqlone factorization.
    /// @see @ref factor_solve
    void solve_forward(Context &ctx, mut_view<> ux, mut_view<> λ);
    /// Perform a reverse solve with the Cyqlone factorization.
    /// @param ctx Parallel context.
    /// @param ux On entry, the result of the forward solve; on exit the solution of the primal
    ///           variables of the KKT system.
    /// @param λ On entry, the result of the forward solve; on exit the solution of the dual
    ///          variables corresponding to the dynamics constraints of the KKT system.
    void solve_reverse(Context &ctx, mut_view<> ux, mut_view<> λ);
    /// Fused variant of @ref solve_reverse and @ref transposed_dynamics_constr (for improved
    /// locality of the dynamics Jacobians).
    void solve_reverse_mul(Context &ctx, mut_view<> ux, mut_view<> λ, mut_view<> Mᵀλ);
    using ddp_func_t = void(Context &ctx, index_t i, batch_view<default_order> F, batch_view<> ux,
                            batch_view<> b, mut_batch_view<> x_next);
    /// Perform a reverse solve with the Cyqlone factorization, using the given dynamics function,
    /// which can be used to implement differential dynamic programming (DDP).
    /// @param ctx Parallel context.
    /// @param ux On entry, the result of the forward solve; on exit the solution of the primal
    ///           variables of the KKT system.
    /// @param λ On entry, the result of the forward solve; on exit the solution of the dual
    ///          variables corresponding to the dynamics constraints of the KKT system.
    void solve_reverse_ddp(Context &ctx, mut_view<> ux, mut_view<> λ, real_t α,
                           const std::function<ddp_func_t> &simulate);
    /// Fused variant of @ref solve_reverse_ddp and @ref transposed_dynamics_constr (for improved
    /// locality of the dynamics Jacobians).
    void solve_reverse_mul_ddp(Context &ctx, mut_view<> ux, mut_view<> λ, real_t α,
                               const std::function<ddp_func_t> &simulate, mut_view<> Mᵀλ);
    /// Perform factorization updates of the Cyqlone factorization as described by
    /// Algorithm 4 in the paper.
    /// @param ctx Parallel context.
    /// @param ΔΣ Changes to the ALM penalty factors Σ.
    void update(Context &ctx, view<> ΔΣ);
    /// Fused variant of @ref update and @ref solve_forward.
    void update_solve(Context &ctx, view<> ΔΣ, mut_view<> ux, mut_view<> λ);

    /// @}

    /// @name Low-level factorization and forward solve routines
    /// @{

    index_t riccati_thread_assignment(Context &ctx) const { return add_wrap_p(ctx.index, 1); }
    template <bool Factor = true, bool Solve = true>
    void factor_riccati_solve(Context &ctx, value_type γ, view<> Σ, mut_view<> ux, mut_view<> λ);
    template <bool Factor = true, bool Solve = true>
    void compute_schur(Context &ctx, real_t ρ_inv, mut_view<> ux, mut_view<> λ);

    /// @}

    /// @name Low-level factorization and forward solve routines for parallel cyclic reduction
    /// @{

    template <bool Factor = true, bool Solve = true>
    void factor_solve_impl(Context &ctx, value_type γ, real_t ρ_inv, view<> Σ, mut_view<> ux,
                           mut_view<> λ);

    /// @}

    /// @name Low-level reverse solve routines
    /// @{

    template <class F>
    void solve_riccati_reverse_impl(Context &ctx, mut_view<> ux, mut_view<> λ, mut_view<> work,
                                    real_t α, const F &simulate,
                                    std::optional<mut_view<>> Mᵀλ) const;
    void solve_riccati_reverse(Context &ctx, mut_view<> ux, mut_view<> λ, mut_view<> work,
                               std::optional<mut_view<>> Mᵀλ) const;
    void solve_riccati_reverse_ddp(Context &ctx, mut_view<> ux, mut_view<> λ, mut_view<> work,
                                   real_t α, const std::function<ddp_func_t> &simulate,
                                   std::optional<mut_view<>> Mᵀλ) const;
    void solve_reverse(Context &ctx, mut_view<> ux, mut_view<> λ, mut_view<> work,
                       std::optional<mut_view<>> Mᵀλ = std::nullopt) const;

    /// @}

    /// @name Low-level factorization update routines
    /// @{

    /// Update the modified Riccati factorization of a single block column as described by
    /// Algorithm 3 in the paper.
    template <bool Solve = true>
    void update_riccati_solve(Context &ctx, view<> ΔΣ, mut_view<> ux, mut_view<> λ);
    void update_riccati(Context &ctx, view<> ΔΣ) { update_riccati_solve<false>(ctx, ΔΣ, {}, {}); }
    template <bool Solve = true>
    void update_solve_impl(Context &ctx, view<> ΔΣ, mut_view<> ux, mut_view<> λ);

    /// @}

    /// @name Build sparse representations for debugging and testing
    /// @{

    [[nodiscard]] SparseMatrix build_sparse(const CyqloneStorage<value_type> &ocp,
                                            std::span<const value_type> Σ) const;
    [[nodiscard]] SparseMatrix build_sparse_no_penalty() const;
    [[nodiscard]] std::vector<value_type> build_rhs(view<> rq, view<> b, value_type scale_rq = -1,
                                                    value_type scale_b = -1) const;
    [[nodiscard]] std::vector<value_type> build_sol(view<> ux, view<> λ) const {
        return build_rhs(ux, λ, 1, 1);
    }
    [[nodiscard]] SparseMatrix build_sparse_factor() const;
    [[nodiscard]] SparseMatrix build_sparse_diag() const;
    [[nodiscard]] SparseMatrix build_sparse_reg(real_t γ, real_t ρ_inv_internal,
                                                real_t ρ_inv_windows) cons
};
} // namespace CYQLONE_NS(cyqlone)