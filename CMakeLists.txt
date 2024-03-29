cmake_minimum_required(VERSION 3.22)
project(RPN CXX)

set(CMAKE_CXX_STANDARD 20)


#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

include_directories(src)

add_library(RPN_LIB
        src/calc/calculator.h
        src/calc/calculator.cpp
        src/infrastructure/converter/converter.h
        src/infrastructure/converter/converter.cpp
        src/constants_storage.h
        src/calc/parser/parser.cpp
        src/calc/parser/parser.h)

add_executable(calc src/main.cpp
        src/app/application.cpp
        src/app/application.h)

target_link_libraries(calc PRIVATE RPN_LIB)

# Tests
#enable_testing()
#add_executable(rpn_test tests/calculator_test.cpp)
#add_executable(converter_test tests/converter_test.cpp)
#
#target_link_libraries(rpn_test PRIVATE RPN_LIB CONAN_PKG::catch2)
#target_link_libraries(converter_test PRIVATE RPN_LIB CONAN_PKG::catch2)
#
#add_test(NAME RPN_TEST COMMAND rpn_test)
#add_test(NAME CONVERTER_TEST COMMAND converter_test)
