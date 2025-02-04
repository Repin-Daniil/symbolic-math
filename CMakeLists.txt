cmake_minimum_required(VERSION 3.22)
project(Math)

set(CMAKE_CXX_STANDARD 20)

include_directories(symcpp)

add_library(SYMCPP STATIC
        symcpp/symcpp.h

        symcpp/constants_storage.h

        symcpp/expression.h
        symcpp/expression.cpp
        symcpp/symbol.h
        symcpp/symbol.cpp
        symcpp/number.h
        symcpp/number.cpp

        symcpp/core/abstract-syntax-tree/node.h
        symcpp/core/abstract-syntax-tree/operations/unary_operation.h
        symcpp/core/abstract-syntax-tree/operations/unary_operation.cpp
        symcpp/core/abstract-syntax-tree/operations/binary_operation.h
        symcpp/core/abstract-syntax-tree/operations/binary_operation.cpp

        symcpp/core/abstract-syntax-tree/operands/number_node.h
        symcpp/core/abstract-syntax-tree/operands/number_node.cpp
        symcpp/core/abstract-syntax-tree/operands/variable_node.h
        symcpp/core/abstract-syntax-tree/operands/variable_node.cpp
        symcpp/core/abstract-syntax-tree/operands/constant_node.h
        symcpp/core/abstract-syntax-tree/operands/constant_node.cpp

        symcpp/core/abstract-syntax-tree/operations/binary/addition.h
        symcpp/core/abstract-syntax-tree/operations/binary/addition.cpp
        symcpp/core/abstract-syntax-tree/operations/binary/multiplication.h
        symcpp/core/abstract-syntax-tree/operations/binary/multiplication.cpp
        symcpp/core/abstract-syntax-tree/operations/binary/subtraction.h
        symcpp/core/abstract-syntax-tree/operations/binary/subtraction.cpp
        symcpp/core/abstract-syntax-tree/operations/binary/division.h
        symcpp/core/abstract-syntax-tree/operations/binary/division.cpp
        symcpp/core/abstract-syntax-tree/operations/binary/exponentiation.h
        symcpp/core/abstract-syntax-tree/operations/binary/exponentiation.cpp

        symcpp/core/abstract-syntax-tree/operations/unary/logarithm.h
        symcpp/core/abstract-syntax-tree/operations/unary/logarithm.cpp
        symcpp/core/abstract-syntax-tree/operations/unary/cos.h
        symcpp/core/abstract-syntax-tree/operations/unary/cos.cpp
        symcpp/core/abstract-syntax-tree/operations/unary/sin.h
        symcpp/core/abstract-syntax-tree/operations/unary/sin.cpp
        symcpp/core/abstract-syntax-tree/operations/unary/sqrt.h
        symcpp/core/abstract-syntax-tree/operations/unary/sqrt.cpp
        symcpp/core/abstract-syntax-tree/operations/unary/tangent.h
        symcpp/core/abstract-syntax-tree/operations/unary/tangent.cpp
        symcpp/core/abstract-syntax-tree/operations/unary/unary_minus.h
        symcpp/core/abstract-syntax-tree/operations/unary/unary_minus.cpp

        symcpp/utils/converter/converter.h
        symcpp/utils/converter/converter.cpp

        symcpp/utils/helper/helper.h
        symcpp/utils/helper/helper.cpp

        symcpp/utils/parser/ast_builder.h
        symcpp/utils/parser/ast_builder.cpp

        symcpp/core/engine/stack_calc/calculator.h
        symcpp/core/engine/stack_calc/calculator.cpp
)

add_executable(simple samples/simple/simple.cpp)
add_executable(basic samples/basic/basic.cpp)
add_executable(tangent_builder samples/tangent_builder/tangent_builder.cpp)
add_executable(interactive_calc samples/interactive/interactive.cpp)

target_link_libraries(simple PRIVATE SYMCPP)
target_link_libraries(basic PRIVATE SYMCPP)
target_link_libraries(tangent_builder PRIVATE SYMCPP)
target_link_libraries(interactive_calc PRIVATE SYMCPP)

# Tests
enable_testing()

add_executable(rpn_test tests/math/stack_machine.cpp tests/catch.hpp)
add_executable(converter_test tests/utils/converter_test.cpp tests/catch.hpp)
#add_executable(derivative_test tests/math/derivative.cpp tests/catch.hpp)
add_executable(math_test tests/math/basic_test.cpp tests/catch.hpp)
#add_executable(simplification_test tests/math/simplification.cpp tests/catch.hpp)
#add_executable(api_test tests/api/expression_test.cpp
#        tests/api/symbol_test.cpp
#tests/api/expression_test.cpp
#        tests/api/number_test.cpp tests/catch.hpp)

target_link_libraries(rpn_test PRIVATE SYMCPP)
target_link_libraries(converter_test PRIVATE SYMCPP)
target_link_libraries(math_test PRIVATE SYMCPP)
#target_link_libraries(derivative_test PRIVATE SYMCPP)
#target_link_libraries(simplification_test PRIVATE SYMCPP)
#target_link_libraries(api_test PRIVATE SYMCPP)

add_test(NAME RPN_TEST COMMAND rpn_test)
add_test(NAME CONVERTER_TEST COMMAND converter_test)
add_test(NAME MATH_TEST COMMAND math_test)
#add_test(NAME DERIVATIVE_TEST COMMAND derivative_test)
#add_test(NAME SIMPLIFICATION_TEST COMMAND simplification_test)
#add_test(NAME API_TEST COMMAND api_test)


