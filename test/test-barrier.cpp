#include <fancyqlone/barrier.hpp>
#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <vector>
#include <version>
#if defined(__linux__)
#include <guanaqo/string-util.hpp>
#include <sys/utsname.h>
#endif

class BarrierTest : public ::testing::TestWithParam<uint32_t> {};

fancyqlone::index_t cyq_get_num_proc();

static bool old_kernel() {
#if defined(__linux__)
    // Check if the kernel version is older than 6.x, which seems to cause issues with futexes
    // not waking up threads properly.
    struct utsname buf;
    if (uname(&buf) == 0) {
        auto [maj, _] = guanaqo::split(buf.release, ".");
        // NOLINTNEXTLINE(*-suspicious-stringview-data-usage): maj is null-terminated, and atoi
        return std::atoi(maj.data()) < 6; // only reads until the first non-digit.
    }
#endif
    return false;
}

TEST_P(BarrierTest, stress) {
    if (old_kernel())
        GTEST_SKIP() << "Skipping test on old Linux kernel";
    const uint32_t num_workers = GetParam();
    const auto hw_workers      = static_cast<uint32_t>(cyq_get_num_proc());
    const uint32_t iterations  = num_workers <= hw_workers ? 100'000 : 100;

    using Barrier = fancyqlone::TreeBarrier<>;
    ASSERT_GE(Barrier::max(), num_workers + 1);
    Barrier barrier(num_workers + 1, {});

    std::atomic<uint32_t> counter{0};
    std::vector<std::jthread> threads;
    threads.reserve(num_workers);

    // Worker threads
    for (uint32_t i = 0; i < num_workers; ++i) {
        threads.emplace_back([&, i] {
            uint32_t success = 0;
            for (uint32_t iter = 0; iter < iterations; ++iter) {
                uint32_t val = counter.load(std::memory_order_relaxed);
                success += (val == iter || val == iter + 1);
                success += decltype(barrier)::BarrierPhase{iter} == barrier.current_phase();
                barrier.arrive_and_wait(i + 1); // worker IDs start at 1
            }
            EXPECT_EQ(success, 2 * iterations) << i;
        });
    }

    // Counter thread (thread_id = 0)
    std::jthread counter_thread{[&] {
        for (uint32_t iter = 0; iter < iterations; ++iter) {
            counter.fetch_add(1, std::memory_order_relaxed);
            barrier.arrive_and_wait(0);
        }
    }};
}

#if __cpp_lib_barrier >= 201907L
#include <barrier>

TEST_P(BarrierTest, std) {
    if (old_kernel())
        GTEST_SKIP() << "Skipping test on old Linux kernel";
    const uint32_t num_workers = GetParam();
    const auto hw_workers      = static_cast<uint32_t>(cyq_get_num_proc());
    const uint32_t iterations  = num_workers <= hw_workers ? 100'000 : 100;

    using Barrier = std::barrier<>;
    ASSERT_GE(Barrier::max(), num_workers + 1);
    Barrier barrier(num_workers + 1, {});

    std::atomic<uint32_t> counter{0};
    std::vector<std::jthread> threads;
    threads.reserve(num_workers);

    // Worker threads
    for (uint32_t i = 0; i < num_workers; ++i) {
        threads.emplace_back([&, i] {
            uint32_t success = 0;
            for (uint32_t iter = 0; iter < iterations; ++iter) {
                uint32_t val = counter.load(std::memory_order_relaxed);
                success += (val == iter || val == iter + 1);
                barrier.arrive_and_wait();
            }
            EXPECT_EQ(success, iterations) << i;
        });
    }

    // Counter thread (thread_id = 0)
    std::jthread counter_thread{[&] {
        for (uint32_t iter = 0; iter < iterations; ++iter) {
            counter.fetch_add(1, std::memory_order_relaxed);
            barrier.arrive_and_wait();
        }
    }};
}
#endif

TEST_P(BarrierTest, reduce) {
    if (old_kernel())
        GTEST_SKIP() << "Skipping test on old Linux kernel";
    const uint32_t num_workers = GetParam();
    const auto hw_workers      = static_cast<uint32_t>(cyq_get_num_proc());
    const uint32_t iterations  = num_workers <= hw_workers ? 100'000 : 100;

    using Barrier = fancyqlone::TreeBarrier<>;
    ASSERT_GE(Barrier::max(), num_workers);
    Barrier barrier(num_workers, {});

    std::vector<std::jthread> threads;
    threads.reserve(num_workers);

    for (uint32_t i = 0; i < num_workers; ++i) {
        threads.emplace_back([&, i] {
            uint32_t success = 0;
            for (uint32_t iter = 0; iter < iterations; ++iter) {
                auto res = barrier.reduce(i, i + 1, std::plus{});
                success += res == num_workers * (num_workers + 1) / 2;
            }
            EXPECT_EQ(success, iterations) << i;
        });
    }
}

TEST_P(BarrierTest, shuffle) {
    if (old_kernel())
        GTEST_SKIP() << "Skipping test on old Linux kernel";
    const uint32_t num_workers = GetParam();
    const auto hw_workers      = static_cast<uint32_t>(cyq_get_num_proc());
    const uint32_t iterations  = num_workers <= hw_workers ? 30'000 : 100;

    using Barrier = fancyqlone::TreeBarrier<>;
    ASSERT_GE(Barrier::max(), num_workers);
    Barrier barrier(num_workers, {});

    std::vector<std::jthread> threads;
    threads.reserve(num_workers);

    for (uint32_t i = 0; i < num_workers; ++i) {
        threads.emplace_back([&, i] {
            uint32_t success = 0;
            for (uint32_t iter = 0; iter < iterations; ++iter) {
                auto encode = [iter](uint32_t stage, uint32_t thread_id) {
                    return stage * uint64_t{1'000'000'000} + iter * uint64_t{10'000} + thread_id;
                };

                // First shuffle: receive from thread_id - 1.
                const uint32_t src_rotr = (i - 1 + num_workers) % num_workers;
                auto token_rotr         = barrier.shuffle_rotr_start(i, encode(0, i), 1);
                success += barrier.shuffle_wait(i, std::move(token_rotr)) == encode(0, src_rotr);

                // Second shuffle: receive from thread_id + n, using the non-void callback overload.
                const uint32_t rotl_n   = (num_workers + 1) / 2;
                const uint32_t src_rotl = (i + rotl_n) % num_workers;
                auto token_rotl         = barrier.shuffle_rotl_start(i, encode(1, i), rotl_n);
                success += barrier.shuffle_wait(i, std::move(token_rotl), [](uint64_t x) {
                    return x ^ uint64_t{0x5A5A5A5A5A5A5A5A};
                }) == (encode(1, src_rotl) ^ uint64_t{0x5A5A5A5A5A5A5A5A});

                // Third shuffle: explicit reverse permutation, using the void callback overload.
                const uint32_t src_reverse = num_workers - 1 - i;
                auto token_reverse         = barrier.shuffle_start(i, encode(2, i), src_reverse);
                barrier.shuffle_wait(i, std::move(token_reverse),
                                     [&](uint64_t x) { success += x == encode(2, src_reverse); });
            }
            EXPECT_EQ(success, 3 * iterations) << i;
        });
    }
}

// Instantiate the test with different numbers of worker threads
INSTANTIATE_TEST_SUITE_P(BarrierTest, BarrierTest,
                         ::testing::Values(1, 2, 3, 4, 5, 6, 7, 8, 9, 254, 255, 256, 257));
