#pragma once

#include <cyqlone/config.hpp>
#include <cyqlone/example-problems/export.h>
#include <cyqlone/ocp.hpp>

#include <array>
#include <vector>

namespace cyqlone::qpalm::problems {

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
        2, 2, 10, 0.25, 0.25, 10, 0.2, 0.2, 0.2, 1e-10, 1e-10, 0.3,
    };
    std::array<real_t, 12> force_weights{
        1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6,
        1e-6, 1e-6, 1e-6, 1e-6, 1e-6, 1e-6,
    };
    std::vector<CentroidalQuadrupedGaitPhase> gait{
        {8, {true, false, false, true}},
        {8, {false, true, true, false}},
        {8, {true, false, false, true}},
        {8, {false, true, true, false}},
    };

};

struct CentroidalQuadrupedProblem {
    LinearOCPStorage ocp;
    std::vector<real_t> reference;
};

struct FanCentroidalQuadrupedProblem {
    FanOCPStorage ocp;
    std::vector<real_t> friction_coefficients;
};

} // namespace cyqlone::qpalm::problems

namespace CYQLONE_NS(cyqlone::qpalm::problems) {

CentroidalQuadrupedProblem CYQLONE_EXAMPLE_PROBLEMS_EXPORT
centroidal_quadruped(CentroidalQuadrupedParams p = {});

FanCentroidalQuadrupedProblem CYQLONE_EXAMPLE_PROBLEMS_EXPORT
fan_centroidal_quadruped(CentroidalQuadrupedParams p, index_t num_branches,
                         real_t mu_radius = 0.2);

} // namespace CYQLONE_NS(cyqlone::qpalm::problems)
