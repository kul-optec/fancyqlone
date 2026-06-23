#include <cyqlone/serial-fan-cyqlone.hpp>
#include <cyqlone/implementation/sfan-data.tpp>
#include <cyqlone/implementation/sfan-factor.tpp>
#include <cyqlone/implementation/sfan-mat-vec.tpp>
#include <cyqlone/implementation/sfan-update.tpp>


namespace CYQLONE_NS(cyqlone) {

#define SerialFANCYQLONE_INSTANTIATE_CYQLONE(VL, O) template struct SerialFanCyqloneSolver<VL, real_t, O>;
BATMAT_FOREACH_VL_DEFAULT(SerialFANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::ColMajor)
BATMAT_FOREACH_VL_DEFAULT(SerialFANCYQLONE_INSTANTIATE_CYQLONE, StorageOrder::RowMajor)

} // namespace CYQLONE_NS(cyqlone)
