#include <cyqlone/cyqlone.hpp>
#include <cyqlone/fan-cyqlone.hpp>

#include <cyqlone/linalg.hpp>

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
void FanCyqloneSolver<VL, T, DefaultOrder, Ctx>::update_solve(Context &ctx, FanStorage ΔΣ,
                                                              FanStorage ux, FanStorage λ) {
    auto temp5 = ctx.is_master();
    auto temp2 = ΔΣ;
    auto temp3 = ux;
    auto temp4 = λ;
    throw std::runtime_error("Not implemented");
}
} // namespace CYQLONE_NS(cyqlone)