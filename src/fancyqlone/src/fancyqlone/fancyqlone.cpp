#include <fancyqlone/fancyqlone/fancyqlone.hpp>
#include <fancyqlone/fancyqlone/implementation/fan-data.tpp>
#include <fancyqlone/fancyqlone/implementation/fan-factor.tpp>
#include <fancyqlone/fancyqlone/implementation/fan-mat-vec.tpp>
#include <fancyqlone/fancyqlone/implementation/fan-update.tpp>


namespace CYQLONE_NS(cyqlone) {

#define FANCYQLONE_INSTANTIATE_CYQLONE(VL, O) template struct FanCyqloneSolver<VL, real_t, O>;
BATMAT_FOREACH_VL_DEFAULT(FANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::ColMajor)
BATMAT_FOREACH_VL_DEFAULT(FANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::RowMajor)

} // namespace CYQLONE_NS(cyqlone)
