#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.tpp>
#include <cyqlone/qpalm/implementation/solver.tpp>
#include <cyqlone/qpalm/backends/backend-cyqlone/ineq-constr.tpp>
#include <cyqlone/qpalm/backends/backend-cyqlone/linalg.tpp>
#include <cyqlone/qpalm/backends/backend-cyqlone/linesearch.tpp>
#include <cyqlone/qpalm/backends/backend-cyqlone/solve.tpp>
#include "cyqlone/parallel.hpp"
#include <batmat/config.hpp>

namespace CYQLONE_NS(cyqlone::qpalm) {

#define CYQLONE_INSTANTIATE_QPALM_Cyqlone(v, order)                                                \
                                                                                                   \
    template class Solver<CyQPALMBackend<v, order> *>;                                             \
    template class Solver<unique_CyQPALMBackend<v, order>>;                                        \
    template struct unique_CyQPALMBackend<v, order>;                                               \
                                                                                                   \
    template unique_CyQPALMBackend<v, order> make_cyqpalm_backend<v, order>(                       \
        const CyQPALMBackend<v, order>::traits::CStorage &ocp, CyqloneData data,                   \
        const CyQPALMBackendSettings &settings);                                                   \
    template void update_cyqpalm_backend<v, order>(                                                \
        CyQPALMBackend<v, order> &, const CyQPALMBackend<v, order>::traits::CStorage &ocp);        \
    template void update_cyqpalm_backend<v, order>(                                                \
        CyQPALMBackend<v, order> &,                                                                \
        const typename CyQPALMBackend<v, order>::traits::OCPStorage &ocp);

// BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_Cyqlone, StorageOrder::ColMajor)
// BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_Cyqlone, StorageOrder::RowMajor)
template <index_t v, StorageOrder order>
using DefaultInnerSolver =
    CyqloneSolver<
        v,
        real_t,
        order,
        parallel::Context<parallel::SharedContext>
    >;

template <index_t v, StorageOrder order>
using FanInnerSolver =
    FanCyqloneSolver<
        v,
        real_t,
        order,
        parallel::FanContext<parallel::FanSharedContext>
    >;
template <index_t v, StorageOrder order>
using SerialFanInnerSolver =
    SerialFanCyqloneSolver<
        v,
        real_t,
        order,
        parallel::Context<parallel::SharedContext>
    >;
#define CYQLONE_INSTANTIATE_QPALM_FanCyqlone(v, order, InnerSolver)                                             \
                                                                                                   \
    template class Solver<CyQPALMBackend<v, order, InnerSolver<v, order>> *>;                      \
    template class Solver<unique_CyQPALMBackend<v, order, InnerSolver<v, order>>>;                 \
    template struct unique_CyQPALMBackend<v, order, InnerSolver<v, order>>;                        \
                                                                                                   \
    template unique_CyQPALMBackend<v, order, InnerSolver<v, order>>                                \
    make_cyqpalm_backend<v, order>(                                                                \
        const CyQPALMBackend<v, order, InnerSolver<v, order>>::traits::CStorage &ocp,              \
        CyqloneData data, const CyQPALMBackendSettings &settings);                                 \
    template void update_cyqpalm_backend<v, order>(                                                \
        CyQPALMBackend<v, order, InnerSolver<v, order>> &,                                         \
        const CyQPALMBackend<v, order, InnerSolver<v, order>>::traits::CStorage &ocp);             \
    template void update_cyqpalm_backend<v, order>(                                                \
        CyQPALMBackend<v, order, InnerSolver<v, order>> &,                                         \
        const typename CyQPALMBackend<v, order, InnerSolver<v, order>>::traits::OCPStorage &ocp);

BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_FanCyqlone, StorageOrder::ColMajor, DefaultInnerSolver)
BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_FanCyqlone, StorageOrder::ColMajor, FanInnerSolver)
BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_FanCyqlone, StorageOrder::ColMajor, SerialFanInnerSolver)
BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_FanCyqlone, StorageOrder::RowMajor, DefaultInnerSolver)

// BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_FanCyqlone, StorageOrder::RowMajor, FanInnerSolver)
// BATMAT_FOREACH_VL_DEFAULT(CYQLONE_INSTANTIATE_QPALM_FanCyqlone, StorageOrder::RowMajor)
} // namespace CYQLONE_NS(cyqlone::qpalm)
