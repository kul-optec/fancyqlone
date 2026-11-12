#include <fancyqlone/fancyqpalm/status.hpp>
#include <ostream>

namespace fancyqlone::qpalm {

std::ostream &operator<<(std::ostream &os, SolverStatus s) { return os << enum_name(s); }

} // namespace fancyqlone::qpalm
