# Murphi C++ Library

## Description

This is a C++ Library to generate Murphi code from C++

## Prerequisites

- C++ compiler, support for c++14 or higher
- CMake version 3.15 or greater

## Build and Run

- Clone the repository - `git clone https://github.com/veselypeta/murphi-lib.git`
- `cd murphi-lib`
- Create a build directory - `mkdir build && cd build`
- Run CMake to generate build files, tested with Ninja but other will likely work `cmake -G Ninja ..`
- Build the library `cmake --build .`
- (optional) Install the library `cmake --install`


## Test

The Library uses `googletest` for the unit testing framework. 

To run the tests, simply run `ctest` from inside the build directory.

## Murphi
We are targeting CMurphi from the following repository: https://bitbucket.org/Nik-U/cmurphi/src/master/

Full syntax of Murphi is outlined here: https://www.cs.ubc.ca/~ajh/courses/cpsc513/assign-token/User.Manual