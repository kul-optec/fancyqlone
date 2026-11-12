include(cmake/Library.cmake)
find_package(guanaqo REQUIRED COMPONENTS BLAS)
find_package(batmat REQUIRED)
if (CYQLONE_WITH_ZLIB)
    find_package(ZLIB REQUIRED)
endif()

# Main library
# ------------------------------------------------------------------------------
add_library(cyqlone
    "fancyqlone/src/conversion.cpp"
    "fancyqlone/src/cyqlone/cyqlone.cpp"
    "fancyqlone/src/fancyqlone/fancyqlone.cpp"
    "fancyqlone/src/sequential-fancyqlone/serial-fancyqlone.cpp"
    "fancyqlone/src/cyqlone/cyqlone-storage.cpp"
    "fancyqlone/src/ocp.cpp"
    "fancyqlone/src/tracing.cpp"
)
target_sources(cyqlone PUBLIC FILE_SET HEADERS
    BASE_DIRS "fancyqlone/include"
    FILES "fancyqlone/include/fancyqlone/config.hpp"
          "fancyqlone/include/fancyqlone/ocp.hpp"
          "fancyqlone/include/fancyqlone/random-ocp.hpp"
          "fancyqlone/include/fancyqlone/conversion.hpp"
          "fancyqlone/include/fancyqlone/cyqlone/cyqlone-params.hpp"
          "fancyqlone/include/fancyqlone/cyqlone/cyqlone-storage.hpp"
          "fancyqlone/include/fancyqlone/neumaier.hpp"
          "fancyqlone/include/fancyqlone/cyqlone/cyqlone.hpp"
          "fancyqlone/include/fancyqlone/fancyqlone/fancyqlone.hpp"
          "fancyqlone/include/fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp"
          "fancyqlone/include/fancyqlone/cyqlone/tridiagonal-solver.hpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/indexing.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/update.tpp"
          "fancyqlone/include/fancyqlone/fancyqlone/implementation/fan-update.tpp"
          "fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/sfan-update.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/factor.tpp"
          "fancyqlone/include/fancyqlone/fancyqlone/implementation/fan-factor.tpp"
          "fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/sfan-factor.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/pcr.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/cr.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/mat-vec.tpp"
          "fancyqlone/include/fancyqlone/fancyqlone/implementation/fan-mat-vec.tpp"
          "fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/sfan-mat-vec.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/schur.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/pcg.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/riccati.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/data.tpp"
          "fancyqlone/include/fancyqlone/fancyqlone/implementation/fan-data.tpp"
          "fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/sfan-data.tpp"
          "fancyqlone/include/fancyqlone/cyqlone/implementation/sparse.tpp"
          "fancyqlone/include/fancyqlone/linalg.hpp"
          "fancyqlone/include/fancyqlone/packing.hpp"
          "fancyqlone/include/fancyqlone/parallel.hpp"
          "fancyqlone/include/fancyqlone/timing.hpp"
          "fancyqlone/include/fancyqlone/tracing.hpp"
          "fancyqlone/include/fancyqlone/barrier.hpp"
          "fancyqlone/include/fancyqlone/sparse.hpp"
)
target_link_libraries(cyqlone PUBLIC batmat::batmat guanaqo::guanaqo guanaqo::blas
                              PRIVATE cyqlone::warnings)
cyqlone_configure_library(cyqlone)
target_compile_definitions(cyqlone PUBLIC
    $<$<BOOL:${CYQLONE_COMPENSATE_SUM_LINE_SEARCH}>:CYQLONE_COMPENSATE_SUM_LINE_SEARCH>
    $<$<BOOL:${CYQLONE_QUADRUPLE_SUM_LINE_SEARCH}>:CYQLONE_QUADRUPLE_SUM_LINE_SEARCH>
    $<$<BOOL:${CYQLONE_WITH_MATIO}>:CYQLONE_WITH_MATIO>
    $<$<BOOL:${CYQLONE_WITH_ZLIB}>:CYQLONE_WITH_ZLIB>)
if (CYQLONE_WITH_MATIO)
    find_package(matio REQUIRED)
    target_sources(cyqlone PRIVATE "fancyqlone/src/matio.cpp")
    target_sources(cyqlone PUBLIC FILE_SET HEADERS
        BASE_DIRS "fancyqlone/include"
        FILES "fancyqlone/include/fancyqlone/matio.hpp")
    target_link_libraries(cyqlone PUBLIC matio::matio)
endif()
if (CYQLONE_WITH_ZLIB)
    target_link_libraries(cyqlone PRIVATE ZLIB::ZLIB)
endif()

# QPALM solver
# ------------------------------------------------------------------------------
if (CYQLONE_WITH_QPALM)
    add_library(qpalm
        "fancyqpalm/src/breakpoint.cpp"
        "fancyqpalm/src/qpalm.cpp"
        "fancyqpalm/src/status.cpp"
        "fancyqpalm/src/ocp-backend-cyqlone.cpp"
    )
    target_sources(qpalm PUBLIC FILE_SET HEADERS
        BASE_DIRS "fancyqpalm/include"
        FILES "fancyqpalm/include/fancyqlone/fancyqpalm/qpalm.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/status.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/solver.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/detailed-stats.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/settings.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.tpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/ineq-constr.tpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/linalg.tpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/linesearch.tpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/solve.tpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/implementation/algorithms.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/implementation/breakpoint.hpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/implementation/breakpoint.tpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/implementation/linesearch.tpp"
              "fancyqpalm/include/fancyqlone/fancyqpalm/implementation/solver.tpp"
    )
    target_link_libraries(qpalm PUBLIC cyqlone::cyqlone)
    cyqlone_configure_library(qpalm EXPORT_PREFIX cyqlone HEADER_SUBDIR fancyqpalm)
    if (CYQLONE_WITH_SKA_SORT)
        find_package(ska-sort REQUIRED)
        target_link_libraries(qpalm PUBLIC ska-sort::ska-sort)
        target_compile_definitions(qpalm PUBLIC CYQLONE_WITH_SKA_SORT)
    endif()

    # Example problems
    if (CYQLONE_WITH_EXAMPLE_PROBLEMS)
        find_package(Eigen3 REQUIRED)
        add_library(example-problems
            "example-problems/src/centroidal-quadruped.cpp"
            "example-problems/src/csv.cpp"
            "example-problems/src/platooning.cpp"
            "example-problems/src/spring-mass.cpp"
        )
        target_sources(example-problems PUBLIC FILE_SET HEADERS
            BASE_DIRS "example-problems/include"
            FILES     "example-problems/include/fancyqlone/fancyqpalm/example-problems/centroidal-quadruped.hpp"
                      "example-problems/include/fancyqlone/fancyqpalm/example-problems/platooning.hpp"
                      "example-problems/include/fancyqlone/fancyqpalm/example-problems/zoh.hpp"
                      "example-problems/include/fancyqlone/fancyqpalm/example-problems/csv.hpp"
                      "example-problems/include/fancyqlone/fancyqpalm/example-problems/spring-mass.hpp"
        )
        target_link_libraries(example-problems
            PUBLIC cyqlone::cyqlone Eigen3::Eigen guanaqo::guanaqo guanaqo::blas)
        cyqlone_configure_library(example-problems EXPORT_PREFIX cyqlone)
    endif()
endif()

# ==============================================================================

# Save the project version to a generated file
configure_file("cmake/cyqlone-version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/cyqlone-version.h" @ONLY)
target_sources(cyqlone PUBLIC FILE_SET HEADERS
    BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/include"
    FILES "${CMAKE_CURRENT_BINARY_DIR}/include/cyqlone-version.h"
)

# Build time
set(CYQLONE_BUILD_TIME_CPP "${CMAKE_CURRENT_BINARY_DIR}/cyqlone-build-time.cpp")
if (CYQLONE_WITH_ACCURATE_BUILD_TIME)
    add_custom_target(cyqlone-build-time-generate
        BYPRODUCTS ${CYQLONE_BUILD_TIME_CPP}
        COMMAND ${CMAKE_COMMAND}
            -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildTime.cmake"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    target_sources(cyqlone PRIVATE ${CYQLONE_BUILD_TIME_CPP})
    add_dependencies(cyqlone cyqlone-build-time-generate)
else()
    include(cmake/BuildTime.cmake)
    set(CYQLONE_BUILD_TIME "${CYQLONE_BUILD_TIME}" CACHE STRING
        "Build time to embed in the library. Consider using SOURCE_DATE_EPOCH instead of setting this directly.")
    unset(CYQLONE_BUILD_TIME) # Keep only the cache variable
    target_sources(cyqlone PRIVATE ${CYQLONE_BUILD_TIME_CPP})
endif()

# Installation
include(cmake/Install.cmake)
