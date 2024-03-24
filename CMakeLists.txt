cmake_minimum_required(VERSION 3.22)
project(RPN CXX)

set(CMAKE_CXX_STANDARD 20)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

add_library(RPN_LIB
        src/calculator.h
        src/calculator.cpp
        src/constants_storage.h)

add_executable(calc src/main.cpp)
target_link_libraries(calc PRIVATE RPN_LIB)

# Tests

