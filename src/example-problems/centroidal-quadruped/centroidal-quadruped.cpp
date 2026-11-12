/*
 * This file contains code derived from:
 * https://gitlab.laas.fr/paleziart/quadruped-qp-problems
 *
 * Copyright 2023 Pierre-Alexandre Leziart
 *
 * Original code licensed under the Apache License, Version 2.0.
 * C++ modifications:
 */
#include <fancyqlone/conversion.hpp>
#include <fancyqlone/fancyqpalm/example-problems/centroidal-quadruped.hpp>
#include <guanaqo/eigen/view.hpp>

#include <Eigen/Core>
#include <Eigen/LU>

#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace CYQLONE_NS(cyqlone::qpalm::problems) {
namespace {

constexpr index_t nx = 12;
constexpr index_t nu = 12;
constexpr index_t ny = 28;

using Vector3 = Eigen::Matrix<real_t, 3, 1>;
using Matrix3 = Eigen::Matrix<real_t, 3, 3>;

Vector3 reference_position(const CentroidalQuadrupedParams &p, real_t time) {
    const auto [vx, vy, yaw_rate] = p.v_ref;
    Vector3 position{0, 0, p.base_height};
    if (yaw_rate != 0) {
        const auto c = std::cos(yaw_rate * time);
        const auto s = std::sin(yaw_rate * time);
        position(0)  = (vx * s + vy * (c - 1)) / yaw_rate;
        position(1)  = (vy * s - vx * (c - 1)) / yaw_rate;
    } else {
        position(0) = vx * time;
        position(1) = vy * time;
    }
    return position;
}

void set_reference_state(const CentroidalQuadrupedParams &p, real_t time, real_t *state) {
    const auto [vx, vy, yaw_rate] = p.v_ref;
    const auto position           = reference_position(p, time);
    state[0]                      = position(0);
    state[1]                      = position(1);
    state[2]                      = position(2);
    state[5]                      = yaw_rate * time;
    state[11]                     = yaw_rate;
    if (yaw_rate != 0) {
        const auto c = std::cos(yaw_rate * time);
        const auto s = std::sin(yaw_rate * time);
        state[6]     = vx * c + vy * s;
        state[7]     = vy * c - vx * s;
    } else {
        state[6] = vx;
        state[7] = vy;
    }
}

Matrix3 skew(const Vector3 &v) {
    Matrix3 result;
    result << 0, -v(2), v(1), v(2), 0, -v(0), -v(1), v(0), 0;
    return result;
}

std::vector<std::array<bool, 4>> expand_gait(const CentroidalQuadrupedParams &p) {
    std::vector<std::array<bool, 4>> contacts;
    contacts.reserve(static_cast<size_t>(p.N_horiz));
    index_t cycle_duration = 0;
    for (const auto &phase : p.gait) {
        if (phase.duration <= 0)
            throw std::invalid_argument("Gait phase durations must be positive");
        if (phase.duration > std::numeric_limits<index_t>::max() - cycle_duration)
            throw std::invalid_argument("Gait cycle duration is too large");
        cycle_duration += phase.duration;
    }
    auto offset = p.initial_stage % cycle_duration;
    while (static_cast<index_t>(contacts.size()) < p.N_horiz) {
        for (const auto &phase : p.gait) {
            if (offset >= phase.duration) {
                offset -= phase.duration;
                continue;
            }
            for (index_t i = offset;
                 i < phase.duration && static_cast<index_t>(contacts.size()) < p.N_horiz; ++i)
                contacts.push_back(phase.contacts);
            offset = 0;
        }
    }
    return contacts;
}

void validate(const CentroidalQuadrupedParams &p) {
    if (p.gait.empty())
        throw std::invalid_argument("The gait must contain at least one phase");
    if (p.N_horiz <= 0)
        throw std::invalid_argument("The prediction horizon must be positive");
    if (p.initial_stage < 0)
        throw std::invalid_argument("The initial prediction stage must be nonnegative");
    if (p.dt <= 0)
        throw std::invalid_argument("The time step must be positive");
    if (p.mass <= 0)
        throw std::invalid_argument("The robot mass must be positive");
    if (p.mu < 0)
        throw std::invalid_argument("The friction coefficient must be nonnegative");
    if (p.f_max < 0)
        throw std::invalid_argument("The maximum contact force must be nonnegative");
}

} // namespace

CentroidalQuadrupedProblem centroidal_quadruped(CentroidalQuadrupedParams p) {
    using guanaqo::as_view;
    validate(p);
    const auto contacts = expand_gait(p);
    const auto N        = static_cast<index_t>(contacts.size());
    const auto inf      = std::numeric_limits<real_t>::infinity();

    LinearOCPStorage ocp{.dim{
        .N_horiz = N,
        .nx      = nx,
        .nu      = nu,
        .ny      = ny,
        .ny_N    = 0,
    }};
    ocp.b().set_constant(0);
    ocp.b(0)(2, 0) = p.base_height;
    ocp.b_min().set_constant(-inf);
    ocp.b_max().set_constant(+inf);

    std::vector<real_t> reference(static_cast<size_t>(N * (nx + nu) + nx));
    for (index_t i = 0; i <= N; ++i) {
        auto offset = static_cast<size_t>(i * (nx + nu));
        const auto time = (static_cast<real_t>(p.initial_stage) + static_cast<real_t>(i)) * p.dt;
        set_reference_state(p, time, reference.data() + offset);
    }

    Matrix3 inertia;
    inertia << p.inertia[0], p.inertia[1], p.inertia[2], p.inertia[3], p.inertia[4],
        p.inertia[5], p.inertia[6], p.inertia[7], p.inertia[8];
    const std::array<Vector3, 4> footholds{
        Vector3{+p.foot_x, +p.foot_y, 0},
        Vector3{+p.foot_x, -p.foot_y, 0},
        Vector3{-p.foot_x, +p.foot_y, 0},
        Vector3{-p.foot_x, -p.foot_y, 0},
    };

    for (index_t i = 0; i < N; ++i) {
        auto Ai = ocp.A(i), Bi = ocp.B(i), Di = ocp.D(i);
        auto Qi = ocp.Q(i), Ri = ocp.R(i);
        auto lbi = ocp.b_min(i), ubi = ocp.b_max(i);

        Ai.set_constant(0);
        Ai.set_diagonal(1);
        for (index_t j = 0; j < 6; ++j)
            Ai(j, j + 6) = p.dt;

        for (index_t foot = 0; foot < 4; ++foot)
            for (index_t axis = 0; axis < 3; ++axis)
                Bi(6 + axis, 3 * foot + axis) = p.dt / p.mass;

        const auto ref_offset = static_cast<size_t>((i + 1) * (nx + nu));
        const auto yaw        = reference[ref_offset + 5];
        const auto c          = std::cos(yaw);
        const auto s          = std::sin(yaw);
        Matrix3 rotation;
        rotation << c, -s, 0, s, c, 0, 0, 0, 1;
        const Matrix3 inertia_inv = (rotation.transpose() * inertia * rotation).inverse();
        const Vector3 base_position{reference[ref_offset], reference[ref_offset + 1],
                                    reference[ref_offset + 2]};
        for (index_t foot = 0; foot < 4; ++foot) {
            const Matrix3 angular = inertia_inv * skew(footholds[foot] - base_position) * p.dt;
            Bi.block(9, 3 * foot, 3, 3) = as_view(angular);
        }
        ocp.b(i + 1)(8, 0) = -p.gravity * p.dt;

        if (i > 0)
            for (index_t j = 0; j < nx; ++j)
                Qi(j, j) = p.state_weights[j];
        for (index_t j = 0; j < nu; ++j)
            Ri(j, j) = p.force_weights[j];

        for (index_t foot = 0; foot < 4; ++foot) {
            const auto row = 4 * foot;
            const auto col = 3 * foot;
            Di(row + 0, col + 0) = +1;
            Di(row + 1, col + 0) = -1;
            Di(row + 2, col + 1) = +1;
            Di(row + 3, col + 1) = -1;
            for (index_t j = 0; j < 4; ++j) {
                Di(row + j, col + 2) = -p.mu;
                ubi(row + j, 0)      = 0;
            }
            for (index_t axis = 0; axis < 3; ++axis) {
                const auto force_row = 16 + col + axis;
                Di(force_row, col + axis) = 1;
                if (!contacts[i][foot]) {
                    lbi(force_row, 0) = 0;
                    ubi(force_row, 0) = 0;
                } else if (axis == 2) {
                    lbi(force_row, 0) = 0;
                    ubi(force_row, 0) = p.f_max;
                }
            }
        }
    }

    auto QN = ocp.Q(N);
    for (index_t j = 0; j < nx; ++j)
        QN(j, j) = p.state_weights[j];
    reference_to_gradient(ocp, reference);

    return {.ocp = std::move(ocp), .reference = std::move(reference)};
}

FanCentroidalQuadrupedProblem fan_centroidal_quadruped(CentroidalQuadrupedParams p,
                                                       index_t num_branches,
                                                       real_t mu_radius) {
    if (num_branches <= 0)
        throw std::invalid_argument("The number of branches must be positive");
    if (mu_radius < 0 || p.mu - mu_radius < 0)
        throw std::invalid_argument("The friction uncertainty interval must be nonnegative");

    std::vector<LinearOCPStorage> ocps;
    std::vector<real_t> friction_coefficients;
    const auto nominal_mu = p.mu;
    ocps.reserve(static_cast<size_t>(num_branches));
    friction_coefficients.reserve(static_cast<size_t>(num_branches));
    for (index_t branch = 0; branch < num_branches; ++branch) {
        if (num_branches > 1)
            p.mu = nominal_mu - mu_radius + 2 * mu_radius * static_cast<real_t>(branch) /
                                                 static_cast<real_t>(num_branches - 1);
        friction_coefficients.push_back(p.mu);
        ocps.push_back(std::move(centroidal_quadruped(p).ocp));
    }
    return {
        .ocp                   = FanOCPStorage{.ocps = std::move(ocps)},
        .friction_coefficients = std::move(friction_coefficients),
    };
}

} // namespace CYQLONE_NS(cyqlone::qpalm::problems)
