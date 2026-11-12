#pragma once

#include <fancyqlone/config.hpp>
#include <nanobind/nanobind.h>

namespace FANCYQLONE_NS(fancyqlone) {

template <index_t VL>
void register_fancyqlone_solver(nanobind::module_ &m);

} // namespace FANCYQLONE_NS(fancyqlone)
