#include <cyqlone/cyqlone.hpp>

#include <batmat/assume.hpp>

namespace CYQLONE_NS(cyqlone) {

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto TricyqleSolver<VL, T, DefaultOrder, Ctx>::sub_wrap_ceil_p(index_t a, index_t b) const
    -> index_t {
    const index_t c = ceil_p();
    BATMAT_ASSUME(c > 0);
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < c);
    a -= b;
    return a < 0 ? a + c : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto TricyqleSolver<VL, T, DefaultOrder, Ctx>::add_wrap_ceil_p(index_t a, index_t b) const
    -> index_t {
    const index_t c = ceil_p();
    BATMAT_ASSUME(c > 0);
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < c);
    a += b;
    return a >= c ? a - c : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto TricyqleSolver<VL, T, DefaultOrder, Ctx>::sub_wrap_p(index_t a, index_t b) const -> index_t {
    BATMAT_ASSUME(p > 0);
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < p);
    a -= b;
    return a < 0 ? a + p : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto TricyqleSolver<VL, T, DefaultOrder, Ctx>::add_wrap_p(index_t a, index_t b) const -> index_t {
    BATMAT_ASSUME(p > 0);
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < p);
    a += b;
    return a >= p ? a - p : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
[[nodiscard]] index_t TricyqleSolver<VL, T, DefaultOrder, Ctx>::ν2(index_t bi) const {
    BATMAT_ASSUME(bi > 0);
    auto ui = static_cast<std::make_unsigned_t<index_t>>(bi);
    return static_cast<index_t>(std::countr_zero(ui));
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
[[nodiscard]] index_t TricyqleSolver<VL, T, DefaultOrder, Ctx>::ν2p(index_t bi) const {
    BATMAT_ASSUME(bi >= 0);
    return bi == 0 ? lp() : ν2(bi);
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::add_wrap_ceil_N(index_t a, index_t b) const
    -> index_t {
    const index_t N = ceil_N();
    BATMAT_ASSUME(N >= 0);
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < N);
    a += b;
    return a >= N ? a - N : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::sub_wrap_ceil_N(index_t a, index_t b) const
    -> index_t {
    const index_t N = ceil_N();
    BATMAT_ASSUME(N >= 0);
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < N);
    a -= b;
    return a < 0 ? a + N : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::sub_wrap_p(index_t a, index_t b) const -> index_t {
    return tricyqle.sub_wrap_p(a, b);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::add_wrap_p(index_t a, index_t b) const -> index_t {
    return tricyqle.add_wrap_p(a, b);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::sub_wrap_ceil_p(index_t a, index_t b) const
    -> index_t {
    return tricyqle.sub_wrap_ceil_p(a, b);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::add_wrap_ceil_p(index_t a, index_t b) const
    -> index_t {
    return tricyqle.add_wrap_ceil_p(a, b);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::sub_wrap_ceil_P(index_t a, index_t b) const
    -> index_t {
    const index_t c = ceil_P();
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < c);
    a -= b;
    return a < 0 ? a + c : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::add_wrap_ceil_P(index_t a, index_t b) const
    -> index_t {
    const index_t c = ceil_P();
    BATMAT_ASSUME(a >= 0);
    BATMAT_ASSUME(b >= 0);
    BATMAT_ASSUME(a < c);
    a += b;
    return a >= c ? a - c : a;
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
auto CyqloneSolver<VL, T, DefaultOrder, Ctx>::get_linear_batch_offset(index_t biA) const
    -> index_t {
    const auto levA = biA > 0 ? get_level(biA) : lp() + lv();
    const auto levP = lp();
    if (levA >= levP)
        return (((1 << levP) - 1) << (lp() + lv() - levP)) + (biA >> levP);
    return (((1 << levA) - 1) << (lp() + lv() - levA)) + get_index_in_level(biA);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
[[nodiscard]] index_t CyqloneSolver<VL, T, DefaultOrder, Ctx>::ν2(index_t bi) const {
    return tricyqle.ν2(bi);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
[[nodiscard]] index_t CyqloneSolver<VL, T, DefaultOrder, Ctx>::ν2p(index_t bi) const {
    return tricyqle.ν2p(bi);
}
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
[[nodiscard]] index_t CyqloneSolver<VL, T, DefaultOrder, Ctx>::stage_index(index_t c, index_t i,
                                                                           index_t l) const {
    return params.eliminate_u0_first ? sub_wrap_ceil_N(c * n + l * p * n, i)
                                     : sub_wrap_ceil_N(c * n + l * p * n + n - 1, i);
}

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
[[nodiscard]] StageIndexInv
CyqloneSolver<VL, T, DefaultOrder, Ctx>::inverse_stage_index(index_t stage) const {
    const index_t N = ceil_N();

    BATMAT_ASSUME(stage >= 0);
    BATMAT_ASSUME(stage < N);
    BATMAT_ASSUME(n > 0);
    BATMAT_ASSUME(N % n == 0);

    const index_t K = N / n; // should be p * VL

    const index_t q = stage / n;
    const index_t r = stage - q * n;

    index_t k;
    index_t i;

    if (params.eliminate_u0_first) {
        // stage = n*k - i mod N
        if (r == 0) {
            k = q;
            i = 0;
        } else {
            k = q + 1;
            if (k == K)
                k = 0;

            i = n - r;
        }
    } else {
        // stage = n*k + n - 1 - i mod N
        k = q;
        i = n - 1 - r;
    }

    const index_t c = k % p;
    const index_t l = k / p;

    BATMAT_ASSUME(c >= 0);
    BATMAT_ASSUME(c < p);
    BATMAT_ASSUME(l >= 0);
    BATMAT_ASSUME(l < VL);
    BATMAT_ASSUME(i >= 0);
    BATMAT_ASSUME(i < n);
    BATMAT_ASSERT(stage == stage_index(c, i, l));
    return {
        .c = c,
        .i = i,
        .l = l,
    };
}

} // namespace CYQLONE_NS(cyqlone)
