cmake_minimum_required(VERSION 3.22)
project(RPN CXX)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories(src)

add_library(LIBRARY
        src/constants_storage.h

        src/math/calc/calculator.h
        src/math/calc/calculator.cpp

        src/utils/converter/converter.h
        src/utils/converter/converter.cpp

        src/utils/helper/helper.h
        src/utils/helper/helper.cpp
        src/math/algebra/algebra.cpp
        src/math/algebra/algebra.h
        src/math/algebra/expression.h
        src/math/algebra/expressions/operands/number.cpp
        src/math/algebra/expressions/operands/number.h
        src/math/algebra/expressions/operands/variable.cpp
        src/math/algebra/expressions/operands/variable.h
        src/math/algebra/expressions/operations/binary/addition.cpp
        src/math/algebra/expressions/operations/binary/addition.h
        src/utils/abstract-syntax-tree/ast.cpp
        src/utils/abstract-syntax-tree/ast.h
        src/math/algebra/expressions/operations/unary-operation.h
        src/math/algebra/expressions/operations/binary-operation.h
        src/math/algebra/expressions/operations/unary-operation.cpp
        src/math/algebra/expressions/operations/binary-operation.cpp
        src/math/algebra/expressions/operations/binary/multiplication.cpp
        src/math/algebra/expressions/operations/binary/multiplication.h
        src/math/algebra/expressions/operations/binary/substraction.cpp
        src/math/algebra/expressions/operations/binary/substraction.h
        src/math/algebra/expressions/operations/binary/division.cpp
        src/math/algebra/expressions/operations/binary/division.h
        src/math/algebra/expressions/operations/binary/exponentiation.cpp
        src/math/algebra/expressions/operations/binary/exponentiation.h
        src/math/algebra/expressions/operations/unary/logarithm.cpp
        src/math/algebra/expressions/operations/unary/logarithm.h)

add_executable(calc src/main.cpp
        src/app/application.cpp
        src/app/application.h)

target_link_libraries(calc PRIVATE LIBRARY)

# Tests
enable_testing()

add_executable(rpn_test tests/calculator_test.cpp)
add_executable(converter_test tests/converter_test.cpp)
add_executable(app_test tests/application_test.cpp src/app/application.h src/app/application.cpp)

target_link_libraries(rpn_test PRIVATE LIBRARY CONAN_PKG::catch2)
target_link_libraries(converter_test PRIVATE LIBRARY CONAN_PKG::catch2)
target_link_libraries(app_test PRIVATE LIBRARY CONAN_PKG::catch2)

add_test(NAME RPN_TEST COMMAND rpn_test)
add_test(NAME CONVERTER_TEST COMMAND converter_test)
add_test(NAME APPLICATION_TEST COMMAND app_test)
