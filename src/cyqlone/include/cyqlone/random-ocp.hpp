#pragma once

#include <cyqlone/config.hpp>
#include <cyqlone/ocp.hpp>
#include <random>

namespace cyqlone {

/// Generates a random linear OCP with the given dimensions and random seed.
/// @ingroup topic-ocp-formulations
inline LinearOCPStorage generate_random_ocp(OCPDim dim, uint_fast32_t seed = 0) {
    LinearOCPStorage ocp{.dim = dim};
    auto [N, nx, nu, ny, ny_N] = ocp.dim;

    using std::abs;
    std::mt19937 rng{seed};
    std::uniform_real_distribution<real_t> uni{-1, 1};
    std::bernoulli_distribution bernoulli{0.5};

    // Dynamics and constraint matrices
    for (index_t i = 0; i < N; ++i) {
        auto Ai = ocp.A(i), Bi = ocp.B(i), Ci = ocp.C(i), Di = ocp.D(i);
        auto Qi = ocp.Q(i), Ri = ocp.R(i), Si = ocp.S(i), Hi = ocp.H(i);
        Ai.generate([&] { return uni(rng) * 0.9; });
        Bi.generate([&] { return uni(rng); });
        Ci.generate([&] { return uni(rng); });
        Di.generate([&] { return uni(rng); });
        Qi.generate([&] { return uni(rng); });
        Ri.generate([&] { return uni(rng); });
        Si.generate([&] { return uni(rng); });
        // Make sure H(i) is SPD
        Hi.add_to_diagonal(2 * static_cast<real_t>(nx + nu));
        for (index_t c = 0; c < nx + nu; ++c)
            for (index_t r = c + 1; r < nx + nu; ++r)
                Hi(c, r) = Hi(r, c);
        auto qi = ocp.q(i), ri = ocp.r(i), bi = ocp.b(i);
        qi.generate([&] { return uni(rng); });
        ri.generate([&] { return uni(rng); });
        bi.generate([&] { return uni(rng); });
    }
    auto Ci = ocp.C(N), Qi = ocp.Q(N);
    Ci.generate([&] { return uni(rng); });
    Qi.generate([&] { return uni(rng); });
    // Make sure Q(N) is SPD
    Qi.add_to_diagonal(2 * static_cast<real_t>(nx));
    for (index_t c = 0; c < nx; ++c)
        for (index_t r = c + 1; r < nx; ++r)
            Qi(c, r) = Qi(r, c);
    auto qi = ocp.q(N), bi = ocp.b(N);
    qi.generate([&] { return uni(rng); });
    bi.generate([&] { return uni(rng); });

    // Compute feasible b_min and b_max
    std::vector<real_t> u_rand_(nu), x_rand_(2 * nx);
    guanaqo::MatrixView<real_t, index_t> u_rand{{.data = u_rand_.data(), .rows = nu, .cols = 1}},
        x_rand{{.data = x_rand_.data(), .rows = nx, .cols = 2}};
    u_rand.generate([&] { return uni(rng); });
    x_rand.left_cols(1) = ocp.b(0); // x0
    for (index_t i = 0; i < N; ++i) {
        auto xi = x_rand.middle_cols(i % 2, 1), xi_next = x_rand.middle_cols((i + 1) % 2, 1);
        auto ui = u_rand;
        for (index_t j = 0; j < ny; ++j) {
            for (index_t k = 0; k < nx; ++k)
                ocp.b_min(i)(j, 0) += ocp.C(i)(j, k) * xi(k, 0);
            for (index_t k = 0; k < nu; ++k)
                ocp.b_min(i)(j, 0) += ocp.D(i)(j, k) * ui(k, 0);
            ocp.b_max(i)(j, 0) = ocp.b_min(i)(j, 0);
            // Optionally add some slack to the constraints
            if (bernoulli(rng))
                ocp.b_min(i)(j, 0) -= abs(uni(rng));
            if (bernoulli(rng))
                ocp.b_max(i)(j, 0) += abs(uni(rng));
        }
        // Propagate dynamics
        for (index_t j = 0; j < nx; ++j) {
            xi_next(j, 0) = 0;
            for (index_t k = 0; k < nx; ++k)
                xi_next(j, 0) += ocp.A(i)(j, k) * xi(k, 0);
            for (index_t k = 0; k < nu; ++k)
                xi_next(j, 0) += ocp.B(i)(j, k) * ui(k, 0);
        }
    }
    auto xi = x_rand.middle_cols(N % 2, 1);
    for (index_t j = 0; j < ny_N; ++j) {
        for (index_t k = 0; k < nx; ++k)
            ocp.b_min(N)(j, 0) += ocp.C(N)(j, k) * xi(k, 0);
        ocp.b_max(N)(j, 0) = ocp.b_min(N)(j, 0);
        if (bernoulli(rng))
            ocp.b_min(N)(j, 0) -= abs(uni(rng));
        if (bernoulli(rng))
            ocp.b_max(N)(j, 0) += abs(uni(rng));
    }

    return ocp;
}
/// Generates a random linear OCP with the given dimensions and random seed.
/// @ingroup topic-ocp-formulations
inline LinearOCPStorage generate_random_ocp_input_constr(OCPDim dim, uint_fast32_t seed = 0) {
    LinearOCPStorage ocp{.dim = dim};
    auto [N, nx, nu, ny, ny_N] = ocp.dim;

    using std::abs;
    std::mt19937 rng{seed};
    std::uniform_real_distribution<real_t> uni{-1, 1};
    std::bernoulli_distribution bernoulli{0.5};

    // Dynamics and constraint matrices
    for (index_t i = 0; i < N; ++i) {
        auto Ai = ocp.A(i), Bi = ocp.B(i), Ci = ocp.C(i), Di = ocp.D(i);
        auto Qi = ocp.Q(i), Ri = ocp.R(i), Si = ocp.S(i), Hi = ocp.H(i);
        Ai.generate([&] { return uni(rng) * 0.9; });
        Bi.generate([&] { return uni(rng); });
        Ci.generate([&] { return uni(rng) * 0.0; });
        Di.generate([&] { return uni(rng); });
        Qi.generate([&] { return uni(rng); });
        Ri.generate([&] { return uni(rng); });
        Si.generate([&] { return uni(rng); });
        // Make sure H(i) is SPD
        Hi.add_to_diagonal(2 * static_cast<real_t>(nx + nu));
        for (index_t c = 0; c < nx + nu; ++c)
            for (index_t r = c + 1; r < nx + nu; ++r)
                Hi(c, r) = Hi(r, c);
        auto qi = ocp.q(i), ri = ocp.r(i), bi = ocp.b(i);
        qi.generate([&] { return uni(rng); });
        ri.generate([&] { return uni(rng); });
        bi.generate([&] { return uni(rng); });
    }
    auto Ci = ocp.C(N), Qi = ocp.Q(N);
    Ci.generate([&] { return uni(rng); });
    Qi.generate([&] { return uni(rng); });
    // Make sure Q(N) is SPD
    Qi.add_to_diagonal(2 * static_cast<real_t>(nx));
    for (index_t c = 0; c < nx; ++c)
        for (index_t r = c + 1; r < nx; ++r)
            Qi(c, r) = Qi(r, c);
    auto qi = ocp.q(N), bi = ocp.b(N);
    qi.generate([&] { return uni(rng); });
    bi.generate([&] { return uni(rng); });

    // Compute feasible b_min and b_max
    std::vector<real_t> u_rand_(nu), x_rand_(2 * nx);
    guanaqo::MatrixView<real_t, index_t> u_rand{{.data = u_rand_.data(), .rows = nu, .cols = 1}},
        x_rand{{.data = x_rand_.data(), .rows = nx, .cols = 2}};
    u_rand.generate([&] { return uni(rng); });
    x_rand.left_cols(1) = ocp.b(0); // x0
    for (index_t i = 0; i < N; ++i) {
        auto xi = x_rand.middle_cols(i % 2, 1), xi_next = x_rand.middle_cols((i + 1) % 2, 1);
        auto ui = u_rand;
        for (index_t j = 0; j < ny; ++j) {
            for (index_t k = 0; k < nx; ++k)
                ocp.b_min(i)(j, 0) += ocp.C(i)(j, k) * xi(k, 0);
            for (index_t k = 0; k < nu; ++k)
                ocp.b_min(i)(j, 0) += ocp.D(i)(j, k) * ui(k, 0);
            ocp.b_max(i)(j, 0) = ocp.b_min(i)(j, 0);
            // Optionally add some slack to the constraints
            if (bernoulli(rng))
                ocp.b_min(i)(j, 0) -= abs(uni(rng));
            if (bernoulli(rng))
                ocp.b_max(i)(j, 0) += abs(uni(rng));
        }
        // Propagate dynamics
        for (index_t j = 0; j < nx; ++j) {
            xi_next(j, 0) = 0;
            for (index_t k = 0; k < nx; ++k)
                xi_next(j, 0) += ocp.A(i)(j, k) * xi(k, 0);
            for (index_t k = 0; k < nu; ++k)
                xi_next(j, 0) += ocp.B(i)(j, k) * ui(k, 0);
        }
    }
    auto xi = x_rand.middle_cols(N % 2, 1);
    for (index_t j = 0; j < ny_N; ++j) {
        for (index_t k = 0; k < nx; ++k)
            ocp.b_min(N)(j, 0) += ocp.C(N)(j, k) * xi(k, 0);
        ocp.b_max(N)(j, 0) = ocp.b_min(N)(j, 0);
        if (bernoulli(rng))
            ocp.b_min(N)(j, 0) -= abs(uni(rng));
        if (bernoulli(rng))
            ocp.b_max(N)(j, 0) += abs(uni(rng));
    }

    return ocp;
}

} // namespace cyqlone
