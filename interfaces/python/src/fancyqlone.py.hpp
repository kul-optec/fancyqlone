#pragma once

#include <cyqlone/config.hpp>
#include <nanobind/nanobind.h>

namespace CYQLONE_NS(cyqlone) {

template <index_t VL>
void register_fancyqlone_solver(nanobind::module_ &m);

} // namespace CYQLONE_NS(cyqlone)
