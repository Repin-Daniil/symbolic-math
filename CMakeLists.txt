cmake_minimum_required(VERSION 3.22)
project(Math)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_library(SYMCPP STATIC
        src/symcpp.h

        src/symcpp/abstract-syntax-tree/node.h
        src/symcpp/abstract-syntax-tree/operations/unary_operation.h
        src/symcpp/abstract-syntax-tree/operations/unary_operation.cpp
        src/symcpp/abstract-syntax-tree/operations/binary_operation.h
        src/symcpp/abstract-syntax-tree/operations/binary_operation.cpp

        src/symcpp/abstract-syntax-tree/operands/number_node.h
        src/symcpp/abstract-syntax-tree/operands/number_node.cpp
        src/symcpp/abstract-syntax-tree/operands/variable_node.h
        src/symcpp/abstract-syntax-tree/operands/variable_node.cpp
        src/symcpp/abstract-syntax-tree/operands/constant_node.h
        src/symcpp/abstract-syntax-tree/operands/constant_node.cpp

        src/symcpp/abstract-syntax-tree/operations/binary/addition.h
        src/symcpp/abstract-syntax-tree/operations/binary/addition.cpp
        src/symcpp/abstract-syntax-tree/operations/binary/multiplication.h
        src/symcpp/abstract-syntax-tree/operations/binary/multiplication.cpp
        src/symcpp/abstract-syntax-tree/operations/binary/subtraction.h
        src/symcpp/abstract-syntax-tree/operations/binary/subtraction.cpp
        src/symcpp/abstract-syntax-tree/operations/binary/division.h
        src/symcpp/abstract-syntax-tree/operations/binary/division.cpp
        src/symcpp/abstract-syntax-tree/operations/binary/exponentiation.h
        src/symcpp/abstract-syntax-tree/operations/binary/exponentiation.cpp

        src/symcpp/abstract-syntax-tree/operations/unary/logarithm.h
        src/symcpp/abstract-syntax-tree/operations/unary/logarithm.cpp
        src/symcpp/abstract-syntax-tree/operations/unary/cos.h
        src/symcpp/abstract-syntax-tree/operations/unary/cos.cpp
        src/symcpp/abstract-syntax-tree/operations/unary/sin.h
        src/symcpp/abstract-syntax-tree/operations/unary/sin.cpp
        src/symcpp/abstract-syntax-tree/operations/unary/sqrt.h
        src/symcpp/abstract-syntax-tree/operations/unary/sqrt.cpp
        src/symcpp/abstract-syntax-tree/operations/unary/tangent.h
        src/symcpp/abstract-syntax-tree/operations/unary/tangent.cpp
        src/symcpp/abstract-syntax-tree/operations/unary/unary_minus.h
        src/symcpp/abstract-syntax-tree/operations/unary/unary_minus.cpp

        src/symcpp/constants_storage.h

        src/symcpp/expression.h
        src/symcpp/expression.cpp
        src/symcpp/symbol.h
        src/symcpp/symbol.cpp
        src/symcpp/number.h
        src/symcpp/number.cpp

        src/symcpp/utils/converter/converter.h
        src/symcpp/utils/converter/converter.cpp

        src/symcpp/utils/helper/helper.h
        src/symcpp/utils/helper/helper.cpp

        src/symcpp/utils/parser/ast_builder.h
        src/symcpp/utils/parser/ast_builder.cpp

        src/symcpp/stack_calc/calculator.h
        src/symcpp/stack_calc/calculator.cpp
)

# Samples
add_executable(calculator tools/main_calc.cpp
        samples/stack_calculator/app/application.h
        samples/stack_calculator/app/application.cpp)

add_executable(lib_test tools/main_lib.cpp)
add_executable(simple samples/simple/simple.cpp)
add_executable(tangent_builder samples/tangent_builder/tangent_builder.cpp)
add_executable(interactive_calc samples/interactive/interactive.cpp)

target_link_libraries(lib_test PRIVATE SYMCPP)
target_link_libraries(calculator PRIVATE SYMCPP)
target_link_libraries(simple PRIVATE SYMCPP)
target_link_libraries(tangent_builder PRIVATE SYMCPP)
target_link_libraries(interactive_calc PRIVATE SYMCPP)

# Tests
enable_testing()

add_executable(rpn_test tests/calculator_test.cpp tests/catch.hpp)
add_executable(converter_test tests/converter_test.cpp tests/catch.hpp)
#add_executable(app_test tests/application_test.cpp samples/app/application.h samples/app/application.cpp tests/catch.hpp)
add_executable(expression_test tests/operands_test.cpp tests/binary_operations_test.cpp tests/unary_operations_test.cpp
        #        tests/ast_test.cpp
        tests/catch.hpp)

target_link_libraries(rpn_test PRIVATE SYMCPP)
target_link_libraries(converter_test PRIVATE SYMCPP)
#target_link_libraries(app_test PRIVATE SYMCPP)
target_link_libraries(expression_test PRIVATE SYMCPP)

add_test(NAME RPN_TEST COMMAND rpn_test)
add_test(NAME CONVERTER_TEST COMMAND converter_test)
#add_test(NAME APPLICATION_TEST COMMAND app_test)
add_test(NAME EXPRESSIONS_TEST COMMAND expression_test)
