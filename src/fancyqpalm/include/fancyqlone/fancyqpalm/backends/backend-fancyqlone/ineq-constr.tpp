#pragma once

#include <fancyqlone/linalg.hpp>
#include <fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.tpp>
#include <batmat/simd.hpp>
#include <iostream>

namespace FANCYQLONE_NS(fancyqlone::qpalm) {

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
index_t CyQPALMBackend<VL, DefaultOrder, LinearSolver>::update_penalty_y(
    Context &ctx, ineq_constr_vec_t &Σ, const ineq_constr_vec_t &e, const ineq_constr_vec_t &e_old,
    const PenaltySettings &settings) {
    GUANAQO_TRACE("update_penalty_y", 0);
    auto t                  = get_timed(&Timings::update_penalty_y);
    const real_t min_denom  = 1e-6;
    const real_t norm_inf_e = fmax(min_denom, norm_inf(ctx, e));
    index_t num_changed     = 0;
    const auto update_simd  = [&](auto Σji, auto eji, auto eji_old) {
        using batmat::datapar::select;
        using batmat::datapar::reduce_count;
        auto insufficient_progress = abs(eji) >= settings.θ * abs(eji_old);
        auto update_factor =
            select(insufficient_progress, settings.Δy * abs(eji) / norm_inf_e, decltype(eji){1});
        update_factor *= settings.Δy_always;
        auto Σ_new = Σji * update_factor;
        Σ_new      = fmax(Σji * settings.Δy_always, fmin(Σ_new, decltype(Σ_new){settings.max_penalty_y}));
        num_changed += reduce_count(Σ_new != Σji);
        return Σ_new;
    };
    const auto update_batch = [&](auto Σj, auto ej, auto ej_old) {
        linalg::transform_elementwise(update_simd, Σj, Σj, ej, ej_old);
    };
    ocp.foreach_batch(ctx, update_batch, Σ, e, e_old);
    return ctx.reduce(num_changed);
}

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
void CyQPALMBackend<VL, DefaultOrder, LinearSolver>::ineq_constr_resid(Context &ctx,
                                                                       const ineq_constr_vec_t &Ax,
                                                                       ineq_constr_vec_t &e) const {
    GUANAQO_TRACE("ineq_constr_resid", 0);
    auto t                       = get_timed(&Timings::ineq_constr_resid);
    const auto ineq_constr_resid = [](auto Axj, auto b_minj, auto b_maxj, auto ej) {
        linalg::clamp_resid(Axj, b_minj, b_maxj, ej);
    };
    ocp.foreach_batch(ctx, ineq_constr_resid, Ax, b_min_strided, b_max_strided, e);
}

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
void CyQPALMBackend<VL, DefaultOrder, LinearSolver>::project_multipliers_ineq(
    Context &ctx, ineq_constr_vec_t &y) const {
    GUANAQO_TRACE("project_multipliers_ineq", 0);
    const auto proj_simd = [](auto yji, auto b_minji, auto b_maxji) {
        using batmat::datapar::select;
        yji = select(isfinite(b_minji), yji, fmax(yji, decltype(yji){0}));
        yji = select(isfinite(b_maxji), yji, fmin(yji, decltype(yji){0}));
        return yji;
    };
    const auto proj_batch = [&](auto yji, auto b_minji, auto b_maxji) {
        linalg::transform_elementwise(proj_simd, yji, yji, b_minji, b_maxji);
    };
    ocp.foreach_batch(ctx, proj_batch, y, b_min_strided, b_max_strided);
}

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
real_t CyQPALMBackend<VL, DefaultOrder, LinearSolver>::ineq_constr_viol(
    Context &ctx, const ineq_constr_vec_t &Ax) const {
    GUANAQO_TRACE("ineq_constr_viol", 0);
    static constexpr auto norms_simd = batmat::linalg::norms<real_t, typename traits::simd>{};
    using simd_scal = batmat::datapar::simd<real_t, batmat::datapar::scalar_abi<real_t>>;
    static constexpr auto norms_simd_scal = batmat::linalg::norms<real_t, simd_scal>{};
    static constexpr auto norms_scal      = batmat::linalg::norms<real_t>{};
    auto t                                = get_timed(&Timings::ineq_constr_viol);
    auto nrm_simd                         = norms_simd.zero_simd();
    auto nrm_simd_scal                    = norms_simd_scal.zero_simd();
    const auto viol_simd                  = [&](auto Axji, auto b_minji, auto b_maxji) {
        auto zi = fmax(b_minji, fmin(Axji, b_maxji));
        if constexpr (std::is_same_v<decltype(Axji), simd_scal>) {
            nrm_simd_scal = norms_simd_scal(nrm_simd_scal, Axji - zi);
        } else {
            nrm_simd = norms_simd(nrm_simd, Axji - zi);
        }
    };
    const auto viol_batch = [&](auto Axj, auto b_min_j, auto b_max_j) {
        linalg::for_each_elementwise(viol_simd, Axj, b_min_j, b_max_j);
    };

    ocp.foreach_batch(ctx, viol_batch, Ax, b_min_strided, b_max_strided);
    auto nrm_scal = norms_simd_scal(nrm_simd_scal);
    nrm_scal      = norms_scal(nrm_scal, norms_simd(nrm_simd));
    // auto nrms_scal = norms_scal.zeros();
    return ctx.reduce(nrm_scal, norms_scal).norm_inf();
}

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
real_t CyQPALMBackend<VL, DefaultOrder, LinearSolver>::ineq_constr_resid_al(
    Context &ctx, const ineq_constr_vec_t &y, const ineq_constr_vec_t &ŷ,
    const ineq_constr_vec_t &Σ, ineq_constr_vec_t &e) {
    GUANAQO_TRACE("ineq_constr_resid_al", 0);
    static constexpr auto norms_simd = batmat::linalg::norms<real_t, typename traits::simd>{};
    using simd_scal = batmat::datapar::simd<real_t, batmat::datapar::scalar_abi<real_t>>;
    static constexpr auto norms_simd_scal = batmat::linalg::norms<real_t, simd_scal>{};
    static constexpr auto norms_scal      = batmat::linalg::norms<real_t>{};

    auto t                           = get_timed(&Timings::ineq_constr_resid_al);
    auto nrm_simd                    = norms_simd.zero_simd();
    auto nrm_simd_scal               = norms_simd_scal.zero_simd();
    const auto resid_simd            = [&](auto yji, auto ŷji, auto Σji) {
        auto ei = (ŷji - yji) / Σji;
        if constexpr (std::is_same_v<decltype(yji), simd_scal>) {
            nrm_simd_scal = norms_simd_scal(nrm_simd_scal, ei);
        } else {
            nrm_simd = norms_simd(nrm_simd, ei);
        }
        return ei;
    };
    const auto resid_batch = [&](auto ej, auto yj, auto ŷj, auto Σj) {
        linalg::transform_elementwise(resid_simd, ej, yj, ŷj, Σj);
    };
    ocp.foreach_batch(ctx, resid_batch, e, y, ŷ, Σ);
    auto nrm_scal = norms_simd_scal(nrm_simd_scal);
    nrm_scal      = norms_scal(nrm_scal, norms_simd(nrm_simd));
    // auto nrms_scal = norms_scal.zeros();
    return ctx.reduce(nrm_scal, norms_scal).norm_inf();
}

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
index_t CyQPALMBackend<VL, DefaultOrder, LinearSolver>::calc_ŷ_Aᵀŷ(
    Context &ctx, const ineq_constr_vec_t &Ax, const ineq_constr_vec_t &Σ,
    const ineq_constr_vec_t &y, ineq_constr_vec_t &ŷ, var_vec_t &Aᵀŷ, active_set_t &J) {
    index_t count_J   = 0;
    const auto ŷ_simd = [&count_J](auto Σi, auto yi, auto Axi, auto li, auto ui) {
        using batmat::datapar::select;
        using batmat::datapar::reduce_count;
        auto ζ = Axi + yi / Σi, z = fmax(li, fmin(ζ, ui));
        auto Ji = z != ζ; // TODO: inclusive?
#if 0
        simd ŷi{0};
        where(Ji, ŷi) = yi + Σi * (Axi - z);
#else
        auto ŷi = yi + Σi * (Axi - z);
#endif
        auto ΣJi = select(Ji, Σi, decltype(Σi){0});
        count_J += static_cast<index_t>(reduce_count(Ji));
        return std::make_pair(ŷi, ΣJi);
    };
    const auto ŷ_batch = [&ŷ_simd](auto ŷi, auto Ji, auto Σi, auto yi, auto Axi, auto li, auto ui) {
        linalg::transform2_elementwise(ŷ_simd, ŷi, Ji, //
                                       Σi, yi, Axi, li, ui);
    };
    {
        auto t = get_timed(&Timings::calc_y_hat);
        ocp.foreach_batch(ctx, ŷ_batch, ŷ, J, Σ, y, Ax, b_min_strided, b_max_strided);
    }
    auto t = get_timed(&Timings::calc_y_hat_AT);
    // ocp.print_grad(ctx,ŷ, "ŷ");
    // ocp.print_grad(ctx, Ax, "Ax");
    // ocp.print_grad(ctx, y, "Y");
    // ocp.print_grad(ctx, b_min_strided, "b_min");
    // ocp.print_grad(ctx, b_max_strided, "b_max");
    // ocp.print_grad(ctx, Σ, "Σ")


    mat_vec_AT(ctx, ŷ, Aᵀŷ);
    // ocp.print_grad(ctx, Aᵀŷ, "Aᵀŷ");
    // std::cout << "count_J = " << count_J << std::endl;
    return ctx.reduce(count_J);
}

} // namespace FANCYQLONE_NS(fancyqlone::qpalm)
