#pragma once

#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.tpp>
#include "cyqlone/cyqlone.hpp"
#include "cyqlone/qpalm/implementation/breakpoint.hpp"
#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>
#include <span>
#include <type_traits>
#include <utility>
#include <vector>

namespace CYQLONE_NS(cyqlone::qpalm) {

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
template <class T, size_t N>
void CyQPALMBackend<VL, DefaultOrder, LinearSolver>::merge_chunk(
    std::span<const T> chunk, size_t chunk_index, std::span<const std::array<size_t, N>> separators,
    std::span<T> out) {
    GUANAQO_TRACE("merge_chunk", 0, chunk.size());
    size_t num_chunks = separators.size();
    BATMAT_ASSUME(chunk_index < num_chunks);
    std::array<size_t, N> offsets{};
    for (size_t i = 0; i < N; ++i)
        for (size_t c = 0; c < chunk_index; ++c)
            offsets[i] += separators[c][i];
    for (size_t i = 0; i < N - 1; ++i)
        for (size_t c = chunk_index; c < num_chunks; ++c)
            offsets[i + 1] += separators[c][i];
    std::copy(chunk.begin(), chunk.begin() + separators[chunk_index][0], out.begin() + offsets[0]);
    for (size_t i = 1; i < N; ++i)
        std::copy(chunk.begin() + separators[chunk_index][i - 1],
                  chunk.begin() + separators[chunk_index][i], out.begin() + offsets[i]);
}

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
BreakpointsResult CyQPALMBackend<VL, DefaultOrder, LinearSolver>::compute_partition_breakpoints_cyq(
    Context &ctx, std::vector<Breakpoint> &breakpoints, const ineq_constr_vec_t &Σ,
    const ineq_constr_vec_t &y, const ineq_constr_vec_t &Ad, const ineq_constr_vec_t &Ax,
    const ineq_constr_vec_t &b_min, const ineq_constr_vec_t &b_max) {
    auto t = get_timed(&Timings::breakpoints);
    using std::isfinite;
    using std::sqrt;
    // Allocate memory
    const index_t ny_M = std::max(ocp.ny, ocp.ny_0 + ocp.ny_N);
    ctx.run_single_sync([&] {
        const index_t m = ocp.ceil_N() * ny_M;
        breakpoints.resize(2 * m);
        breakpoints_temp.resize(2 * m);
        thread_indices.resize(ocp.p);
    });
    // Parallelization and vectorization
    auto thr_parts            = std::span{thread_indices}.subspan(0, ocp.p);
    const index_t ti          = ocp.riccati_thread_assignment(ctx);
    const index_t bpt_per_thr = 2 * ny_M * ocp.n * ocp.v;
    // Partition the breakpoints into a finite and an infinite part (per thread)
    Breakpoint *const fin_0 = breakpoints_temp.data() + ti * bpt_per_thr;
    Breakpoint *const inf_0 = fin_0 + bpt_per_thr;
    Breakpoint *fin = fin_0, *inf = inf_0;
    // Compute break points t[i] and intermediate values α[i] and δ[i]
    const auto brkpts_simd = [&](auto Σi, auto yi, auto Adi, auto Axi, auto li, auto ui) {
        const auto s  = sqrt(Σi);
        const auto δ2 = s * Adi, δ1 = -δ2;
        const auto α1 = (yi + Σi * (Axi - li)) / s, α2 = (Σi * (ui - Axi) - yi) / s;
        const auto t1 = α1 / δ1, t2 = α2 / δ2;
        BATMAT_FULLY_UNROLLED_FOR (int l = 0; l < ocp.v; ++l) {
            *(isfinite(t1[l]) ? fin++ : --inf) = {.t = t1[l], .δ = δ1[l]};
            *(isfinite(t2[l]) ? fin++ : --inf) = {.t = t2[l], .δ = δ2[l]};
        }
        // Invariant: finite values in [fin_0, fin) and infinite values in [inf, inf_0)
    };
    const auto brkpts_batch = [&](auto Σj, auto yj, auto Adj, auto Axj, auto b_min_j,
                                  auto b_max_j) {
        linalg::for_each_elementwise(brkpts_simd, Σj, yj, Adj, Axj, b_min_j, b_max_j);
    };
    ocp.foreach_batch(ctx, brkpts_batch, Σ, y, Ad, Ax, b_min, b_max);
    // Now partition the finite breakpoints into negative and positive parts.
    // Partitioning the chunk of each thread separately improves partitioning performance
    // later on in the line search because of branch prediction.
    auto [pos, large] = [&] {
        GUANAQO_TRACE("linesearch breakpoints cyqlone partition", ti);
        auto pos   = partition(fin_0, fin, [](Breakpoint p) { return p.t <= 0; }).begin();
        auto large = partition(pos, fin, [](Breakpoint p) { return p.t <= 1; }).begin();
        return std::pair{pos, large};
    }();
    // Store the separator indices for all threads, to merge the partitions in parallel later.
    thr_parts[ti][0]    = pos - fin_0;   // index of first positive breakpoint (per thread)
    thr_parts[ti][1]    = large - fin_0; // index of first breakpoint larger than 1 (per thread)
    thr_parts[ti][2]    = fin - fin_0;   // index of first infinite breakpoint (per thread)
    thr_parts[ti][3]    = inf_0 - fin_0; // total number of breakpoints (per thread)
    auto thr_parts_done = ctx.arrive();  // all-to-all
    // Compute the partial sums
    PartitionedBreakpoints pos_neg_bp{.neg_bp = std::span{fin_0, pos},
                                      .pos_bp = std::span{pos, fin}};
    auto ab_neg = partial_sum_negative(pos_neg_bp);
    // Synchronize the separator indices for all threads.
    ctx.wait(std::move(thr_parts_done));
    // Merge all local partitions of all threads into a single partitioned array.
    GUANAQO_TRACE("linesearch breakpoints cyqlone merge", ti);
    merge_chunk<Breakpoint, 4>(std::span{fin_0, inf_0}, ti, thr_parts, std::span{breakpoints});
    // Compute the total sums across all threads.
    auto ab_neg_and_merge_done = ctx.arrive_reduce(ab_neg, std::plus<>{});
    // Compute the final partition indices by summing the partition sizes of all threads.
    auto first_pos = std::accumulate(thr_parts.begin(), thr_parts.end(), breakpoints.begin(),
                                     [](auto it, auto &i) { return it += i[0]; }),
         first_inf = std::accumulate(thr_parts.begin(), thr_parts.end(), breakpoints.begin(),
                                     [](auto it, auto &i) { return it += i[2]; });
    // Wait for the total sums across all threads. Also synchronize the merged breakpoints.
    ab_neg = ctx.wait_reduce(std::move(ab_neg_and_merge_done));
    return {.bp     = {.neg_bp = std::span{breakpoints.begin(), first_pos},
                       .pos_bp = std::span{first_pos, first_inf}},
            .ab_neg = ab_neg};
}

template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
BreakpointsResult CyQPALMBackend<VL, DefaultOrder, LinearSolver>::compute_partition_breakpoints_fan(
    Context &ctx, std::vector<Breakpoint> &breakpoints, const ineq_constr_vec_t &Σ,
    const ineq_constr_vec_t &y, const ineq_constr_vec_t &Ad, const ineq_constr_vec_t &Ax,
    const ineq_constr_vec_t &b_min, const ineq_constr_vec_t &b_max) {
    auto t = get_timed(&Timings::breakpoints);
    using std::isfinite;
    using std::sqrt;
    // Allocate memory
    const index_t c     = ctx.total_ctx.index;
    const index_t p_tot = std::accumulate(ocp.p.begin(), ocp.p.end(), 0);

    const index_t ny_M_c = std::max(ocp.solver_storages[c].cyqlone_solver.ny,
                                    ocp.solver_storages[c].cyqlone_solver.ny_N);
    ctx.run_single_sync([&] {
        const index_t m = ocp.num_internal_constraints();
        breakpoints.resize(2 * m);
        breakpoints_temp.resize(2 * m);
        thread_indices.resize(p_tot + 1);
    });
    // Parallelization and vectorization
    auto thr_parts = std::span{thread_indices}.subspan(0, p_tot + 1);
    const index_t ti =
        ocp.solver_storages[c].cyqlone_solver.riccati_thread_assignment(ctx.branch_ctx);
    const index_t bpt_branch = 2 * ny_M_c * ocp.solver_storages[c].cyqlone_solver.n * ocp.v;
    index_t bpt_offset       = 0;
    index_t t_offset         = 0;
    for (index_t i = 0; i < c; ++i) {
        bpt_offset +=
            2 * ny_M_c *
            ocp.solver_storages[i]
                .cyqlone_solver
                .ceil_N(); // offset of the current thread's breakpoints in breakpoints_temp
        t_offset += ocp.solver_storages[i].cyqlone_solver.p;
    }
    // Partition the breakpoints into a finite and an infinite part (per thread)
    Breakpoint *const fin_0 = breakpoints_temp.data() + bpt_offset + ti * bpt_branch;
    Breakpoint *const inf_0 = fin_0 + bpt_branch;
    Breakpoint *fin = fin_0, *inf = inf_0;
    // Compute break points t[i] and intermediate values α[i] and δ[i]
    const auto brkpts_simd = [&](auto Σi, auto yi, auto Adi, auto Axi, auto li, auto ui) {
        const auto s  = sqrt(Σi);
        const auto δ2 = s * Adi, δ1 = -δ2;
        const auto α1 = (yi + Σi * (Axi - li)) / s, α2 = (Σi * (ui - Axi) - yi) / s;
        const auto t1 = α1 / δ1, t2 = α2 / δ2;
        BATMAT_FULLY_UNROLLED_FOR (int l = 0; l < ocp.v; ++l) {
            *(isfinite(t1[l]) ? fin++ : --inf) = {.t = t1[l], .δ = δ1[l]};
            *(isfinite(t2[l]) ? fin++ : --inf) = {.t = t2[l], .δ = δ2[l]};
        }
        // Invariant: finite values in [fin_0, fin) and infinite values in [inf, inf_0)
    };
    const auto brkpts_batch = [&](auto Σj, auto yj, auto Adj, auto Axj, auto b_min_j,
                                  auto b_max_j) {
        linalg::for_each_elementwise(brkpts_simd, Σj, yj, Adj, Axj, b_min_j, b_max_j);
    };
    ocp.foreach_batch(ctx, brkpts_batch, Σ, y, Ad, Ax, b_min, b_max);
    // Now partition the finite breakpoints into negative and positive parts.
    // Partitioning the chunk of each thread separately improves partitioning performance
    // later on in the line search because of branch prediction.
    auto [pos, large] = [&] {
        GUANAQO_TRACE("linesearch breakpoints cyqlone partition", ti);
        auto pos   = partition(fin_0, fin, [](Breakpoint p) { return p.t <= 0; }).begin();
        auto large = partition(pos, fin, [](Breakpoint p) { return p.t <= 1; }).begin();
        return std::pair{pos, large};
    }();
    // Store the separator indices for all threads, to merge the partitions in parallel later.
    thr_parts[t_offset + ti][0] = pos - fin_0; // index of first positive breakpoint (per thread)
    thr_parts[t_offset + ti][1] =
        large - fin_0; // index of first breakpoint larger than 1 (per thread)
    thr_parts[t_offset + ti][2] = fin - fin_0;   // index of first infinite breakpoint (per thread)
    thr_parts[t_offset + ti][3] = inf_0 - fin_0; // total number of breakpoints (per thread)
    auto thr_parts_done         = ctx.arrive();  // all-to-all
    // Compute the partial sums
    PartitionedBreakpoints pos_neg_bp{.neg_bp = std::span{fin_0, pos},
                                      .pos_bp = std::span{pos, fin}};
    auto ab_neg = partial_sum_negative(pos_neg_bp);
    // Synchronize the separator indices for all threads.
    ctx.wait(std::move(thr_parts_done));
    ABSums ab_neg_0{};
    ctx.run_single_sync([&] {
        // calculate breakpoints for stage 0
        const index_t m = ocp.num_internal_constraints();

        Breakpoint *const fin_0 = breakpoints_temp.data() + m * 2 - 2 * ocp.ny_0;
        Breakpoint *const inf_0 = fin_0 + 2 * ocp.ny_0;
        Breakpoint *fin = fin_0, *inf = inf_0;
        // Compute break points t[i] and intermediate values α[i] and δ[i]
        const auto brkpts_simd = [&](auto Σi, auto yi, auto Adi, auto Axi, auto li, auto ui) {
            const auto s  = sqrt(Σi);
            const auto δ2 = s * Adi, δ1 = -δ2;
            const auto α1 = (yi + Σi * (Axi - li)) / s, α2 = (Σi * (ui - Axi) - yi) / s;
            const auto t1 = α1 / δ1, t2 = α2 / δ2;
            BATMAT_FULLY_UNROLLED_FOR (int l = 0; l < ocp.v; ++l) {
                *(isfinite(t1[l]) ? fin++ : --inf) = {.t = t1[l], .δ = δ1[l]};
                *(isfinite(t2[l]) ? fin++ : --inf) = {.t = t2[l], .δ = δ2[l]};
            }
            // Invariant: finite values in [fin_0, fin) and infinite values in [inf, inf_0)
        };
        const auto brkpts_batch = [&](auto Σj, auto yj, auto Adj, auto Axj, auto b_min_j,
                                      auto b_max_j) {
            linalg::for_each_elementwise(brkpts_simd, Σj, yj, Adj, Axj, b_min_j, b_max_j);
        };
        brkpts_batch(Σ.first.batch(0), y.first.batch(0), Ad.first.batch(0), Ax.first.batch(0),
                     b_min.first.batch(0), b_max.first.batch(0));
        // partition the breakpoints into a finite and an infinite part (per thread)
        auto [pos_0, large_0] = [&] {
            GUANAQO_TRACE("linesearch breakpoints cyqlone partition", ti);
            auto pos   = partition(fin_0, fin, [](Breakpoint p) { return p.t <= 0; }).begin();
            auto large = partition(pos, fin, [](Breakpoint p) { return p.t <= 1; }).begin();
            return std::pair{pos, large};
        }();
        thr_parts[p_tot][0] = pos - fin_0;   // index of first positive breakpoint (per thread)
        thr_parts[p_tot][1] = large - fin_0; // index of first breakpoint larger than 1 (per thread)
        thr_parts[p_tot][2] = fin - fin_0;   // index of first infinite breakpoint (per thread)
        thr_parts[p_tot][3] = inf_0 - fin_0; // total number of breakpoints (per thread)
        ab_neg_0            = partial_sum_negative(
            {.neg_bp = std::span{fin_0, pos_0}, .pos_bp = std::span{pos_0, large_0}});
        merge_chunk<Breakpoint, 4>(std::span{fin_0, inf_0}, p_tot, thr_parts,
                                   std::span{breakpoints});
    });
    // Merge all local partitions of all threads into a single partitioned array.
    GUANAQO_TRACE("linesearch breakpoints cyqlone merge", ti);
    merge_chunk<Breakpoint, 4>(std::span{fin_0, inf_0}, t_offset + ti, thr_parts,
                               std::span{breakpoints});
    // Compute the total sums across all threads.
    auto ab_neg_and_merge_done = ctx.arrive_reduce(ab_neg, std::plus<>{});
    // Compute the final partition indices by summing the partition sizes of all threads.
    auto first_pos = std::accumulate(thr_parts.begin(), thr_parts.end(), breakpoints.begin(),
                                     [](auto it, auto &i) { return it += i[0]; }),
         first_inf = std::accumulate(thr_parts.begin(), thr_parts.end(), breakpoints.begin(),
                                     [](auto it, auto &i) { return it += i[2]; });
    // Wait for the total sums across all threads. Also synchronize the merged breakpoints.
    ab_neg = ctx.wait_reduce(std::move(ab_neg_and_merge_done));
    ab_neg = ctx.call_broadcast([&] { return ab_neg + ab_neg_0; });
    return {.bp     = {.neg_bp = std::span{breakpoints.begin(), first_pos},
                       .pos_bp = std::span{first_pos, first_inf}},
            .ab_neg = ab_neg};
}
/// @todo better way of differentiating functions
template <index_t VL, StorageOrder DefaultOrder, class LinearSolver>
BreakpointsResult CyQPALMBackend<VL, DefaultOrder, LinearSolver>::compute_partition_breakpoints(
    Context &ctx, std::vector<Breakpoint> &breakpoints, const ineq_constr_vec_t &Σ,
    const ineq_constr_vec_t &y, const ineq_constr_vec_t &Ad, const ineq_constr_vec_t &Ax,
    const ineq_constr_vec_t &b_min, const ineq_constr_vec_t &b_max) {
    std::cout << "compute_partition_breakpoints: " << typeid(LinearSolver).name() << std::endl;
    if constexpr (std::is_same_v<LinearSolver,
                                 CyqloneSolver<VL, real_t, DefaultOrder,
                                               parallel::Context<parallel::SharedContext>>>)
        return compute_partition_breakpoints_cyq(ctx, breakpoints, Σ, y, Ad, Ax, b_min, b_max);
    else
        return compute_partition_breakpoints_fan(ctx, breakpoints, Σ, y, Ad, Ax, b_min, b_max);
}
} // namespace CYQLONE_NS(cyqlone::qpalm)
