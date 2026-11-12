#pragma once

#include <batmat/config.hpp>

#if defined(__AVX512F__)
#define FANCYQLONE_NS(ns) ns::inline avx512
#elif defined(__AVX2__)
#define FANCYQLONE_NS(ns) ns::inline avx2
#else
#define FANCYQLONE_NS(ns) ns
#endif

namespace fancyqlone {
using batmat::index_t;
using batmat::real_t;
} // namespace fancyqlone
