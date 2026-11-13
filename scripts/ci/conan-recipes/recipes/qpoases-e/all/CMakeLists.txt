cmake_minimum_required(VERSION 3.24)
project(qpoases_e LANGUAGES C)

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
target_compile_features(qpOASES_e PUBLIC c_std_99)
target_compile_definitions(qpOASES_e PUBLIC __NO_STATIC__ PRIVATE __SUPPRESSANYOUTPUT__ __NO_COPYRIGHT__)
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
install(TARGETS qpOASES_e
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
