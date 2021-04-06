# require a minimum version of cmake
cmake_minimum_required(VERSION 3.10)

# set(CMAKE_CXX_COMPILER "g++")
project(murphi LANGUAGES CXX VERSION 1.0 DESCRIPTION "murphi generator c++ library" )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/703bd9caab50b139428cea1aaff9974ebee5742e.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# include gnu dirs
include(GNUInstallDirs)

# add the library
add_library(murphi SHARED src/murphi.cpp)

# set the properties to export version and pupblic header for api
set_target_properties(murphi PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 PUBLIC_HEADER include/murphi.h)

# configure file
configure_file(murphi.pc.in murphi.pc @ONLY)

# setup the include directories
target_include_directories(murphi PRIVATE include)



# generate an install rule
install(TARGETS murphi 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/murphi.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


## Testing
enable_testing()

add_executable(
  murphi-test
  tests/murphi.cpp
)

target_include_directories(murphi-test PRIVATE include)

target_link_libraries(
    murphi-test
    murphi
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(murphi-test)