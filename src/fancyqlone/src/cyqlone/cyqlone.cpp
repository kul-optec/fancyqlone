#include <batmat/config.hpp>
#include <fancyqlone/cyqlone/cyqlone.hpp>
#include <fancyqlone/cyqlone/implementation/cr.tpp>
#include <fancyqlone/cyqlone/implementation/data.tpp>
#include <fancyqlone/cyqlone/implementation/factor.tpp>
#include <fancyqlone/cyqlone/implementation/indexing.tpp>
#include <fancyqlone/cyqlone/implementation/mat-vec.tpp>
#include <fancyqlone/cyqlone/implementation/pcg.tpp>
#include <fancyqlone/cyqlone/implementation/pcr.tpp>
#include <fancyqlone/cyqlone/implementation/riccati.tpp>
#include <fancyqlone/cyqlone/implementation/schur.tpp>
#include <fancyqlone/cyqlone/implementation/sparse.tpp>
#include <fancyqlone/cyqlone/implementation/update.tpp>

namespace FANCYQLONE_NS(fancyqlone) {

#define CYQLONE_INSTANTIATE_TRICYQLE(T, VL, O) template struct TricyqleSolver<VL, T, O>;
BATMAT_FOREACH_DTYPE_VL(CYQLONE_INSTANTIATE_TRICYQLE, StorageOrder::ColMajor)
BATMAT_FOREACH_DTYPE_VL(CYQLONE_INSTANTIATE_TRICYQLE, StorageOrder::RowMajor)
#define CYQLONE_INSTANTIATE_CYQLONE(VL, O) template struct CyqloneSolver<VL, real_t, O>;
BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_CYQLONE, StorageOrder::ColMajor)
BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_CYQLONE, StorageOrder::RowMajor)

} // namespace FANCYQLONE_NS(fancyqlone)
