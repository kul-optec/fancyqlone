#include <fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp>
#include <fancyqlone/sequential-fancyqlone/implementation/sfan-data.tpp>
#include <fancyqlone/sequential-fancyqlone/implementation/sfan-factor.tpp>
#include <fancyqlone/sequential-fancyqlone/implementation/sfan-mat-vec.tpp>
#include <fancyqlone/sequential-fancyqlone/implementation/sfan-update.tpp>


namespace CYQLONE_NS(cyqlone) {

#define SerialFANCYQLONE_INSTANTIATE_CYQLONE(VL, O) template struct SerialFanCyqloneSolver<VL, real_t, O>;
BATMAT_FOREACH_VL_DEFAULT(SerialFANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::ColMajor)
BATMAT_FOREACH_VL_DEFAULT(SerialFANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::RowMajor)

} // namespace CYQLONE_NS(cyqlone)
