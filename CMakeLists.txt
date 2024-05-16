cmake_minimum_required(VERSION 3.22)
project(Math)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_library(MATH STATIC
        src/symcpp.h

        src/math/abstract-syntax-tree/node.h
        src/math/abstract-syntax-tree/operations/unary_operation.h
        src/math/abstract-syntax-tree/operations/unary_operation.cpp
        src/math/abstract-syntax-tree/operations/binary_operation.h
        src/math/abstract-syntax-tree/operations/binary_operation.cpp

        src/math/abstract-syntax-tree/operands/number_node.h
        src/math/abstract-syntax-tree/operands/number_node.cpp
        src/math/abstract-syntax-tree/operands/variable_node.h
        src/math/abstract-syntax-tree/operands/variable_node.cpp

        src/math/abstract-syntax-tree/operations/binary/addition.h
        src/math/abstract-syntax-tree/operations/binary/addition.cpp
        src/math/abstract-syntax-tree/operations/binary/multiplication.h
        src/math/abstract-syntax-tree/operations/binary/multiplication.cpp
        src/math/abstract-syntax-tree/operations/binary/subtraction.h
        src/math/abstract-syntax-tree/operations/binary/subtraction.cpp
        src/math/abstract-syntax-tree/operations/binary/division.h
        src/math/abstract-syntax-tree/operations/binary/division.cpp
        src/math/abstract-syntax-tree/operations/binary/exponentiation.h
        src/math/abstract-syntax-tree/operations/binary/exponentiation.cpp

        src/math/abstract-syntax-tree/operations/unary/logarithm.h
        src/math/abstract-syntax-tree/operations/unary/logarithm.cpp
        src/math/abstract-syntax-tree/operations/unary/cos.h
        src/math/abstract-syntax-tree/operations/unary/cos.cpp
        src/math/abstract-syntax-tree/operations/unary/sin.h
        src/math/abstract-syntax-tree/operations/unary/sin.cpp
        src/math/abstract-syntax-tree/operations/unary/sqrt.h
        src/math/abstract-syntax-tree/operations/unary/sqrt.cpp
        src/math/abstract-syntax-tree/operations/unary/tangent.h
        src/math/abstract-syntax-tree/operations/unary/tangent.cpp
        src/math/abstract-syntax-tree/operations/unary/unary_minus.h
        src/math/abstract-syntax-tree/operations/unary/unary_minus.cpp

        src/math/constants_storage.h

        src/math/expression.h
        src/math/expression.cpp
        src/math/symbol.h
        src/math/symbol.cpp
        src/math/number.h
        src/math/number.cpp

        src/math/utils/converter/converter.h
        src/math/utils/converter/converter.cpp

        src/math/utils/helper/helper.h
        src/math/utils/helper/helper.cpp

        src/math/utils/parser/ast_builder.h
        src/math/utils/parser/ast_builder.cpp

        src/math/stack_calc/calculator.h
        src/math/stack_calc/calculator.cpp
)

# Samples
add_executable(calculator tools/main_calc.cpp
        samples/app/application.h
        samples/app/application.cpp)

add_executable(lib_test tools/main_lib.cpp)

target_link_libraries(lib_test PRIVATE MATH)
target_link_libraries(calculator PRIVATE MATH)

# Tests
enable_testing()

add_executable(rpn_test tests/calculator_test.cpp tests/catch.hpp)
add_executable(converter_test tests/converter_test.cpp tests/catch.hpp)
#add_executable(app_test tests/application_test.cpp samples/app/application.h samples/app/application.cpp tests/catch.hpp)
add_executable(expression_test tests/operands_test.cpp tests/binary_operations_test.cpp tests/unary_operations_test.cpp
        #        tests/ast_test.cpp
        tests/catch.hpp)

target_link_libraries(rpn_test PRIVATE MATH)
target_link_libraries(converter_test PRIVATE MATH)
#target_link_libraries(app_test PRIVATE MATH)
target_link_libraries(expression_test PRIVATE MATH)

add_test(NAME RPN_TEST COMMAND rpn_test)
add_test(NAME CONVERTER_TEST COMMAND converter_test)
#add_test(NAME APPLICATION_TEST COMMAND app_test)
add_test(NAME EXPRESSIONS_TEST COMMAND expression_test)
