#include <cyqlone/cyqlone.hpp>
#include <cyqlone/serial-fan-cyqlone.hpp>

#include <cyqlone/linalg.hpp>
#include <fstream>
#include <iostream>
#include <batmat/assume.hpp>
#include <batmat/linalg/copy.hpp>
#include <batmat/linalg/gemv.hpp>
#include <batmat/linalg/simdify.hpp>
#include <batmat/linalg/symv.hpp>
#include <batmat/linalg/uview.hpp>
#include <batmat/loop.hpp>
namespace CYQLONE_NS(cyqlone) {
namespace la = cyqlone::linalg;

using la::tril;
template <index_t VL, class T, StorageOrder DefaultOrder, class Ctx>
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve(
    [[maybe_unused]] Context &ctx,
    [[maybe_unused]] const FanStorage &ΔΣ,
    [[maybe_unused]] FanStorage &ux,
    [[maybe_unused]] FanStorage &λ)
{
    throw std::runtime_error("update_solve not implemented yet");
}
} // namespace CYQLONE_NS(cyqlone)