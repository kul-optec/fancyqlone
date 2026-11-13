cmake_minimum_required(VERSION 3.24)
project(treeqp LANGUAGES C CXX)

find_package(blasfeo CONFIG REQUIRED)
find_package(hpipm CONFIG REQUIRED)
find_package(qpoases-e CONFIG REQUIRED)
option(TREEQP_WITH_OPENMP "Enable OpenMP parallelism" OFF)
if(TREEQP_WITH_OPENMP)
    find_package(OpenMP REQUIRED COMPONENTS C)
endif()

add_library(treeqp
    treeqp/src/tree_qp_common.c
    treeqp/src/dual_Newton_common.c
    treeqp/src/dual_Newton_scenarios.c
    treeqp/src/dual_Newton_tree.c
    treeqp/src/dual_Newton_tree_clipping.c
    treeqp/src/dual_Newton_tree_qpoases.c
    treeqp/src/hpmpc_tree.c
    treeqp/src/hpipm_tree.c
    treeqp/utils/blasfeo.c
    treeqp/utils/memory.c
    treeqp/utils/profiling.c
    treeqp/utils/print.c
    treeqp/utils/timing.c
    treeqp/utils/tree.c
    treeqp/utils/utils.c)
add_library(treeqp::treeqp ALIAS treeqp)
target_compile_features(treeqp PUBLIC c_std_99)
target_compile_definitions(treeqp PUBLIC PROFILE=0 PRIVATE PRINT_LEVEL=0 NREP=1)
# SAVE_DATA and DEBUGGING_ENABLED use #ifdef, so leave them undefined.
if(TREEQP_WITH_OPENMP)
    target_compile_definitions(treeqp PRIVATE PARALLEL)
    target_link_libraries(treeqp PRIVATE OpenMP::OpenMP_C)
endif()
target_sources(treeqp PUBLIC FILE_SET HEADERS BASE_DIRS . FILES
    treeqp/src/tree_qp_common.h
    treeqp/src/dual_Newton_common.h
    treeqp/src/dual_Newton_scenarios.h
    treeqp/src/dual_Newton_tree.h
    treeqp/src/dual_Newton_tree_clipping.h
    treeqp/src/dual_Newton_tree_qpoases.h
    treeqp/src/hpmpc_tree.h
    treeqp/src/hpipm_tree.h
    treeqp/utils/blasfeo.h
    treeqp/utils/memory.h
    treeqp/utils/profiling.h
    treeqp/utils/print.h
    treeqp/utils/timing.h
    treeqp/utils/tree.h
    treeqp/utils/types.h
    treeqp/utils/utils.h)
target_link_libraries(treeqp PUBLIC blasfeo hpipm qpoases-e::qpoases-e)
if(UNIX)
    target_link_libraries(treeqp PRIVATE m)
endif()

add_library(treeqp_cpp_interface interfaces/treeqp_cpp/treeqp_cpp_interface.cpp)
add_library(treeqp::cpp ALIAS treeqp_cpp_interface)
set_target_properties(treeqp_cpp_interface PROPERTIES EXPORT_NAME cpp)
target_compile_features(treeqp_cpp_interface PUBLIC cxx_std_11)
target_sources(treeqp_cpp_interface PUBLIC FILE_SET HEADERS BASE_DIRS . FILES
    interfaces/treeqp_cpp/treeqp_cpp_interface.hpp)
target_link_libraries(treeqp_cpp_interface PUBLIC treeqp)

set_target_properties(treeqp treeqp_cpp_interface PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)
install(TARGETS treeqp treeqp_cpp_interface EXPORT treeqp-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT treeqp-targets NAMESPACE treeqp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/treeqp)
include(CMakePackageConfigHelpers)
configure_package_config_file(treeqp-config.cmake.in treeqp-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/treeqp)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/treeqp-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/treeqp)
