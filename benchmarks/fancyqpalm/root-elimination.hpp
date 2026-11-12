#pragma once

#include "constraint-layout.hpp"

#include <stdexcept>
#include <utility>

namespace fanqp {

inline std::vector<double> initial_state(const fancyqlone::FanOCPStorage &fan) {
    const auto reference = fan.ocps.front().b(0);
    std::vector<double> x0(reference.data, reference.data + reference.rows);
    for (const auto &ocp : fan.ocps)
        for (int i = 0; i < reference.rows; ++i)
            if (ocp.b(0)(i, 0) != x0[i])
                throw std::invalid_argument("All fan branches must share the same initial state");
    return x0;
}

struct ReducedRoot {
    StageConstraints constraints;
    std::vector<double> r;
    std::vector<std::vector<double>> b;
    double objective_offset = 0;
};

/// Substitute fixed x0, preserving the original constraint-row mapping.
/// The retained rows depend only on D0, so subsequent x0 updates preserve shape.
inline ReducedRoot eliminate_root_state(const fancyqlone::FanOCPStorage &fan,
                                        std::span<const double> x0, bool native_bounds) {
    const int nx = static_cast<int>(fan.ocps.front().dim.nx);
    const int nu = static_cast<int>(fan.ocps.front().dim.nu);
    if (x0.size() != static_cast<std::size_t>(nx))
        throw std::invalid_argument("Initial-state dimension mismatch");

    ReducedRoot result;
    // Extract input bounds, keeping state-containing rows general until substitution.
    result.constraints = analyze_constraints(fan.ocps, 0, native_bounds, false);
    auto &constraints  = result.constraints;
    const int ng       = static_cast<int>(constraints.lower.size());
    std::vector<int> kept, remap(ng, -1);
    std::vector<double> lower, upper;
    for (int row = 0; row < ng; ++row) {
        double shift = 0;
        for (int col = 0; col < nx; ++col)
            shift += constraints.C[row + col * ng] * x0[col];
        bool has_input = false;
        for (int col = 0; col < nu; ++col)
            has_input = has_input || constraints.D[row + col * ng] != 0;
        if (!has_input) {
            if (!(constraints.lower[row] <= shift && shift <= constraints.upper[row]))
                throw std::invalid_argument("Initial state violates a root constraint");
            continue;
        }
        remap[row] = static_cast<int>(kept.size());
        kept.push_back(row);
        lower.push_back(constraints.lower[row] - shift);
        upper.push_back(constraints.upper[row] - shift);
    }
    for (auto &row : constraints.rows) {
        if (row.kind != ConstraintRow::Kind::General)
            continue;
        row.index = remap[row.index];
        if (row.index < 0)
            row.kind = ConstraintRow::Kind::Inactive;
    }
    std::vector<double> D(kept.size() * nu);
    for (int col = 0; col < nu; ++col)
        for (std::size_t row = 0; row < kept.size(); ++row)
            D[row + col * kept.size()] = constraints.D[kept[row] + col * ng];
    constraints.C.clear();
    constraints.xmin.clear();
    constraints.xmax.clear();
    constraints.D     = std::move(D);
    constraints.lower = std::move(lower);
    constraints.upper = std::move(upper);

    result.r.assign(nu, 0);
    for (const auto &ocp : fan.ocps) {
        for (int i = 0; i < nu; ++i) {
            result.r[i] += ocp.r(0)(i, 0);
            for (int j = 0; j < nx; ++j)
                result.r[i] += ocp.S(0)(i, j) * x0[j];
        }
        auto &b = result.b.emplace_back(nx);
        for (int i = 0; i < nx; ++i) {
            b[i] = ocp.b(1)(i, 0);
            for (int j = 0; j < nx; ++j)
                b[i] += ocp.A(0)(i, j) * x0[j];
            result.objective_offset +=
                ocp.q(0)(i, 0) * x0[i] + 0.5 * ocp.Q(0)(i, i) * x0[i] * x0[i];
            for (int j = 0; j < i; ++j)
                result.objective_offset += ocp.Q(0)(i, j) * x0[i] * x0[j];
        }
    }
    return result;
}

} // namespace fanqp
