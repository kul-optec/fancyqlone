#include <cyqlone/conversion.hpp>
#include <cyqlone/qpalm/backends/ocp-backend-cyqlone.hpp>
#include <cyqlone/qpalm/example-problems/csv.hpp>
#include <cyqlone/qpalm/example-problems/platooning.hpp>
#include <cyqlone/qpalm/solver.hpp>
#include "cyqlone/cyqlone-storage.hpp"
#include "cyqlone/fan-cyqlone.hpp"
#include "cyqlone/matio.hpp"
#include "cyqlone/ocp.hpp"
#include <gtest/gtest.h>
#include <cyqlone-version.h>
#include <fstream>

#include <batmat/loop.hpp>
#include <guanaqo/io/csv.hpp>
#include <guanaqo/print.hpp>
#include <guanaqo/trace.hpp>
#include <iostream>
#include <vector>

#include <cyqlone/conversion.hpp>
using cyqlone::index_t;
using cyqlone::real_t;
using StorageOrder = cyqlone::StorageOrder;

namespace qp = cyqlone::qpalm;
index_t cyq_get_num_proc();
#if GUANAQO_WITH_TRACING
static void init_trace() {
    guanaqo::get_trace_logger().reset();
    guanaqo::get_trace_logger().logs.resize(65565);
    GUANAQO_TRACE("init", 0);
}
static std::filesystem::path save_trace(const char *name) {
    std::optional tr = guanaqo::get_trace_logger().trace("end", 0);
    std::filesystem::path out_dir{"traces"};
    out_dir /= *cyqlone_commit_hash ? cyqlone_commit_hash : "unknown";
    std::filesystem::path out_file = out_dir / name;
    std::filesystem::create_directories(out_dir);
    std::ofstream csv{out_file};
    guanaqo::TraceLogger::write_column_headings(csv) << '\n';
    tr.reset();
    for (const auto &log : guanaqo::get_trace_logger().get_logs())
        csv << log << '\n';
    return out_file;
}
#endif

#include <fstream>

#include <iostream>

#include <cmath>
#include <cstddef>
#include <iostream>
#include <string_view>
#include <vector>

#include <cmath>
#include <span>
#include <vector>
TEST(QPALM, with_inequality_2iter) {
    index_t num_branches = 2;
    index_t N            = 32;
    std::vector<cyqlone::LinearOCPStorage> ocps(num_branches);
    for (index_t i = 0; i < num_branches; ++i) {
        auto filename = std::format("python/cmpc/ocp_data_constr{}_{}.mat", N, i);

        cyqlone::LinearOCPStorage ocp_fan;
        auto matfp = cyqlone::open_mat(filename);
        cyqlone::read_from_mat(matfp.get(), "ocp", ocp_fan);

        ocps[i] = ocp_fan;
        guanaqo::print_python(std::cout << "x(0) = ", ocp_fan.b(0), "\n");
        std::cout << "Loaded OCP data from " << filename << " with N=" << ocp_fan.dim.N_horiz
                  << ", nu=" << ocp_fan.dim.nu << ", ny=" << ocp_fan.dim.ny << "\n";
    }
    std::cout << cyq_get_num_proc() << " processors detected\n";
    cyqlone::FanOCPStorage fan_ocp{.ocps    = ocps
    };
    auto cocp          = cyqlone::FanCyqloneStorage<>::build(fan_ocp, ocps[0].D(0).cols);

};