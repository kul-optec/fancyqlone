cmake_minimum_required(VERSION 3.24)
project(qpoases_e LANGUAGES C)

option(QPOASES_WITH_BLAS "Use external BLAS and LAPACK" OFF)
option(QPOASES_WITH_MKL "Use Intel MKL" OFF)
option(QPOASES_WITH_OPENBLAS "Use OpenBLAS" OFF)
set(QPOASES_BLAS_INDEX_TYPE "long long" CACHE STRING "BLAS integer type")

add_library(qpOASES_e
    src/Bounds.c
    src/Constraints.c
    src/Flipper.c
    src/Indexlist.c
    src/Matrices.c
    src/MessageHandling.c
    src/Options.c
    src/OQPinterface.c
    src/QProblem.c
    src/QProblemB.c
    src/Utils.c)
add_library(qpoases-e::qpoases-e ALIAS qpOASES_e)
set_target_properties(qpOASES_e PROPERTIES EXPORT_NAME qpoases-e)
target_compile_features(qpOASES_e PUBLIC c_std_99)
target_compile_definitions(qpOASES_e PUBLIC __NO_STATIC__ PRIVATE __SUPPRESSANYOUTPUT__ __NO_COPYRIGHT__)
if(QPOASES_WITH_BLAS)
    include(cmake/BLAS.cmake)
endif()
if(WIN32)
    target_compile_definitions(qpOASES_e PRIVATE WIN32)
elseif(UNIX)
    # Upstream uses LINUX for the POSIX timer, including on macOS.
    target_compile_definitions(qpOASES_e PRIVATE LINUX)
endif()
target_sources(qpOASES_e PUBLIC FILE_SET HEADERS BASE_DIRS include FILES
    include/qpOASES_e.h
    include/qpOASES_e/Bounds.h
    include/qpOASES_e/Constants.h
    include/qpOASES_e/ConstraintProduct.h
    include/qpOASES_e/Constraints.h
    include/qpOASES_e/Flipper.h
    include/qpOASES_e/Indexlist.h
    include/qpOASES_e/Matrices.h
    include/qpOASES_e/MessageHandling.h
    include/qpOASES_e/Options.h
    include/qpOASES_e/QProblem.h
    include/qpOASES_e/QProblemB.h
    include/qpOASES_e/Types.h
    include/qpOASES_e/UnitTesting.h
    include/qpOASES_e/Utils.h
    include/qpOASES_e/extras/OQPinterface.h)
set_target_properties(qpOASES_e PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
if(UNIX)
    target_link_libraries(qpOASES_e PRIVATE m)
endif()

include(GNUInstallDirs)
install(TARGETS qpOASES_e EXPORT qpoases-e-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT qpoases-e-targets NAMESPACE qpoases-e::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qpoases-e)
include(CMakePackageConfigHelpers)
configure_package_config_file(qpoases-e-config.cmake.in qpoases-e-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qpoases-e)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qpoases-e-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/qpoases-e)
