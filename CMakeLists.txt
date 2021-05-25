# require a minimum version of cmake
cmake_minimum_required(VERSION 3.15)

project(murphi LANGUAGES CXX VERSION 1.0 DESCRIPTION "murphi generator c++ library")

set(DEFAULT_BUILD_TYPE "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## not include this in release version
if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release"))
    message(STATUS "build type is ${CMAKE_BUILD_TYPE}")
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/703bd9caab50b139428cea1aaff9974ebee5742e.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    # include gnu dirs
    include(GNUInstallDirs)
endif ()


set(SOURCE_FILES
        src/murphi.cpp
        src/models/ConstDecl.cpp
        src/models/Decl.cpp
        src/models/Expr.cpp
        src/models/Formal.cpp
        src/models/TypeDecl.cpp
        src/models/TypeExpr.cpp
        src/models/VarDecl.cpp

        src/utils/PrintUtils.cpp

        src/proc/ProcDecl.cpp
        src/proc/Statements.cpp

        src/rules/rules.cpp
        )

# add the library
add_library(${PROJECT_NAME} SHARED
        ${SOURCE_FILES}
        )

# set the properties to export version and pupblic header for api
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 PUBLIC_HEADER include/murphi.h)

# configure file
configure_file(murphi.pc.in murphi.pc @ONLY)

# setup the include directories
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)


# generate an install rule
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

install(FILES ${CMAKE_BINARY_DIR}/murphi.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


## Testing -- only in non release builds
if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release"))
    enable_testing()

    add_executable(
            murphi-test
            tests/module-test.cpp
            tests/statements-test.cpp
            tests/designator-test.cpp
            tests/printutils-test.cpp
            tests/typeexpr-test.cpp
            tests/expr-test.cpp
            tests/rules-test.cpp
            tests/decls-test.cpp
    )

    target_include_directories(murphi-test PRIVATE include)

    target_link_libraries(
            murphi-test
            murphi
            gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(murphi-test)

endif ()