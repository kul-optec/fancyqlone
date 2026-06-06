#include <cyqlone/fan-cyqlone.hpp>
#include <cyqlone/implementation/fan-data.tpp>
#include <cyqlone/implementation/fan-factor.tpp>
#include <cyqlone/implementation/fan-mat-vec.tpp>
#include <cyqlone/implementation/fan-update.tpp>


namespace CYQLONE_NS(cyqlone) {

#define FANCYQLONE_INSTANTIATE_CYQLONE(VL, O) template struct FanCyqloneSolver<VL, real_t, O>;
BATMAT_FOREACH_VL_DEFAULT(FANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::ColMajor)
BATMAT_FOREACH_VL_DEFAULT(FANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::RowMajor)

} // namespace CYQLONE_NS(cyqlone)
