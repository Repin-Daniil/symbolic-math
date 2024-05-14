// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"

#include "math/abstract-syntax-tree/operands/number.h"
#include "math/abstract-syntax-tree/operands/variable.h"

#include "math/abstract-syntax-tree/operations/unary/cos.h"
#include "math/abstract-syntax-tree/operations/unary/cos.h"  // check include guards
#include "math/abstract-syntax-tree/operations/unary/logarithm.h"
#include "math/abstract-syntax-tree/operations/unary/logarithm.h"  // check include guards
#include "math/abstract-syntax-tree/operations/unary/sin.h"
#include "math/abstract-syntax-tree/operations/unary/sin.h"  // check include guards
#include "math/abstract-syntax-tree/operations/unary/sqrt.h"
#include "math/abstract-syntax-tree/operations/unary/sqrt.h"  // check include guards
#include "math/abstract-syntax-tree/operations/unary/tangent.h"
#include "math/abstract-syntax-tree/operations/unary/tangent.h"  // check include guards
#include "math/abstract-syntax-tree/operations/unary/unary_minus.h"
#include "math/abstract-syntax-tree/operations/unary/unary_minus.h"  // check include guards

//
// TEST_CASE("-5", "UnaryMinus") {
//  auto operand = std::make_unique<math::Number>(5);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::UnaryMinus>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "-5");
//  CHECK(result.GetRPNExpression({}) == "5 ~");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-5, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
//}
//
// TEST_CASE("-x {3}", "UnaryMinus") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::UnaryMinus>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({{'x', -3}}) == "-(-3)");
//  CHECK(result.GetRPNExpression({{'x', -3}}) == "3 ~ ~");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-5, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "-1");
//  CHECK(derivative.GetRPNExpression({}) == "1 ~");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-1, 1e-5));
//}
//
// TEST_CASE("-x", "UnaryMinus") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::UnaryMinus>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "-x");
//  CHECK(result.GetRPNExpression({{'x', -3}}) == "3 ~ ~");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-5, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "-1");
//  CHECK(derivative.GetRPNExpression({}) == "1 ~");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-1, 1e-5));
//}
//
// TEST_CASE("-(-x))", "UnaryMinus") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(
//      std::make_unique<math::UnaryMinus>(std::make_unique<math::UnaryMinus>(std::move(operand))));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "x");
//  CHECK(result.GetRPNExpression({}) == "x");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(5, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1");
//  CHECK(derivative.GetRPNExpression({}) == "1");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1, 1e-5));
//}
//
// TEST_CASE("-(-3))", "UnaryMinus") {
//  auto operand = std::make_unique<math::Number>(-3);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::UnaryMinus>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "3");
//  CHECK(result.GetRPNExpression({}) == "3");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(3, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
//}
//
// TEST_CASE("-(x + 1)", "UnaryMinus") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::UnaryMinus>(
//      std::make_unique<math::Addition>(std::move(operand), std::make_unique<math::Number>(1))));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "-(x + 1)");
//  CHECK(result.GetRPNExpression({}) == "x 1 + ~");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-6, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "-1");
//  CHECK(derivative.GetRPNExpression({}) == "1 ~");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-1, 1e-5));
//}
//
// TEST_CASE("tan(1)", "Tangent") {
//  auto operand = std::make_unique<math::Number>(1);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Tangent>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "tan(1)");
//  CHECK(result.GetRPNExpression({}) == "1 tan");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(1), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
//}
//
// TEST_CASE("tan(x)", "Tangent") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Tangent>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "tan(x)");
//  CHECK(result.GetRPNExpression({}) == "x tan");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(5), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / cos(x) ^ 2");
//  CHECK(derivative.GetRPNExpression({}) == "1 x cos 2 ^ /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}),
//               Catch::Matchers::WithinRel(1 / (std::cos(5) * std::cos(5)), 1e-5));
//}
//
// TEST_CASE("tan(x + 25.3)", "Tangent") {
//  auto operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Variable>('x'), std::make_unique<math::Number>(25.3));
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Tangent>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "tan(x + 25.3)");
//  CHECK(result.GetRPNExpression({}) == "x 25.3 + tan");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(5 + 25.3), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / cos(x + 25.3) ^ 2");
//  CHECK(derivative.GetRPNExpression({}) == "1 x 25.3 + cos 2 ^ /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}),
//               Catch::Matchers::WithinRel(1 / (std::cos(5 + 25.3) * std::cos(5 + 25.3)), 1e-5));
//}
//
// TEST_CASE("tan(x) + 12", "Tangent") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Addition>(
//      std::make_unique<math::Tangent>(std::move(operand)), std::make_unique<math::Number>(12)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "tan(x) + 12");
//  CHECK(result.GetRPNExpression({}) == "x tan 12 +");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(5) + 12, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / cos(x) ^ 2");
//  CHECK(derivative.GetRPNExpression({}) == "1 x cos 2 ^ /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}),
//               Catch::Matchers::WithinRel(1 / (std::cos(5) * std::cos(5)), 1e-5));
//}
//
// TEST_CASE("sin(1)", "Sin") {
//  auto operand = std::make_unique<math::Number>(1);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Sin>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sin(1)");
//  CHECK(result.GetRPNExpression({}) == "1 sin");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(1), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
//}
//
// TEST_CASE("sin(x)", "Sin") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Sin>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sin(x)");
//  CHECK(result.GetRPNExpression({}) == "x sin");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(5), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "cos(x)");
//  CHECK(derivative.GetRPNExpression({}) == "x cos");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5), 1e-5));
//}
//
// TEST_CASE("sin(x + 25.3)", "Sin") {
//  auto operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Variable>('x'), std::make_unique<math::Number>(25.3));
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Sin>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sin(x + 25.3)");
//  CHECK(result.GetRPNExpression({}) == "x 25.3 + sin");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(5 + 25.3), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "cos(x + 25.3)");
//  CHECK(derivative.GetRPNExpression({}) == "x 25.3 + cos");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5 + 25.3), 1e-5));
//}
//
// TEST_CASE("sin(x) + 12", "Sin") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Addition>(
//      std::make_unique<math::Sin>(std::move(operand)), std::make_unique<math::Number>(12)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sin(x) + 12");
//  CHECK(result.GetRPNExpression({}) == "x sin 12 +");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(5) + 12, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "cos(x)");
//  CHECK(derivative.GetRPNExpression({}) == "x cos");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5), 1e-5));
//}
//
// TEST_CASE("cos(1)", "Cos") {
//  auto operand = std::make_unique<math::Number>(1);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Cos>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "cos(1)");
//  CHECK(result.GetRPNExpression({}) == "1 cos");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(1), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
//}
//
// TEST_CASE("cos(x)", "Cos") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Cos>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "cos(x)");
//  CHECK(result.GetRPNExpression({}) == "x cos");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "-sin(x)");
//  CHECK(derivative.GetRPNExpression({}) == "x sin ~");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-std::sin(5), 1e-5));
//}
//
// TEST_CASE("cos(x + 25.3)", "Cos") {
//  auto operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Variable>('x'), std::make_unique<math::Number>(25.3));
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Cos>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "cos(x + 25.3)");
//  CHECK(result.GetRPNExpression({}) == "x 25.3 + cos");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5 + 25.3), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "-sin(x + 25.3)");
//  CHECK(derivative.GetRPNExpression({}) == "x 25.3 + sin ~");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-std::sin(5 + 25.3), 1e-5));
//}
//
// TEST_CASE("cos(x) + 12", "Cos") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Addition>(
//      std::make_unique<math::Cos>(std::move(operand)), std::make_unique<math::Number>(12)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "cos(x) + 12");
//  CHECK(result.GetRPNExpression({}) == "x cos 12 +");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5) + 12, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "-sin(x)");
//  CHECK(derivative.GetRPNExpression({}) == "x sin ~");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-std::sin(5), 1e-5));
//}
//
// TEST_CASE("ln(1)", "Logarithm") {
//  auto operand = std::make_unique<math::Number>(1);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Logarithm>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "ln(1)");
//  CHECK(result.GetRPNExpression({}) == "1 ln");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(1), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
//}
//
// TEST_CASE("ln(x)", "Logarithm") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Logarithm>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "ln(x)");
//  CHECK(result.GetRPNExpression({}) == "x ln");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(5), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / x");
//  CHECK(derivative.GetRPNExpression({}) == "1 x /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(0.2, 1e-5));
//}
//
// TEST_CASE("ln(x + 25.3)", "Logarithm") {
//  auto operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Variable>('x'), std::make_unique<math::Number>(25.3));
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Logarithm>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "ln(x + 25.3)");
//  CHECK(result.GetRPNExpression({}) == "x 25.3 + ln");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(5 + 25.3), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / (x + 25.3)");
//  CHECK(derivative.GetRPNExpression({}) == "1 x 25.3 + /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (5 + 25.3), 1e-5));
//}
//
// TEST_CASE("ln(x) + 12", "Logarithm") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Addition>(
//      std::make_unique<math::Logarithm>(std::move(operand)), std::make_unique<math::Number>(12)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "ln(x) + 12");
//  CHECK(result.GetRPNExpression({}) == "x ln 12 +");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(5) + 12, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / x");
//  CHECK(derivative.GetRPNExpression({}) == "1 x /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(0.2, 1e-5));
//}
//
// TEST_CASE("sqrt(1)", "SquareRoot") {
//  auto operand = std::make_unique<math::Number>(1);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::SquareRoot>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "1");
//  CHECK(result.GetRPNExpression({}) == "1");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(1), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (5), 1e-5));
//}
//
// TEST_CASE("sqrt(4)", "SquareRoot") {
//  auto operand = std::make_unique<math::Number>(4);
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::SquareRoot>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sqrt(4)");
//  CHECK(result.GetRPNExpression({}) == "4 sqrt");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(4), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "0");
//  CHECK(derivative.GetRPNExpression({}) == "0");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (5), 1e-5));
//}
//
// TEST_CASE("sqrt(x)", "SquareRoot") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::SquareRoot>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sqrt(x)");
//  CHECK(result.GetRPNExpression({{'x', 12.25}}) == "12.25 sqrt");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(5), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / (2 * sqrt(x))");
//  CHECK(derivative.GetRPNExpression({}) == "1 2 x sqrt * /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (2 * sqrt(5)), 1e-5));
//}
//
// TEST_CASE("sqrt(x + 25.3)", "SquareRoot") {
//  auto operand =
//      std::make_unique<math::Addition>(std::make_unique<math::Variable>('x'), std::make_unique<math::Number>(25.3));
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::SquareRoot>(std::move(operand)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sqrt(x + 25.3)");
//  CHECK(result.GetRPNExpression({}) == "x 25.3 + sqrt");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(5 + 25.3), 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / (2 * sqrt(x + 25.3))");
//  CHECK(derivative.GetRPNExpression({}) == "1 2 x 25.3 + sqrt * /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (2 * sqrt(5 + 25.3)), 1e-5));
//}
//
// TEST_CASE("sqrt(x) + 12", "SquareRoot") {
//  auto operand = std::make_unique<math::Variable>('x');
//
//  auto result = utils::AbstractSyntaxTree(std::make_unique<math::Addition>(
//      std::make_unique<math::SquareRoot>(std::move(operand)), std::make_unique<math::Number>(12)));
//  auto derivative = result.GetDerivative();
//
//  CHECK(result.GetInfixExpression({}) == "sqrt(x) + 12");
//  CHECK(result.GetRPNExpression({}) == "x sqrt 12 +");
//  REQUIRE_THAT(result.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(5) + 12, 1e-5));
//
//  CHECK(derivative.GetInfixExpression({}) == "1 / (2 * sqrt(x))");
//  CHECK(derivative.GetRPNExpression({}) == "1 2 x sqrt * /");
//  REQUIRE_THAT(derivative.GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (2 * sqrt(5)), 1e-5));
//}