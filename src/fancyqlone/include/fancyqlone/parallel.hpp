#pragma once

/// @file
/// Parallel execution context and synchronization primitives.
/// @ingroup topic-parallelization

#include <fancyqlone/barrier.hpp>
#include <fancyqlone/config.hpp>
#include <batmat/config.hpp>
#include <syncstream>
#if BATMAT_WITH_OPENMP
#include <batmat/openmp.h>
#else
#include <batmat/thread-pool.hpp>
#endif
#include <guanaqo/trace.hpp>
#include <cstdint>
#include <functional>
#include <iostream>
#include <type_traits>
#include <utility>

namespace fancyqlone::parallel {

struct SharedContext;
struct FanSharedContext;

template <class SC = SharedContext>
struct Context;
template <class SC = FanSharedContext>
struct FanContext;

/// Abstraction for a parallel execution context: a set of threads that can synchronize and
/// communicate with each other using barriers.
/// @see Context
/// @ingroup topic-parallelization
struct SharedContext {
#if GUANAQO_WITH_TRACING
    struct completion_type {
        void operator()() const noexcept { GUANAQO_TRACE_INSTANT("barrier-complete", 0); }
    };
#else
    using completion_type = EmptyCompletion;
#endif
    using barrier_type = TreeBarrier<completion_type, uint16_t>;
    const index_t num_thr;
    barrier_type barrier{static_cast<uint32_t>(num_thr), {}};
#if !BATMAT_WITH_OPENMP
    batmat::thread_pool thread_pool{static_cast<size_t>(num_thr)};
#endif
    /// Execute the given function in parallel on all threads, blocking until completion.
    /// The function will be called with a @ref Context that contains the thread index, and that can
    /// be used to synchronize and communicate between threads.
    template <class F>
    void run(F &&);

    void update_spin_count(uint32_t spin_count) {
        set_barrier_spin_count(spin_count);
    } // namespace fancyqlone::parallel

    uint32_t set_barrier_spin_count(uint32_t spin_count) {
        static_assert(std::is_same_v<decltype(barrier.spin_count), decltype(spin_count)>);
        return std::exchange(barrier.spin_count, spin_count);
    }
};
/// Abstraction for a parallel execution context: a set of threads that can synchronize and
/// communicate with each other using barriers.
/// @see Context
/// @ingroup topic-parallelization
struct FanSharedContext {
#if GUANAQO_WITH_TRACING
    struct completion_type {
        void operator()() const noexcept { GUANAQO_TRACE_INSTANT("barrier-complete", 0); }
    };
#else
    using completion_type = EmptyCompletion;
#endif
    using barrier_type = TreeBarrier<completion_type, uint16_t>;
    const index_t num_thr;
    std::vector<SharedContext> branch_contexts;

    barrier_type barrier{static_cast<uint32_t>(num_thr), {}};
#if !BATMAT_WITH_OPENMP
    batmat::thread_pool thread_pool{static_cast<size_t>(num_thr)};
#endif
    /// Execute the given function in parallel on all threads, blocking until completion.
    /// The function will be called with a @ref Context that contains the thread index, and that can
    /// be used to synchronize and communicate between threads.
    template <class F>
    void run(F &&);
    void update_spin_count(uint32_t spin_count) {
        set_barrier_spin_count(spin_count);
        for (auto &ctx : branch_contexts) {
            ctx.set_barrier_spin_count(spin_count);
            // std::cout << "branch spin count: " << ctx.barrier.spin_count << std::endl;
        }
    }
    /// Configure the barrier spin count used in parallel synchronization before falling back to a
    /// futex wait.
    uint32_t set_barrier_spin_count(uint32_t spin_count) {
        static_assert(std::is_same_v<decltype(barrier.spin_count), decltype(spin_count)>);
        return std::exchange(barrier.spin_count, spin_count);
    }
};

/// Thread context for parallel execution. Each thread has a unique thread index, and can
/// synchronize and communicate with other threads in the same shared context.
/// @see SharedContext
/// @ingroup topic-parallelization
template <class SC>
struct Context {
    using shared_context_type = SC;
#if GUANAQO_WITH_TRACING && !GUANAQO_WITH_PERFETTO
    struct arrival_token {
        using token_t = typename shared_context_type::barrier_type::arrival_token;
        token_t token;
        guanaqo::TraceLogger::ScopedLog trace;
    };
#else
    using arrival_token = typename shared_context_type::barrier_type::arrival_token;
#endif
    template <class T>
    using arrival_token_typed = shared_context_type::barrier_type::template arrival_token_typed<T>;
    template <class T>
    using shuffle_token = shared_context_type::barrier_type::template shuffle_token<T>;

    shared_context_type &shared;
    const index_t index;

    [[nodiscard]] index_t num_thr() const { return shared.num_thr; }

    friend constexpr bool operator==(const Context &a, const Context &b) {
        return &a.shared == &b.shared && a.index == b.index;
    }

    /// Check if this thread is the master thread (thread index 0).
    /// Useful for determining which thread should perform operations like printing to the console,
    /// which should be done by a single thread and does not require synchronization.
    [[nodiscard]] bool is_master() const { return index == 0; }

    /// Arrive at the barrier and obtain a token that can be used to wait for completion of the
    /// current barrier phase.
    /// @note    Token must be awaited before any other call to arrive.
    [[nodiscard]] arrival_token arrive() {
#if GUANAQO_WITH_TRACING && !GUANAQO_WITH_PERFETTO
        auto trace = guanaqo::get_trace_logger().trace("barrier-arrive", index);
        return {shared.barrier.arrive(static_cast<uint32_t>(index)), std::move(trace)};
#else
        return shared.barrier.arrive(static_cast<uint32_t>(index));
#endif
    }
// #if GUANAQO_WITH_TRACING && !GUANAQO_WITH_PERFETTO
//     /// Arrive at the barrier and obtain a token that can be used to wait for completion of the
//     /// current barrier phase and call a function on completion.
//     /// @note    Token must be awaited before any other call to arrive.
//     template <class C>
//     [[nodiscard]] arrival_token::token_t arrive_with_completion(C func) {

//         return shared.barrier.arrive_with_completion(static_cast<uint32_t>(index), std::move(func));
//     };
// #else
    /// Arrive at the barrier and obtain a token that can be used to wait for completion of the
    /// current barrier phase and call a function on completion.
    /// @note    Token must be awaited before any other call to arrive.
    template <class C>
    [[nodiscard]]  shared_context_type::barrier_type::arrival_token arrive_with_completion(C func) {

        return shared.barrier.arrive_with_completion(static_cast<uint32_t>(index), std::move(func));
    }
// #endif
    /// Await a token returned by @ref arrive(), waiting for the barrier phase to complete.
    void wait(arrival_token &&token) {
#if GUANAQO_WITH_TRACING && !GUANAQO_WITH_PERFETTO
        auto trace = std::move(token.trace);
        shared.barrier.wait(std::move(token.token));
#else
        shared.barrier.wait(std::move(token));
#endif
    }

    /// Arrive at the barrier and wait for the barrier phase to complete. This is a convenience
    /// wrapper around @ref arrive() and @ref wait() for the common case where the thread does not
    /// have other work to do while waiting.
    void arrive_and_wait() {
#if !GUANAQO_WITH_PERFETTO
        GUANAQO_TRACE("barrier-arrive-and-wait", index);
#endif
        shared.barrier.arrive_and_wait(static_cast<uint32_t>(index));
    }
    /// Debug version of @ref arrive_and_wait() that performs a sanity check to ensure that all
    /// threads are arriving at the same line of code. The @p line parameter should be the same
    /// for all threads arriving at the same barrier. It is only verified in debug builds, and is
    /// equivalent to @ref arrive_and_wait() in release builds.
    void arrive_and_wait(int line) {
#if !GUANAQO_WITH_PERFETTO
        GUANAQO_TRACE("barrier-arrive-and-wait", index);
#endif
        shared.barrier.arrive_and_wait(static_cast<uint32_t>(index), line);
    }

    /// Broadcast a value @p x from the thread with index @p src to all threads.
    template <class T>
    T broadcast(T x, index_t src = 0) {
        return shared.barrier.broadcast(static_cast<uint32_t>(index), std::move(x),
                                        static_cast<uint32_t>(src));
    }

    /// Call a function @p f with the given @p args on a single thread and broadcast the return
    /// value to all threads.
    template <class F, class... Args>
    auto call_broadcast(F &&f, Args &&...args) -> std::invoke_result_t<F, Args...> {
        using T = std::invoke_result_t<F, Args...>;
        // TODO: implement with a relaxed atomic that gets reset during the completion handler,
        //       so only the first thread that arrives will execute the function, rather than always
        //       executing on the master thread.
        if (is_master())
            return broadcast(std::invoke(std::forward<F>(f), std::forward<Args>(args)...), 0);
        else
            return broadcast(T{}, 0);
    }

    /// Perform a reduction of @p x across all threads using the given binary function @p func.
    /// Returns a token that can be used to wait for the reduction to complete and obtain the
    /// reduced value.
    template <class T, class F>
    [[nodiscard]] auto arrive_reduce(T x, F func) {
        return shared.barrier.arrive_reduce(static_cast<uint32_t>(index), std::move(x),
                                            std::move(func));
    }
    /// Perform a reduction of @p x across all threads using the given binary function @p func.
    /// Returns a token that can be used to wait for the reduction to complete and obtain the
    /// reduced value.
    template <class T, class F, class CF>
    [[nodiscard]] auto arrive_reduce_with_completion(T x, F func, CF completion) {
        return shared.barrier.arrive_reduce(static_cast<uint32_t>(index), std::move(x),
                                            std::move(func), std::move(completion));
    }

    /// Wait for the reduction initiated by @ref arrive_reduce() to complete and obtain the reduced
    /// value.
    template <class T>
    T wait_reduce(arrival_token_typed<T> &&token) {
        return shared.barrier.wait_reduce(std::move(token));
    }

    /// Perform a reduction of @p x across all threads using the given binary function @p func, and
    /// wait for the result.
    template <class T, class F>
    T reduce(T x, F func) {
        return shared.barrier.reduce(static_cast<uint32_t>(index), std::move(x), std::move(func));
    }

    /// Reduction with `std::plus`, i.e., summation across all threads.
    /// @see reduce(T,F)
    template <class T>
    T reduce(T x) {
        return reduce(std::move(x), std::plus<>{});
    }

    /// Wait for all threads to reach this point, then run the given function on a single thread
    /// before releasing all threads again. Changes by all threads are visible during the call to
    /// @p f and changes made by @p f are visible to all threads after this function returns.
    template <class F>
    auto run_single_sync(F &&f) {
        return shared.barrier.arrive_and_wait_with_completion(static_cast<uint32_t>(index),
                                                              std::forward<F>(f));
    }

    template <class T, class F>
    decltype(auto) shuffle_wait(shuffle_token<T> &&token, F &&func) {
        return shared.barrier.shuffle_wait(static_cast<uint32_t>(index), std::move(token),
                                           std::forward<F>(func));
    }

    template <class T>
    decltype(auto) shuffle_wait(shuffle_token<T> &&token) {
        return shared.barrier.shuffle_wait(static_cast<uint32_t>(index), std::move(token));
    }

    template <class T>
    [[nodiscard]] auto shuffle_rotr_start(T x, uint32_t n) {
        return shared.barrier.shuffle_rotr_start(static_cast<uint32_t>(index), std::move(x), n);
    }

    template <class T>
    [[nodiscard]] auto shuffle_rotl_start(T x, uint32_t n) {
        return shared.barrier.shuffle_rotl_start(static_cast<uint32_t>(index), std::move(x), n);
    }
};

template <class T>
struct arrival_token_typed_fan {
    using total_token_t  = typename FanSharedContext::barrier_type::template arrival_token_typed<T>;
    using branch_token_t = typename SharedContext::barrier_type::template arrival_token_typed<T>;
    total_token_t total_token;
    branch_token_t branch_token;
};
struct arrival_token_fan {
#if GUANAQO_WITH_TRACING && !GUANAQO_WITH_PERFETTO
    using total_token_t  = typename Context<FanSharedContext>::arrival_token::token_t;
    using branch_token_t = typename Context<SharedContext>::arrival_token::token_t;
#else
    using total_token_t  = typename Context<FanSharedContext>::arrival_token;
    using branch_token_t = typename Context<SharedContext>::arrival_token;
#endif
    std::optional<total_token_t> total_token;
    branch_token_t branch_token;
};
template <class SC>
struct FanContext {
    using shared_context_type = SC;
    Context<SharedContext> branch_ctx;
    Context<FanSharedContext> total_ctx;
    index_t index;
    template <class T>
    using arrival_token_typed = FanSharedContext::barrier_type::template arrival_token_typed<T>;
    using arrival_token       = FanSharedContext::barrier_type::arrival_token;
#if GUANAQO_WITH_TRACING&& !GUANAQO_WITH_PERFETTO
    using arrival_t           = Context<SharedContext>::arrival_token::token_t;
    using fan_arrival_t       = Context<FanSharedContext>::arrival_token::token_t;
#else
    using arrival_t           = Context<SharedContext>::arrival_token;
    using fan_arrival_t       = Context<FanSharedContext>::arrival_token;
#endif

    [[nodiscard]] bool is_master() const { return total_ctx.is_master() && branch_ctx.is_master(); }
    /// Arrive at the barrier and obtain a token that can be used to wait for completion of the
    /// current barrier phase.
    /// @note    Token must be awaited before any other call to arrive.
    [[nodiscard]] auto arrive() {
        arrival_token total_token = total_ctx.shared.barrier.get_arrival_token();
#if GUANAQO_WITH_TRACING && !GUANAQO_WITH_PERFETTO
        arrival_t branch_token =
            branch_ctx.arrive_with_completion([&, this] { total_token = total_ctx.arrive().token; });
#else 
        arrival_t branch_token =
            branch_ctx.arrive_with_completion([&, this] { total_token = total_ctx.arrive(); });

#endif
        return arrival_token_fan{.total_token  = std::move(total_token),
                                 .branch_token = std::move(branch_token)};
    }
    /// Await a token returned by @ref arrive(), waiting for the barrier phase to complete.
    void wait(arrival_token_fan &&token) {
        branch_ctx.shared.barrier.wait(std::move(token.branch_token));
        total_ctx.shared.barrier.wait(std::move(*token.total_token));
    }

    /// Arrive at the barrier and wait for the barrier phase to complete. This is a convenience
    /// wrapper around @ref arrive() and @ref wait() for the common case where the thread does not
    /// have other work to do while waiting.
    void arrive_and_wait() {
#if !GUANAQO_WITH_PERFETTO
        GUANAQO_TRACE("barrier-arrive-and-wait", index);
#endif
        // std::cout << "Branch " << total_ctx.index << " is waiting at barrier on thread " << index << "\n";
        // std::cout << "Waiting for " << branch_ctx.num_thr() << " threads to arrive at barrier\n";
        branch_ctx.arrive_and_wait();
        // std::cout << "Branch " << total_ctx.index << " is waiting at barrier on thread " << index << "\n";
        // std::cout << "Waiting for " << total_ctx.num_thr() << " threads to arrive at barrier\n";
        if (branch_ctx.is_master()) {
            total_ctx.arrive_and_wait();
        }
        // std::cout << "Branch " << total_ctx.index << " is waiting at barrier on thread " << index << "\n";
        // std::cout << "Waiting for " << branch_ctx.num_thr() << " threads to arrive at barrier\n";
        branch_ctx.arrive_and_wait();
    }
    /// Debug version of @ref arrive_and_wait() that performs a sanity check to ensure that all
    /// threads are arriving at the same line of code. The @p line parameter should be the same
    /// for all threads arriving at the same barrier. It is only verified in debug builds, and is
    /// equivalent to @ref arrive_and_wait() in release builds.
    void arrive_and_wait(int line) {
#if !GUANAQO_WITH_PERFETTO
        GUANAQO_TRACE("barrier-arrive-and-wait", index);
#endif
        branch_ctx.arrive_and_wait(line);

        if (branch_ctx.is_master()) {
            total_ctx.arrive_and_wait(line);
        }
        branch_ctx.arrive_and_wait(line);
    }
    /// Perform a reduction of @p x across all threads using the given binary function @p func.
    /// Returns a token that can be used to wait for the reduction to complete and obtain the
    /// reduced value.
    template <class T, class F>
    [[nodiscard]] arrival_token_typed_fan<T> arrive_reduce(T x, F func) {
        arrival_token_typed<T> total_token = total_ctx.shared.barrier.get_typed_token<T>();
        auto branch_token =
            branch_ctx.arrive_reduce_with_completion(std::move(x), std::move(func), [&](T x_broad) {
                total_token = total_ctx.arrive_reduce(x_broad, std::move(func));
            });
        return arrival_token_typed_fan<T>{.total_token  = std::move(total_token),
                                          .branch_token = std::move(branch_token)};
    };
    template <class T>
    T wait_reduce(arrival_token_typed_fan<T> &&token) {
        T value = total_ctx.wait_reduce(std::move(token.total_token));
        branch_ctx.shared.barrier.wait(std::move(token.branch_token));
        arrive_and_wait(); // ensure all threads have observed the reduced value before any thread can proceed
        return value;
    }
    /// @todo try to make more simpel probabily overkill by broadcasting again
    template <class T, class F>
    T reduce(T x, F func) {
        T branch_reduced = branch_ctx.reduce(std::move(x), func);
        T total_reduced{};
        if (branch_ctx.index == 0) {
            total_reduced = total_ctx.reduce(std::move(branch_reduced), func);
        }
        return branch_ctx.broadcast(std::move(total_reduced), 0);
    }

    template <class T>
    T reduce(T x) {
        return reduce(std::move(x), std::plus<>{});
    }
    /// Wait for all threads to reach this point, then run the given function on a single thread
    /// before releasing all threads again. Changes by all threads are visible during the call to
    /// @p f and changes made by @p f are visible to all threads after this function returns.
    template <class F>
    auto run_single_sync(F &&f) {
        return branch_ctx.run_single_sync(
            [&] { return total_ctx.run_single_sync(std::forward<F>(f)); });
    }
    /// Broadcast a value @p x from the thread with index @p src to all threads. @todo document
    template <typename T>
    T broadcast(T x, index_t src = 0) {
        const index_t branch_size = branch_ctx.num_thr();
        const index_t src_total   = src / branch_size;
        const index_t src_branch  = src % branch_size;

        if (index == src) {
            auto x_broad = total_ctx.broadcast(x, src);
            return branch_ctx.broadcast(x_broad, src_branch);
        } else if ((total_ctx.index != src_total) && (branch_ctx.index == 0)) {
            auto x_broad = total_ctx.broadcast(x, src);
            return branch_ctx.broadcast(x_broad, 0);
        } else if (total_ctx.index == src_total) {
            return branch_ctx.broadcast(x, src_branch);
        } else {
            return branch_ctx.broadcast(x, 0);
        }
    }
    /// Call a function @p f with the given @p args on a single thread and broadcast the return
    /// value to all threads.
    template <class F, class... Args>
    auto call_broadcast(F &&f, Args &&...args) -> std::invoke_result_t<F, Args...> {
        using T = std::invoke_result_t<F, Args...>;
        // TODO: implement with a relaxed atomic that gets reset during the completion handler,
        //       so only the first thread that arrives will execute the function, rather than always
        //       executing on the master thread.
        if (is_master())
            return broadcast(std::invoke(std::forward<F>(f), std::forward<Args>(args)...), 0);
        else
            return broadcast(T{}, 0);
    }
};
template <class F>
void SharedContext::run(F &&f) {

#if !BATMAT_WITH_OPENMP
    thread_pool.sync_run_n(num_thr, [this, &f](index_t i, index_t) {
        Context<SharedContext> ctx{.shared = *this, .index = i};
        f(ctx);
    });
#else
    BATMAT_OMP(parallel for num_threads(num_thr))
    for (index_t i = 0; i < num_thr; ++i) {
        Context<SharedContext> ctx{.shared = *this, .index = i};
        f(ctx);
    }
#endif
}

template <class F>
void FanSharedContext::run(F &&f) {

    std::vector<index_t> cumulative(branch_contexts.size());

    index_t sum = 0;
    for (index_t i = 0; i < num_thr; ++i) {
        cumulative[i] = sum;
        sum += branch_contexts[i].num_thr;

    }
    // std::cout << "Cumulative: ";
    // for (const auto &c : cumulative) {
    //     std::cout << c << " ";
    // }
    // std::cout << "\n";
    index_t total_num_thr = sum;

#if !BATMAT_WITH_OPENMP
    thread_pool.sync_run_n(num_thr, [this, &f, &cumulative](index_t i, index_t) {
        branch_contexts[i].thread_pool.sync_run_n(
            branch_contexts[i].num_thr, [this, &f, i, &cumulative](index_t j, index_t) {
                Context<FanSharedContext> total_ctx{.shared = *this, .index = i};
                Context<SharedContext> branch_ctx{.shared = branch_contexts[i], .index = j};
                FanContext<FanSharedContext> ctx{
                    .branch_ctx = branch_ctx, .total_ctx = total_ctx, .index = cumulative[i] + j};
                f(ctx);
            });
    });
#else
    // omp_set_max_active_levels(2);
    // BATMAT_OMP(parallel for num_threads(num_thr) proc_bind(spread))
    // for (index_t i = 0; i < num_thr; ++i) {

    //     BATMAT_OMP(parallel for num_threads(branch_contexts[i].num_thr) proc_bind(close))
    //     for (index_t j = 0; j < branch_contexts[i].num_thr; ++j) {
    //         Context<FanSharedContext> total_ctx{.shared = *this, .index = i};
    //         Context<SharedContext> branch_ctx{.shared = branch_contexts[i], .index = j};
    //         FanContext<FanSharedContext> ctx{
    //             .branch_ctx = branch_ctx, .total_ctx = total_ctx, .index = cumulative[i] + j};
    //         f(ctx);
    //     }
    // }
    BATMAT_OMP(parallel for num_threads(total_num_thr))
    for (index_t idx = 0; idx < total_num_thr; ++idx) {

        // recover i
        index_t i = static_cast<index_t>(std::upper_bound(cumulative.begin(), cumulative.end(), idx) - cumulative.begin() - 1);

        index_t j = idx - cumulative[i];

        Context<FanSharedContext> total_ctx{.shared = *this, .index = i};
        Context<SharedContext> branch_ctx{.shared = branch_contexts[i], .index = j};

        FanContext<FanSharedContext> ctx{
            .branch_ctx = branch_ctx,
            .total_ctx = total_ctx,
            .index = idx
        };

        f(ctx);
}

#endif
}
}
