/*
 * This file contains code derived from:
 * https://gitlab.laas.fr/paleziart/quadruped-qp-problems
 *
 * Copyright 2023 Pierre-Alexandre Leziart
 *
 * Original code licensed under the Apache License, Version 2.0.
 *
 * C++ modifications:
 * Copyright 2026 Matisse Teuwen
 *
 * This modified work is distributed as part of fancyqlone
 * under the GNU Lesser General Public License, version 3.
 */
#pragma once

#include <fancyqlone/config.hpp>
#include <fancyqlone/example-problems/export.h>
#include <fancyqlone/ocp.hpp>

#include <array>
#include <vector>
#include <stdexcept>

namespace fancyqlone::qpalm::problems {

struct CentroidalQuadrupedGaitPhase {
    index_t duration;
    std::array<bool, 4> contacts;
};

struct CentroidalQuadrupedParams {
    real_t dt      = 0.02;
    real_t mu      = 0.5;
    real_t mass    = 2.5;
    real_t f_max   = 30;
    real_t gravity = 9.81;
    index_t N_horiz = 32;

    index_t initial_stage = 0;

    real_t base_height = 0.235;
    real_t foot_x      = 0.19;
    real_t foot_y      = 0.15;

    std::array<real_t, 3> v_ref{0.1, 0, 0};

    std::array<real_t, 9> inertia{
        3.06065356e-02, -7.44810900e-07, 9.33810799e-06,
        -7.44810900e-07, 5.12750881e-02, -4.33680869e-19,
        9.33810799e-06, -4.33680869e-19, 6.88650704e-02,
    };

    std::array<real_t, 12> state_weights{
        2, 2, 10, 0.25, 0.25, 10,
        0.2, 0.2, 0.2, 0, 0, 0.3,
    };

    std::array<real_t, 12> force_weights{
        5e-5, 5e-5, 5e-5, 5e-5, 5e-5, 5e-5,
        5e-5, 5e-5, 5e-5, 5e-5, 5e-5, 5e-5,
    };

    std::vector<CentroidalQuadrupedGaitPhase> gait;

    uint64_t seed = 0;

    CentroidalQuadrupedParams()
        : gait(make_gait(N_horiz)) {}

    CentroidalQuadrupedParams(index_t N, uint64_t seed, real_t Ts, real_t force_weight = 5e-5, real_t reg = 0)
        : dt(Ts),
          N_horiz(N),
          gait(make_gait(N)),
          seed(seed) {force_weights.fill(force_weight);
          for (auto& w : state_weights)
            w += reg;}

private:
    static std::vector<CentroidalQuadrupedGaitPhase>
    make_gait(index_t N)
    {
        if (N % 4 != 0) {
            throw std::invalid_argument(
                "CentroidalQuadrupedParams: N_horiz must be a multiple of 4"
            );
        }

        const index_t phase_length = N / 4;

        return {
            {phase_length, {true,  false, false, true }},
            {phase_length, {false, true,  true,  false}},
            {phase_length, {true,  false, false, true }},
            {phase_length, {false, true,  true,  false}},
        };
    }
};

struct CentroidalQuadrupedProblem {
    LinearOCPStorage ocp;
    std::vector<real_t> reference;
};

struct FanCentroidalQuadrupedProblem {
    FanOCPStorage ocp;
    std::vector<real_t> friction_coefficients;
};

} // namespace fancyqlone::qpalm::problems

namespace FANCYQLONE_NS(fancyqlone::qpalm::problems) {

CentroidalQuadrupedProblem CYQLONE_EXAMPLE_PROBLEMS_EXPORT
centroidal_quadruped(CentroidalQuadrupedParams p = {});

FanCentroidalQuadrupedProblem CYQLONE_EXAMPLE_PROBLEMS_EXPORT
fan_centroidal_quadruped(CentroidalQuadrupedParams p, index_t num_branches,
                         real_t mu_radius = 0.2);

} // namespace FANCYQLONE_NS(fancyqlone::qpalm::problems)
