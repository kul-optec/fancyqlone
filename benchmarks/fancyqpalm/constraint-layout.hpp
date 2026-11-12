#pragma once

#include <fancyqlone/ocp.hpp>

#include <limits>
#include <span>
#include <vector>

namespace fanqp {

struct ConstraintRow {
    enum class Kind { General, State, Input, Inactive };
    Kind kind = Kind::Inactive;
    int index = -1;
    double dual_scale = 1;
};

struct StageConstraints {
    // Native bounds use state/input indices, independently of solver ordering.
    std::vector<double> xmin, xmax, umin, umax;
    std::vector<int> state_indices, input_indices;
    // Remaining general constraints, in column-major order.
    std::vector<double> C, D, lower, upper;
    // Original rows, stacked by branch at the shared root.
    std::vector<ConstraintRow> rows;
    std::vector<int> row_offsets;
};

inline int constraint_node(int branches, int branch, int stage) {
    return stage == 0 ? 0 : 1 + (stage - 1) * branches + branch;
}

/// Recognize exact +1 selectors. Identical bounds share a native bound; differing
/// duplicates remain general rows. No scaling or bound-intersection machinery.
/// Disabling boxes retains every original row (also used by existing warm starts).
inline StageConstraints analyze_constraints(
    std::span<const fancyqlone::LinearOCPStorage> sources, int stage,
    bool boxes = true, bool state_boxes = true) {
    const int nx = static_cast<int>(sources.front().dim.nx);
    const int nu = stage < sources.front().dim.N_horiz
                       ? static_cast<int>(sources.front().dim.nu) : 0;
    constexpr double inf = std::numeric_limits<double>::infinity();
    StageConstraints result;
    result.xmin.assign(nx, -inf);
    result.xmax.assign(nx, inf);
    result.umin.assign(nu, -inf);
    result.umax.assign(nu, inf);
    std::vector<int> x_count(nx), u_count(nu);
    struct GeneralRow { int branch, row; };
    std::vector<GeneralRow> general;

    using Kind = ConstraintRow::Kind;
    for (int branch = 0; branch < static_cast<int>(sources.size()); ++branch) {
        const auto &ocp = sources[branch];
        const auto C = ocp.C(stage);
        result.row_offsets.push_back(static_cast<int>(result.rows.size()));
        for (int row = 0; row < C.rows; ++row) {
            const double lower = ocp.b_min(stage)(row, 0);
            const double upper = ocp.b_max(stage)(row, 0);
            ConstraintRow mapping;
            if (boxes && lower == -inf && upper == inf) {
                result.rows.push_back(mapping);
                continue;
            }
            int nonzeros = 0;
            bool selector = boxes;
            auto inspect = [&](double coefficient, Kind kind, int index) {
                if (coefficient == 0)
                    return;
                ++nonzeros;
                selector = selector && coefficient == 1;
                mapping.kind = kind;
                mapping.index = index;
            };
            if (boxes) {
                for (int col = 0; col < nx; ++col)
                    inspect(C(row, col), Kind::State, col);
                if (nu > 0)
                    for (int col = 0; col < nu; ++col)
                        inspect(ocp.D(stage)(row, col), Kind::Input, col);
            }
            selector = selector && nonzeros == 1 &&
                       (state_boxes || mapping.kind != Kind::State);
            if (selector) {
                const bool state = mapping.kind == Kind::State;
                auto &counts = state ? x_count : u_count;
                auto &lb = state ? result.xmin : result.umin;
                auto &ub = state ? result.xmax : result.umax;
                const int i = mapping.index;
                if (counts[i] == 0 || (lb[i] == lower && ub[i] == upper)) {
                    lb[i] = lower;
                    ub[i] = upper;
                    ++counts[i];
                    result.rows.push_back(mapping);
                    continue;
                }
            }
            mapping = {Kind::General, static_cast<int>(general.size()), 1};
            // The general-only layout retains these rows for existing HPIPM
            // warm starts, but an unconstrained row always has a zero multiplier.
            if (lower == -inf && upper == inf)
                mapping.kind = Kind::Inactive;
            general.push_back({branch, row});
            result.lower.push_back(lower);
            result.upper.push_back(upper);
            result.rows.push_back(mapping);
        }
    }
    result.row_offsets.push_back(static_cast<int>(result.rows.size()));
    for (int i = 0; i < nx; ++i)
        if (x_count[i])
            result.state_indices.push_back(i);
    for (int i = 0; i < nu; ++i)
        if (u_count[i])
            result.input_indices.push_back(i);
    for (auto &row : result.rows) {
        if (row.kind == Kind::State)
            row.dual_scale = 1.0 / x_count[row.index];
        else if (row.kind == Kind::Input)
            row.dual_scale = 1.0 / u_count[row.index];
    }
    const auto ng = general.size();
    result.C.resize(ng * nx);
    result.D.resize(ng * nu);
    for (std::size_t i = 0; i < ng; ++i) {
        const auto [branch, row] = general[i];
        const auto &ocp = sources[branch];
        for (int col = 0; col < nx; ++col)
            result.C[i + col * ng] = ocp.C(stage)(row, col);
        for (int col = 0; col < nu; ++col)
            result.D[i + col * ng] = ocp.D(stage)(row, col);
    }
    return result;
}

inline double constraint_multiplier(const ConstraintRow &row,
                                    std::span<const double> x,
                                    std::span<const double> u,
                                    std::span<const double> general) {
    using Kind = ConstraintRow::Kind;
    switch (row.kind) {
        case Kind::State: return row.dual_scale * x[row.index];
        case Kind::Input: return row.dual_scale * u[row.index];
        case Kind::General: return general[row.index];
        case Kind::Inactive: return 0;
    }
    return 0;
}

} // namespace fanqp
