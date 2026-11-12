
#include <fancyqlone/cyqlone/cyqlone.hpp>
#include <fancyqlone/fancyqlone/fancyqlone.hpp>

#include <fancyqlone/linalg.hpp>
#include <fancyqlone/packing.hpp>
#include <batmat/assume.hpp>
#include <batmat/linalg/copy.hpp>
#include <batmat/linalg/gemm.hpp>
#include <batmat/linalg/gemv.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/simdify.hpp>
#include <batmat/linalg/symv.hpp>
#include <batmat/linalg/uview.hpp>
#include <batmat/loop.hpp>
#include <fstream>
#include <iostream>
namespace FANCYQLONE_NS(fancyqlone) {
namespace la = fancyqlone::linalg;

using la::tril;

template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve(
    [[maybe_unused]] Context &ctx,
    [[maybe_unused]] const FanStorage &ΔΣ,
    [[maybe_unused]] FanStorage &ux,
    [[maybe_unused]] FanStorage &λ)
{
    throw std::runtime_error("update_solve not implemented yet");
}
} // namespace FANCYQLONE_NS(fancyqlone)
