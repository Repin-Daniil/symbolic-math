// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"

#include "math/abstract-syntax-tree/operands/number.h"
#include "math/abstract-syntax-tree/operands/variable.h"

#include "math/abstract-syntax-tree/operations/binary/addition.h"
#include "math/abstract-syntax-tree/operations/binary/addition.h"  // check include guards
#include "math/abstract-syntax-tree/operations/binary/division.h"
#include "math/abstract-syntax-tree/operations/binary/division.h"  // check include guards
#include "math/abstract-syntax-tree/operations/binary/exponentiation.h"
#include "math/abstract-syntax-tree/operations/binary/exponentiation.h"  // check include guards
#include "math/abstract-syntax-tree/operations/binary/multiplication.h"
#include "math/abstract-syntax-tree/operations/binary/multiplication.h"  // check include guards
#include "math/abstract-syntax-tree/operations/binary/subtraction.h"
#include "math/abstract-syntax-tree/operations/binary/subtraction.h"  // check include guards

//
// TEST_CASE("2 + 5", "Addition") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand = std::make_unique<math::Number>(5);
//
//  auto addition =
//      utils::AbstractSyntaxTree(std::make_unique<math::Addition>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = addition.GetDerivative();
//
//  CHECK(addition.GetInfixExpression({}) == "7");
//  CHECK(addition.GetRPNExpression({}) == "7");
//  CHECK(addition.GetNumericResult({}) == 7);
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  CHECK(derivative.GetNumericResult({}) == 0);
//}
//
// TEST_CASE("2 + x", "Addition") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand = std::make_unique<math::Variable>('x');
//
//  auto addition =
//      utils::AbstractSyntaxTree(std::make_unique<math::Addition>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = addition.GetDerivative();
//
//  CHECK(addition.GetInfixExpression({}) == "2 + x");
//  CHECK(addition.GetRPNExpression({}) == "2 x +");
//  CHECK(addition.GetNumericResult({{'x', 5}}) == 7);
//
//  CHECK(derivative.GetInfixExpression({}) == "1");
//  CHECK(derivative.GetRPNExpression({}) == "1");
//  CHECK(derivative.GetNumericResult({}) == 1);
//}
//
// TEST_CASE("2 + (1.5 + x)", "Addition") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Number>(1.5), std::make_unique<math::Variable>('x'));
//
//  auto addition =
//      utils::AbstractSyntaxTree(std::make_unique<math::Addition>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = addition.GetDerivative();
//
//  CHECK(addition.GetInfixExpression({}) == "2 + 1.5 + x");
//  CHECK(addition.GetRPNExpression({{'x', 1}}) == "2 1.5 1 + +");
//  REQUIRE_THAT(addition.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(8.5, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1");
//  CHECK(derivative.GetRPNExpression({{'x', 1}}) == "1");
//  CHECK(derivative.GetNumericResult({}) == 1);
//}
//
// TEST_CASE("2 - 5.1", "Substraction") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand = std::make_unique<math::Number>(5.1);
//
//  auto substraction =
//      utils::AbstractSyntaxTree(std::make_unique<math::Subtraction>(std::move(left_operand),
//      std::move(right_operand)));
//  auto derivative = substraction.GetDerivative();
//
//  CHECK(substraction.GetInfixExpression({}) == "-3.1");
//  CHECK(substraction.GetRPNExpression({}) == "3.1 ~");
//  REQUIRE_THAT(substraction.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-3.1, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  CHECK(derivative.GetNumericResult({}) == 0);
//}
//
// TEST_CASE("x - 2", "Substraction") {
//  auto left_operand = std::make_unique<math::Variable>('x');
//  auto right_operand = std::make_unique<math::Number>(2);
//
//  auto substraction =
//      utils::AbstractSyntaxTree(std::make_unique<math::Subtraction>(std::move(left_operand),
//      std::move(right_operand)));
//  auto derivative = substraction.GetDerivative();
//
//  CHECK(substraction.GetInfixExpression({}) == "x - 2");
//  CHECK(substraction.GetRPNExpression({{'y', 1}}) == "x 2 -");
//  REQUIRE_THAT(substraction.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(3.5, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1");
//  CHECK(derivative.GetRPNExpression({}) == "1");
//  CHECK(derivative.GetNumericResult({}) == 1);
//}
//
// TEST_CASE("2 - (1.5 + x)", "Substraction") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Number>(1.5), std::make_unique<math::Variable>('x'));
//
//  auto substraction =
//      utils::AbstractSyntaxTree(std::make_unique<math::Subtraction>(std::move(left_operand),
//      std::move(right_operand)));
//  auto derivative = substraction.GetDerivative();
//
//  CHECK(substraction.GetInfixExpression({}) == "2 - (1.5 + x)");
//  CHECK(substraction.GetRPNExpression({}) == "2 1.5 x + -");
//  REQUIRE_THAT(substraction.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(-5, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "-1");
//  CHECK(derivative.GetRPNExpression({}) == "1 ~");
//  CHECK(derivative.GetNumericResult({}) == -1);
//}
//
// TEST_CASE("2 * 5.1", "Multiplication") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand = std::make_unique<math::Number>(5.1);
//
//  auto multiplication = utils::AbstractSyntaxTree(
//      std::make_unique<math::Multiplication>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = multiplication.GetDerivative();
//
//  CHECK(multiplication.GetInfixExpression({}) == "10.2");
//  CHECK(multiplication.GetRPNExpression({}) == "10.2");
//  REQUIRE_THAT(multiplication.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(10.2, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  CHECK(derivative.GetNumericResult({}) == 0);
//}
//
// TEST_CASE("2 * x", "Multiplication") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand = std::make_unique<math::Variable>('x');
//
//  auto multiplication = utils::AbstractSyntaxTree(
//      std::make_unique<math::Multiplication>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = multiplication.GetDerivative();
//
//  CHECK(multiplication.GetInfixExpression({}) == "2 * x");
//  CHECK(multiplication.GetRPNExpression({}) == "2 x *");
//  REQUIRE_THAT(multiplication.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(11, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "2");
//  CHECK(derivative.GetRPNExpression({}) == "2");
//  CHECK(derivative.GetNumericResult({{'x', 5.5}}) == 2);
//}
//
// TEST_CASE("2 * (x + 1)", "Multiplication") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Variable>('x'), std::make_unique<math::Number>(1));
//
//  auto multiplication = utils::AbstractSyntaxTree(
//      std::make_unique<math::Multiplication>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = multiplication.GetDerivative();
//
//  CHECK(multiplication.GetInfixExpression({}) == "2 * (x + 1)");
//  CHECK(multiplication.GetRPNExpression({}) == "2 x 1 + *");
//  REQUIRE_THAT(multiplication.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(13, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "2");
//  CHECK(derivative.GetRPNExpression({}) == "2");
//  CHECK(derivative.GetNumericResult({{'x', 5.5}}) == 2);
//}
//
// TEST_CASE("2 / 5.1", "Division") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand = std::make_unique<math::Number>(5.1);
//
//  auto division =
//      utils::AbstractSyntaxTree(std::make_unique<math::Division>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = division.GetDerivative();
//
//  CHECK(division.GetInfixExpression({}) == "2 / 5.1");
//  CHECK(division.GetRPNExpression({}) == "2 5.1 /");
//  REQUIRE_THAT(division.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(0.392, 1e-2));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinAbs(0, 1e-5));
//}
//
// TEST_CASE("(2 + x) / 5.1", "Division") {
//  auto left_operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Number>(2), std::make_unique<math::Variable>('x'));
//  auto right_operand = std::make_unique<math::Number>(5.1);
//
//  auto division =
//      utils::AbstractSyntaxTree(std::make_unique<math::Division>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = division.GetDerivative();
//
//  CHECK(division.GetInfixExpression({}) == "(2 + x) / 5.1");
//  CHECK(division.GetRPNExpression({}) == "2 x + 5.1 /");
//  REQUIRE_THAT(division.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(1.47, 1e-2));
//
//  CHECK(derivative.GetInfixExpression({}) == "5.1 / 26.01");
//  CHECK(derivative.GetRPNExpression({}) == "5.1 26.01 /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(1 / 5.1, 1e-2));
//}
//
// TEST_CASE("2 ^ x", "Exponentiation") {
//  auto left_operand = std::make_unique<math::Number>(2);
//  auto right_operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(utils::AbstractSyntaxTree(
//      std::make_unique<math::Exponentiation>(std::move(left_operand), std::move(right_operand))));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "2 ^ x");
//  CHECK(result.GetRPNExpression({}) == "2 x ^");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(32, 1e-2));
//
//  CHECK(derivative.GetInfixExpression({}) == "ln(2) * 2 ^ x");
//  CHECK(derivative.GetRPNExpression({}) == "2 ln 2 x ^ *");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(32 * std::log(2), 1e-2));
//}
//
// TEST_CASE("x ^ 2", "Exponentiation") {
//  auto left_operand = std::make_unique<math::Variable>('x');
//  auto right_operand = std::make_unique<math::Number>(2);
//
//  auto result = utils::AbstractSyntaxTree(
//      std::make_unique<math::Exponentiation>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "x ^ 2");
//  CHECK(result.GetRPNExpression({}) == "x 2 ^");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(25, 1e-2));
//
//  CHECK(derivative.GetInfixExpression({}) == "2 * x");
//  CHECK(derivative.GetRPNExpression({}) == "2 x *");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(10, 1e-2));
//}
//
// TEST_CASE("x ^ (2 + 4)", "Exponentiation") {
//  auto left_operand = std::make_unique<math::Variable>('x');
//  auto right_operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Number>(2), std::make_unique<math::Number>(4));
//
//  auto result = utils::AbstractSyntaxTree(
//      std::make_unique<math::Exponentiation>(std::move(left_operand), std::move(right_operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "x ^ 6");
//  CHECK(result.GetRPNExpression({}) == "x 6 ^");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(15625, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "6 * x ^ 5");
//  CHECK(derivative.GetRPNExpression({}) == "6 x 5 ^ *");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(18750, 1e-5));
//}
