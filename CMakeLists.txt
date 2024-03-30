cmake_minimum_required(VERSION 3.22)
project(RPN CXX)

set(CMAKE_CXX_STANDARD 20)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories(src)

add_library(RPN_LIB
        src/constants_storage.h

        src/calc/calculator.h
        src/calc/calculator.cpp

        src/utils/converter/converter.h
        src/utils/converter/converter.cpp

        src/utils/helper/helper.h
        src/utils/helper/helper.cpp)

add_executable(calc src/main.cpp
        src/app/application.cpp
        src/app/application.h)

target_link_libraries(calc PRIVATE RPN_LIB)

# Tests
enable_testing()
add_executable(rpn_test tests/calculator_test.cpp)
add_executable(converter_test tests/converter_test.cpp)
add_executable(app_test tests/application_test.cpp src/app/application.h src/app/application.cpp)

target_link_libraries(rpn_test PRIVATE RPN_LIB CONAN_PKG::catch2)
target_link_libraries(converter_test PRIVATE RPN_LIB CONAN_PKG::catch2)
target_link_libraries(app_test PRIVATE RPN_LIB CONAN_PKG::catch2)

add_test(NAME RPN_TEST COMMAND rpn_test)
add_test(NAME CONVERTER_TEST COMMAND converter_test)
add_test(NAME APPLICATION_TEST COMMAND app_test)
