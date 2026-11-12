#include <fancyqlone/ocp.hpp>
#include <batmat/linalg/norms.hpp>
#include <guanaqo/blas/hl-blas-interface.hpp>
#include <guanaqo/print.hpp>

#include <limits>
#include <numeric>
#include <iostream>
namespace fancyqlone {

auto LinearOCPStorage::compute_kkt_error(const Solution &sol) const -> KKTError {
    // std::cout << "Computing KKT error..." << std::endl;
    using std::clamp;
    const auto [N, nx, nu, ny, ny_N] = dim;
    std::vector<real_t> dual_residual_sto(sol.solution.size());
    auto dual_residual = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_sto);
    auto x             = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.solution),
         y = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.inequality_multipliers),
         λ = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.equality_multipliers);

    // Stationarity
    dual_residual = qr();

    for (index_t j = 0; j < N; ++j) {
        
        auto xuj = x.middle_rows(j * (nx + nu), nx + nu), λj = λ.middle_rows(j * nx, nx),
             λj_next = λ.middle_rows((j + 1) * nx, nx), yj = y.middle_rows(j * ny, ny);
        auto rj = dual_residual.middle_rows(j * (nx + nu), nx + nu);
        guanaqo::blas::xsymv_L(real_t{1}, H(j), xuj, real_t{1}, rj);
        guanaqo::blas::xgemv_T(real_t{1}, AB(j), λj_next, real_t{1}, rj);
        
        if (ny > 0)
            guanaqo::blas::xgemv_T(real_t{1}, CD(j), yj, real_t{1}, rj);
        
        for (index_t i = 0; i < nx; ++i)
            rj(i, 0) -= λj(i, 0);
    }
    auto xN = x.bottom_rows(nx), λN = λ.bottom_rows(nx), yN = y.bottom_rows(ny_N);
    auto rN = dual_residual.bottom_rows(nx);
    guanaqo::blas::xsymv_L(real_t{1}, Q(N), xN, real_t{1}, rN);
    if (ny_N > 0)
        guanaqo::blas::xgemv_T(real_t{1}, C(N), yN, real_t{1}, rN);
    for (index_t i = 0; i < nx; ++i)
        rN(i, 0) -= λN(i, 0);
    const auto norms = batmat::linalg::norms<real_t>{};
    auto stat_norm   = std::accumulate(dual_residual.data, dual_residual.data + dual_residual.rows,
                                       norms.zero(), norms);
    // Inequality constraints
    auto ineq_res_sto = std::vector<real_t>(sol.inequality_multipliers.size());
    auto ineq_res     = guanaqo::MatrixView<real_t, index_t>::as_column(ineq_res_sto);
    auto compl_norm   = norms.zero();
    using std::fmax;
    using std::fmin;
    const auto eps = std::numeric_limits<real_t>::epsilon(), big = 1 / (eps * eps);
    for (index_t j = 0; j < N; ++j) {
       
            auto xuj = x.middle_rows(j * (nx + nu), nx + nu), yj = y.middle_rows(j * ny, ny);
            auto lbj = b_min(j), ubj = b_max(j);
            auto cj = ineq_res.middle_rows(j * ny, ny);
        if (ny > 0)
            guanaqo::blas::xgemv_N(real_t{1}, CD(j), xuj, real_t{-1}, cj);
        for (index_t i = 0; i < ny; ++i) {
            compl_norm =
                norms(compl_norm, yj(i, 0) > 0 ? yj(i, 0) * (cj(i, 0) - fmin(ubj(i, 0), +big))
                                               : yj(i, 0) * (cj(i, 0) - fmax(lbj(i, 0), -big)));
            cj(i, 0) -= clamp(cj(i, 0), lbj(i, 0), ubj(i, 0));
        }
    }
    auto cN = ineq_res.bottom_rows(ny_N);
    if (ny_N > 0)
        guanaqo::blas::xgemv_N(real_t{1}, C(N), xN, real_t{-1}, cN);
    auto lbN = b_min().bottom_rows(ny_N), ubN = b_max().bottom_rows(ny_N);
    for (index_t i = 0; i < ny_N; ++i) {
        compl_norm =
            norms(compl_norm, yN(i, 0) > 0 ? yN(i, 0) * (cN(i, 0) - fmin(ubN(i, 0), +big))
                                           : yN(i, 0) * (cN(i, 0) - fmax(lbN(i, 0), -big)));
        cN(i, 0) -= clamp(cN(i, 0), lbN(i, 0), ubN(i, 0));
    }
    auto ineq_norm =
        std::accumulate(ineq_res.data, ineq_res.data + ineq_res.rows, norms.zero(), norms);
    // Complementarity: lb - Cx <= 0    and    Cx - ub <= 0

    // Equality constraints

    auto eq_res_sto = std::vector<real_t>(sol.equality_multipliers.size());
    auto eq_res     = guanaqo::MatrixView<real_t, index_t>::as_column(eq_res_sto);

    eq_res          = b();

    for (index_t j = 0; j <= N; ++j) {
        auto xj = x.middle_rows(j * (nx + nu), nx);
        auto cj = eq_res.middle_rows(j * nx, nx);
        for (index_t i = 0; i < nx; ++i)
            cj(i, 0) -= xj(i, 0);
        if (j > 0) {
            auto xu_prev = x.middle_rows((j - 1) * (nx + nu), nx + nu);
            guanaqo::blas::xgemv_N(real_t{1}, AB(j - 1), xu_prev, real_t{1}, cj);
        }
    }
    auto eq_norm = std::accumulate(eq_res.data, eq_res.data + eq_res.rows, norms.zero(), norms);
    return {
        .stationarity        = stat_norm.norm_inf(),
        .inequality_residual = ineq_norm.norm_inf(),
        .equality_residual   = eq_norm.norm_inf(),
        .complementarity     = compl_norm.norm_inf(),
    };
}
auto LinearOCPStorage::compute_kkt_error_u0_seperated(const Solution &sol) const -> KKTErroru0Seperated {
    // std::cout << "Computing KKT error..." << std::endl;
    using std::clamp;
    const auto [N, nx, nu, ny, ny_N] = dim;
    std::vector<real_t> dual_residual_sto(sol.solution.size());
    std::vector<real_t> dual_residual_u0_sto(nu);
    auto dual_residual = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_sto);
    auto dual_residual_u0 = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_u0_sto);

    auto x             = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.solution),
         y = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.inequality_multipliers),
         λ = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.equality_multipliers);

    // Stationarity
    dual_residual = qr();
    for (index_t j = 0; j < N; ++j) {
        
        auto xuj = x.middle_rows(j * (nx + nu), nx + nu), λj = λ.middle_rows(j * nx, nx),
             λj_next = λ.middle_rows((j + 1) * nx, nx), yj = y.middle_rows(j * ny, ny);
        auto rj = dual_residual.middle_rows(j * (nx + nu), nx + nu);
        guanaqo::blas::xsymv_L(real_t{1}, H(j), xuj, real_t{1}, rj);
        guanaqo::blas::xgemv_T(real_t{1}, AB(j), λj_next, real_t{1}, rj);
       
        if (ny > 0)
            guanaqo::blas::xgemv_T(real_t{1}, CD(j), yj, real_t{1}, rj);
        for (index_t i = 0; i < nx; ++i)
            rj(i, 0) -= λj(i, 0);
    }
    dual_residual_u0 = dual_residual.middle_rows(nx, nu);
    dual_residual.middle_rows(nx, nu).set_constant(0);

    auto xN = x.bottom_rows(nx), λN = λ.bottom_rows(nx), yN = y.bottom_rows(ny_N);
    auto rN = dual_residual.bottom_rows(nx);
    guanaqo::blas::xsymv_L(real_t{1}, Q(N), xN, real_t{1}, rN);
    if (ny_N > 0)
        guanaqo::blas::xgemv_T(real_t{1}, C(N), yN, real_t{1}, rN);
    for (index_t i = 0; i < nx; ++i)
        rN(i, 0) -= λN(i, 0);
    const auto norms = batmat::linalg::norms<real_t>{};
    auto stat_norm   = std::accumulate(dual_residual.data, dual_residual.data + dual_residual.rows,
                                       norms.zero(), norms);
    // Inequality constraints
    auto ineq_res_sto = std::vector<real_t>(sol.inequality_multipliers.size());
    auto ineq_res     = guanaqo::MatrixView<real_t, index_t>::as_column(ineq_res_sto);
    auto compl_norm   = norms.zero();
    using std::fmax;
    using std::fmin;
    const auto eps = std::numeric_limits<real_t>::epsilon(), big = 1 / (eps * eps);
    for (index_t j = 0; j < N; ++j) {
       
            auto xuj = x.middle_rows(j * (nx + nu), nx + nu), yj = y.middle_rows(j * ny, ny);
            auto lbj = b_min(j), ubj = b_max(j);
            auto cj = ineq_res.middle_rows(j * ny, ny);
        if (ny > 0)
            guanaqo::blas::xgemv_N(real_t{1}, CD(j), xuj, real_t{-1}, cj);
        for (index_t i = 0; i < ny; ++i) {
            compl_norm =
                norms(compl_norm, yj(i, 0) > 0 ? yj(i, 0) * (cj(i, 0) - fmin(ubj(i, 0), +big))
                                               : yj(i, 0) * (cj(i, 0) - fmax(lbj(i, 0), -big)));
            cj(i, 0) -= clamp(cj(i, 0), lbj(i, 0), ubj(i, 0));
        }
    }
    auto cN = ineq_res.bottom_rows(ny_N);
    if (ny_N > 0)
        guanaqo::blas::xgemv_N(real_t{1}, C(N), xN, real_t{-1}, cN);
    auto lbN = b_min().bottom_rows(ny_N), ubN = b_max().bottom_rows(ny_N);
    for (index_t i = 0; i < ny_N; ++i) {
        compl_norm =
            norms(compl_norm, yN(i, 0) > 0 ? yN(i, 0) * (cN(i, 0) - fmin(ubN(i, 0), +big))
                                           : yN(i, 0) * (cN(i, 0) - fmax(lbN(i, 0), -big)));
        cN(i, 0) -= clamp(cN(i, 0), lbN(i, 0), ubN(i, 0));
    }
    auto ineq_norm =
        std::accumulate(ineq_res.data, ineq_res.data + ineq_res.rows, norms.zero(), norms);
    // Complementarity: lb - Cx <= 0    and    Cx - ub <= 0

    // Equality constraints

    auto eq_res_sto = std::vector<real_t>(sol.equality_multipliers.size());
    auto eq_res     = guanaqo::MatrixView<real_t, index_t>::as_column(eq_res_sto);

    eq_res          = b();

    for (index_t j = 0; j <= N; ++j) {
        auto xj = x.middle_rows(j * (nx + nu), nx);
        auto cj = eq_res.middle_rows(j * nx, nx);
        for (index_t i = 0; i < nx; ++i)
            cj(i, 0) -= xj(i, 0);
        if (j > 0) {
            auto xu_prev = x.middle_rows((j - 1) * (nx + nu), nx + nu);
            guanaqo::blas::xgemv_N(real_t{1}, AB(j - 1), xu_prev, real_t{1}, cj);
        }
    }
    auto eq_norm = std::accumulate(eq_res.data, eq_res.data + eq_res.rows, norms.zero(), norms);
    return {{
        .stationarity        = stat_norm.norm_inf(),
        .inequality_residual = ineq_norm.norm_inf(),
        .equality_residual   = eq_norm.norm_inf(),
        .complementarity     = compl_norm.norm_inf(),}  , dual_residual_u0_sto
        };
}
auto LinearOCPStorage::compute_kkt_error_u0x0_seperated(const Solution &sol) const -> KKTErroru0x0Seperated {
    // std::cout << "Computing KKT error..." << std::endl;
    using std::clamp;
    const auto [N, nx, nu, ny, ny_N] = dim;
    std::vector<real_t> dual_residual_sto(sol.solution.size());
    std::vector<real_t> dual_residual_u0_sto(nu);
    auto dual_residual = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_sto);
            auto dual_residual_u0 = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_u0_sto);
    std::vector<real_t> dual_residual_x0_sto(nx);
    auto dual_residual_x0 = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_x0_sto);

    auto x             = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.solution),
         y = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.inequality_multipliers),
         λ = guanaqo::MatrixView<const real_t, index_t>::as_column(sol.equality_multipliers);

    // Stationarity
    dual_residual = qr();
    for (index_t j = 0; j < N; ++j) {
        
        auto xuj = x.middle_rows(j * (nx + nu), nx + nu), λj = λ.middle_rows(j * nx, nx),
             λj_next = λ.middle_rows((j + 1) * nx, nx), yj = y.middle_rows(j * ny, ny);
        auto rj = dual_residual.middle_rows(j * (nx + nu), nx + nu);
        guanaqo::blas::xsymv_L(real_t{1}, H(j), xuj, real_t{1}, rj);
        guanaqo::blas::xgemv_T(real_t{1}, AB(j), λj_next, real_t{1}, rj);
       
        if (ny > 0)
            guanaqo::blas::xgemv_T(real_t{1}, CD(j), yj, real_t{1}, rj);
        for (index_t i = 0; i < nx; ++i)
            rj(i, 0) -= λj(i, 0);
    }
    dual_residual_u0 = dual_residual.middle_rows(nx, nu);
    dual_residual_x0 = dual_residual.middle_rows(0, nx);

    dual_residual.middle_rows(nx, nu).set_constant(0);
    dual_residual.middle_rows(0, nx).set_constant(0);

    auto xN = x.bottom_rows(nx), λN = λ.bottom_rows(nx), yN = y.bottom_rows(ny_N);
    auto rN = dual_residual.bottom_rows(nx);
    guanaqo::blas::xsymv_L(real_t{1}, Q(N), xN, real_t{1}, rN);
    if (ny_N > 0)
        guanaqo::blas::xgemv_T(real_t{1}, C(N), yN, real_t{1}, rN);
    for (index_t i = 0; i < nx; ++i)
        rN(i, 0) -= λN(i, 0);
    const auto norms = batmat::linalg::norms<real_t>{};
    auto stat_norm   = std::accumulate(dual_residual.data, dual_residual.data + dual_residual.rows,
                                       norms.zero(), norms);
    // Inequality constraints
    auto ineq_res_sto = std::vector<real_t>(sol.inequality_multipliers.size());
    auto ineq_res     = guanaqo::MatrixView<real_t, index_t>::as_column(ineq_res_sto);
    auto compl_norm   = norms.zero();
    using std::fmax;
    using std::fmin;
    const auto eps = std::numeric_limits<real_t>::epsilon(), big = 1 / (eps * eps);
    for (index_t j = 0; j < N; ++j) {
       
            auto xuj = x.middle_rows(j * (nx + nu), nx + nu), yj = y.middle_rows(j * ny, ny);
            auto lbj = b_min(j), ubj = b_max(j);
            auto cj = ineq_res.middle_rows(j * ny, ny);
        if (ny > 0)
            guanaqo::blas::xgemv_N(real_t{1}, CD(j), xuj, real_t{-1}, cj);
        for (index_t i = 0; i < ny; ++i) {
            compl_norm =
                norms(compl_norm, yj(i, 0) > 0 ? yj(i, 0) * (cj(i, 0) - fmin(ubj(i, 0), +big))
                                               : yj(i, 0) * (cj(i, 0) - fmax(lbj(i, 0), -big)));
            cj(i, 0) -= clamp(cj(i, 0), lbj(i, 0), ubj(i, 0));
        }
    }
    auto cN = ineq_res.bottom_rows(ny_N);
    if (ny_N > 0)
        guanaqo::blas::xgemv_N(real_t{1}, C(N), xN, real_t{-1}, cN);
    auto lbN = b_min().bottom_rows(ny_N), ubN = b_max().bottom_rows(ny_N);
    for (index_t i = 0; i < ny_N; ++i) {
        compl_norm =
            norms(compl_norm, yN(i, 0) > 0 ? yN(i, 0) * (cN(i, 0) - fmin(ubN(i, 0), +big))
                                           : yN(i, 0) * (cN(i, 0) - fmax(lbN(i, 0), -big)));
        cN(i, 0) -= clamp(cN(i, 0), lbN(i, 0), ubN(i, 0));
    }
    auto ineq_norm =
        std::accumulate(ineq_res.data, ineq_res.data + ineq_res.rows, norms.zero(), norms);
    // Complementarity: lb - Cx <= 0    and    Cx - ub <= 0

    // Equality constraints

    auto eq_res_sto = std::vector<real_t>(sol.equality_multipliers.size());
    auto eq_res     = guanaqo::MatrixView<real_t, index_t>::as_column(eq_res_sto);

    eq_res          = b();

    for (index_t j = 0; j <= N; ++j) {
        auto xj = x.middle_rows(j * (nx + nu), nx);
        auto cj = eq_res.middle_rows(j * nx, nx);
        for (index_t i = 0; i < nx; ++i)
            cj(i, 0) -= xj(i, 0);
        if (j > 0) {
            auto xu_prev = x.middle_rows((j - 1) * (nx + nu), nx + nu);
            guanaqo::blas::xgemv_N(real_t{1}, AB(j - 1), xu_prev, real_t{1}, cj);
        }
    }
    auto eq_norm = std::accumulate(eq_res.data, eq_res.data + eq_res.rows, norms.zero(), norms);
    return {{
        .stationarity        = stat_norm.norm_inf(),
        .inequality_residual = ineq_norm.norm_inf(),
        .equality_residual   = eq_norm.norm_inf(),
        .complementarity     = compl_norm.norm_inf(),}  , dual_residual_u0_sto, dual_residual_x0_sto
        };
}

auto FanOCPStorage::compute_kkt_error(const Solution &sol, bool hpipm) const -> KKTError {
    KKTError kkt_error{
        .stationarity        = 0,
        .inequality_residual = 0,
        .equality_residual   = 0,
        .complementarity     = 0,
    };
    auto nu = ocps[0].dim.nu;
    std::vector<real_t> dual_residual_u0_sto(nu);
    auto dual_residual_u0 = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_u0_sto);
    auto dual_residual_x0_sto = std::vector<real_t>(ocps[0].dim.nx);
    auto dual_residual_x0 = guanaqo::MatrixView<real_t, index_t>::as_column(dual_residual_x0_sto);
    dual_residual_u0.set_constant(0);
// It is assumed that u^0=u^0_j for all branches j so we can skip this constraint in the KKT error computation
    for (index_t i = 0; i < num_branches(); ++i) {
        if (hpipm) {
            auto ocp_kkt_error = ocps[i].compute_kkt_error_u0x0_seperated(sol.solutions[i]);
            dual_residual_u0 += guanaqo::MatrixView<real_t, index_t>::as_column(ocp_kkt_error.stationarity_u0);
            kkt_error.stationarity =
                std::max(kkt_error.stationarity, ocp_kkt_error.kkt.stationarity);
            kkt_error.inequality_residual =
                std::max(kkt_error.inequality_residual, ocp_kkt_error.kkt.inequality_residual);
            kkt_error.equality_residual =
                std::max(kkt_error.equality_residual, ocp_kkt_error.kkt.equality_residual);
            kkt_error.complementarity =
                std::max(kkt_error.complementarity, ocp_kkt_error.kkt.complementarity);
        } else {
        auto ocp_kkt_error = ocps[i].compute_kkt_error_u0_seperated(sol.solutions[i]);
        dual_residual_u0 += guanaqo::MatrixView<real_t, index_t>::as_column(ocp_kkt_error.stationarity_u0);
        kkt_error.stationarity =
            std::max(kkt_error.stationarity, ocp_kkt_error.kkt.stationarity);
        kkt_error.inequality_residual =
            std::max(kkt_error.inequality_residual, ocp_kkt_error.kkt.inequality_residual);
        kkt_error.equality_residual =
            std::max(kkt_error.equality_residual, ocp_kkt_error.kkt.equality_residual);
        kkt_error.complementarity =
            std::max(kkt_error.complementarity, ocp_kkt_error.kkt.complementarity);
        // std::cout << "Done KKT error..." << std::endl;
        // std::cout << "Branch " << i << " KKT error: stationarity = " << ocp_kkt_error.kkt.stationarity
        //           << ", inequality_residual = " << ocp_kkt_error.kkt.inequality_residual
        //           << ", equality_residual = " << ocp_kkt_error.kkt.equality_residual
        //           << ", complementarity = " << ocp_kkt_error.kkt.complementarity << std::endl;

    }}
    const auto norms = batmat::linalg::norms<real_t>{};

    auto stat_norm   = std::accumulate(dual_residual_u0.data, dual_residual_u0.data + dual_residual_u0.rows,
                                       norms.zero(), norms);
    auto stat_norm_x0   = std::accumulate(dual_residual_x0.data, dual_residual_x0.data + dual_residual_x0.rows,
                                       norms.zero(), norms);                                   
    kkt_error.stationarity = std::max(kkt_error.stationarity, stat_norm.norm_inf());
    kkt_error.stationarity = std::max(kkt_error.stationarity, stat_norm_x0.norm_inf());

    return kkt_error;
}
} // namespace fancyqlone
