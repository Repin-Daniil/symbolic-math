cmake_minimum_required(VERSION 3.22)
project(RPN CXX)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include_directories(src)

add_library(RPN_LIB
        src/constants_storage.h

        src/math/calc/calculator.h
        src/math/calc/calculator.cpp

        src/utils/converter/converter.h
        src/utils/converter/converter.cpp

        src/utils/helper/helper.h
        src/utils/helper/helper.cpp
)

add_library(OPERATIONS_LIB
        src/math/algebra/algebra.h
        src/math/algebra/algebra.cpp

        src/utils/abstract-syntax-tree/ast.h
        src/utils/abstract-syntax-tree/ast.cpp

        src/math/algebra/expressions/expression.h
        src/math/algebra/expressions/operations/unary_operation.h
        src/math/algebra/expressions/operations/unary_operation.cpp
        src/math/algebra/expressions/operations/binary_operation.h
        src/math/algebra/expressions/operations/binary_operation.cpp

        src/math/algebra/expressions/operands/number.h
        src/math/algebra/expressions/operands/number.cpp
        src/math/algebra/expressions/operands/variable.h
        src/math/algebra/expressions/operands/variable.cpp

        src/math/algebra/expressions/operations/binary/addition.h
        src/math/algebra/expressions/operations/binary/addition.cpp
        src/math/algebra/expressions/operations/binary/multiplication.h
        src/math/algebra/expressions/operations/binary/multiplication.cpp
        src/math/algebra/expressions/operations/binary/substraction.h
        src/math/algebra/expressions/operations/binary/substraction.cpp
        src/math/algebra/expressions/operations/binary/division.h
        src/math/algebra/expressions/operations/binary/division.cpp
        src/math/algebra/expressions/operations/binary/exponentiation.h
        src/math/algebra/expressions/operations/binary/exponentiation.cpp

        src/math/algebra/expressions/operations/unary/logarithm.h
        src/math/algebra/expressions/operations/unary/logarithm.cpp
        src/math/algebra/expressions/operations/unary/cos.h
        src/math/algebra/expressions/operations/unary/cos.cpp
        src/math/algebra/expressions/operations/unary/sin.h
        src/math/algebra/expressions/operations/unary/sin.cpp
        src/math/algebra/expressions/operations/unary/sqrt.h
        src/math/algebra/expressions/operations/unary/sqrt.cpp
        src/math/algebra/expressions/operations/unary/tan.h
        src/math/algebra/expressions/operations/unary/tan.cpp
        src/math/algebra/expressions/operations/unary/unary_minus.h
        src/math/algebra/expressions/operations/unary/unary_minus.cpp
)

add_executable(calc src/main.cpp
        src/app/application.cpp
        src/app/application.h)

target_link_libraries(calc PRIVATE RPN_LIB)
target_link_libraries(calc PRIVATE OPERATIONS_LIB)

# Tests
enable_testing()

add_executable(rpn_test tests/calculator_test.cpp)
add_executable(converter_test tests/converter_test.cpp)
add_executable(app_test tests/application_test.cpp src/app/application.h src/app/application.cpp)
add_executable(expression_test tests/operands_test.cpp tests/binary_operations_test.cpp tests/unary_operations_test.cpp)

target_link_libraries(rpn_test PRIVATE RPN_LIB CONAN_PKG::catch2)
target_link_libraries(converter_test PRIVATE RPN_LIB CONAN_PKG::catch2)
target_link_libraries(app_test PRIVATE RPN_LIB OPERATIONS_LIB CONAN_PKG::catch2)
target_link_libraries(expression_test PRIVATE OPERATIONS_LIB CONAN_PKG::catch2)

add_test(NAME RPN_TEST COMMAND rpn_test)
add_test(NAME CONVERTER_TEST COMMAND converter_test)
add_test(NAME APPLICATION_TEST COMMAND app_test)
add_test(NAME EXPRESSIONS_TEST COMMAND expression_test)
