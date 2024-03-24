cmake_minimum_required(VERSION 3.22)
project(RPN CXX)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories(src)

add_library(RPN_LIB
        src/calculator.h
        src/calculator.cpp
        src/constants_storage.h)

add_executable(calc src/main.cpp)
target_link_libraries(calc PRIVATE RPN_LIB)

# Tests
enable_testing()
add_executable(calc_test tests/calculator_test.cpp)
target_link_libraries(calc_test PRIVATE RPN_LIB CONAN_PKG::catch2)
add_test(NAME CALCULATOR_TEST COMMAND calc_test)
