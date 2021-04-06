# Murphi C++ Library

## Description

This is a C++ Library to generate Murphi code from C++

## Prerequisites

- C++ compiler, support for c++14 or higher
- CMake version 3.10 or greater

## Build and Run

- Clone the repository - `git clone https://github.com/veselypeta/murphi-lib.git`
- `cd murphi-lib`
- Create a build directory - `mkdir build && cd build`
- Run CMake to generate build files, tested with Ninja but other will likely work `cmake -G Ninja ..`
- Build the library `cmake --build .`
- (optional) Install the library `cmake --install`


## Test

The Library uses `googletest` for the unit testing framework. To run the tests, simply run `ctest` from inside the build directory.