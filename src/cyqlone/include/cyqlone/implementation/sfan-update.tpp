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
void SerialFanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve(Context &ctx, const FanStorage &ΔΣ,
                                                                    FanStorage &ux, FanStorage &λ) {
    // std::cout << "update_solve not implemented yet" << std::endl;

    // std::cout << "ΔΣ: " << ΔΣ.first.rows() << std::endl;
    // std::cout << "ux: " << ux.first.rows() << std::endl;
    // std::cout << "λ: " << λ.first.rows() << std::endl;
    // std::cout << "ctx index: " << ctx.total_ctx.index << std::endl;
    throw std::runtime_error("update_solve not implemented yet");
}
} // namespace CYQLONE_NS(cyqlone)