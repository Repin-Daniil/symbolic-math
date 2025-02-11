cmake_minimum_required(VERSION 3.22)
project(Math)

set(CMAKE_CXX_STANDARD 20)

add_library(SYMCPP STATIC
        src/expression.cpp
        src/symbol.cpp
        src/number.cpp

        src/core/abstract-syntax-tree/operations/unary_operation.cpp
        src/core/abstract-syntax-tree/operations/binary_operation.cpp

        src/core/abstract-syntax-tree/operands/number_node.cpp
        src/core/abstract-syntax-tree/operands/variable_node.cpp
        src/core/abstract-syntax-tree/operands/constant_node.cpp

        src/core/abstract-syntax-tree/operations/binary/addition.cpp
        src/core/abstract-syntax-tree/operations/binary/multiplication.cpp
        src/core/abstract-syntax-tree/operations/binary/subtraction.cpp
        src/core/abstract-syntax-tree/operations/binary/division.cpp
        src/core/abstract-syntax-tree/operations/binary/exponentiation.cpp

        src/core/abstract-syntax-tree/operations/unary/logarithm.cpp
        src/core/abstract-syntax-tree/operations/unary/cos.cpp
        src/core/abstract-syntax-tree/operations/unary/sin.cpp
        src/core/abstract-syntax-tree/operations/unary/sqrt.cpp
        src/core/abstract-syntax-tree/operations/unary/tangent.cpp
        src/core/abstract-syntax-tree/operations/unary/unary_minus.cpp

        src/utils/converter/converter.cpp
        src/utils/helper/helper.cpp
        src/utils/parser/ast_builder.cpp
        src/core/engine/stack_calc/calculator.cpp
        src/utils/logger/log.cpp
)

target_include_directories(SYMCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#FIXME remove public src


add_executable(simple samples/simple.cpp)
add_executable(basic samples/basic.cpp)
add_executable(tangent_builder samples/tangent_builder.cpp)
add_executable(interactive_calc samples/interactive.cpp)


target_link_libraries(simple PRIVATE SYMCPP)
target_link_libraries(basic PRIVATE SYMCPP)
target_link_libraries(tangent_builder PRIVATE SYMCPP)
target_link_libraries(interactive_calc PRIVATE SYMCPP)

# Tests
enable_testing()

add_executable(rpn_test tests/math/stack_machine.cpp tests/catch.hpp)
add_executable(converter_test tests/utils/converter_test.cpp tests/catch.hpp)
add_executable(logger_test tests/utils/logger_test.cpp tests/catch.hpp)

#add_executable(derivative_test tests/math/derivative.cpp tests/catch.hpp)
add_executable(math_test tests/math/basic_test.cpp tests/catch.hpp)
#add_executable(simplification_test tests/math/simplification.cpp tests/catch.hpp)
#add_executable(api_test tests/api/expression_test.cpp
#        tests/api/symbol_test.cpp
#tests/api/expression_test.cpp
#        tests/api/number_test.cpp tests/catch.hpp)

add_library(SYMCPP_TEST INTERFACE)
target_include_directories(SYMCPP_TEST INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(SYMCPP_TEST INTERFACE SYMCPP)

target_link_libraries(rpn_test PRIVATE SYMCPP_TEST)
target_link_libraries(converter_test PRIVATE SYMCPP_TEST)
target_link_libraries(logger_test PRIVATE SYMCPP_TEST)
target_link_libraries(math_test PRIVATE SYMCPP_TEST)

target_link_libraries(rpn_test PRIVATE SYMCPP)
target_link_libraries(converter_test PRIVATE SYMCPP)
target_link_libraries(logger_test PRIVATE SYMCPP)
target_link_libraries(math_test PRIVATE SYMCPP)
#target_link_libraries(derivative_test PRIVATE SYMCPP)
#target_link_libraries(simplification_test PRIVATE SYMCPP)
#target_link_libraries(api_test PRIVATE SYMCPP)

add_test(NAME RPN_TEST COMMAND rpn_test)
add_test(NAME CONVERTER_TEST COMMAND converter_test)
add_test(NAME LOGGER_TEST COMMAND logger_test)
add_test(NAME MATH_TEST COMMAND math_test)
#add_test(NAME DERIVATIVE_TEST COMMAND derivative_test)
#add_test(NAME SIMPLIFICATION_TEST COMMAND simplification_test)
#add_test(NAME API_TEST COMMAND api_test)


