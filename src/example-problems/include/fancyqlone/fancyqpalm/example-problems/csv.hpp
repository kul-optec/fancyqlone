#pragma once

#include <fancyqlone/config.hpp>
#include <fancyqlone/example-problems/export.h>
#include <fancyqlone/ocp.hpp>

#include <filesystem>

namespace FANCYQLONE_NS(fancyqlone::qpalm::problems) {

namespace fs = std::filesystem;

LinearOCPStorage CYQLONE_EXAMPLE_PROBLEMS_EXPORT load_from_csv(const fs::path &folder,
                                                               const std::string &name);

} // namespace FANCYQLONE_NS(fancyqlone::qpalm::problems)
