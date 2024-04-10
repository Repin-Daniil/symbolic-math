#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operands/variable.h"

#include "math/algebra/expressions/operations/unary/cos.h"
#include "math/algebra/expressions/operations/unary/cos.h"  // check include guards
#include "math/algebra/expressions/operations/unary/logarithm.h"
#include "math/algebra/expressions/operations/unary/logarithm.h"  // check include guards
#include "math/algebra/expressions/operations/unary/sin.h"
#include "math/algebra/expressions/operations/unary/sin.h"  // check include guards
#include "math/algebra/expressions/operations/unary/sqrt.h"
#include "math/algebra/expressions/operations/unary/sqrt.h"  // check include guards
#include "math/algebra/expressions/operations/unary/tangent.h"
#include "math/algebra/expressions/operations/unary/tangent.h"  // check include guards
#include "math/algebra/expressions/operations/unary/unary_minus.h"
#include "math/algebra/expressions/operations/unary/unary_minus.h"  // check include guards

TEST_CASE("-5", "UnaryMinus") {
  auto operand = std::make_shared<math::Number>(5);

  auto result = std::make_shared<math::UnaryMinus>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "-5");
  CHECK(result->GetRPN({}) == "5 ~");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-5, 1e-5));

  CHECK(derivative->GetInfix(0) == "-0");
  CHECK(derivative->GetRPN({}) == "0 ~");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("-x", "UnaryMinus") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::UnaryMinus>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "-x");
  CHECK(result->GetRPN({}) == "x ~");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-5, 1e-5));

  CHECK(derivative->GetInfix(0) == "-1");
  CHECK(derivative->GetRPN({}) == "1 ~");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-1, 1e-5));
}

TEST_CASE("-(x + 1)", "UnaryMinus") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::UnaryMinus>(std::make_shared<math::Addition>(operand, std::make_shared<math::Number>(1)));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "-(x + 1)");
  CHECK(result->GetRPN({}) == "x 1 + ~");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-6, 1e-5));

  CHECK(derivative->GetInfix(0) == "-(1 + 0)");
  CHECK(derivative->GetRPN({}) == "1 0 + ~");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-1, 1e-5));
}

TEST_CASE("tan(1)", "Tangent") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Tangent>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "tan(1)");
  CHECK(result->GetRPN({}) == "1 tan");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(1), 1e-5));

  CHECK(derivative->GetInfix(0) == "0 / cos(1) ^ 2");
  CHECK(derivative->GetRPN({}) == "0 1 cos 2 ^ /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("tan(x)", "Tangent") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Tangent>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "tan(x)");
  CHECK(result->GetRPN({}) == "x tan");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(5), 1e-5));

  CHECK(derivative->GetInfix(0) == "1 / cos(x) ^ 2");
  CHECK(derivative->GetRPN({}) == "1 x cos 2 ^ /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}),
               Catch::Matchers::WithinRel(1 / (std::cos(5) * std::cos(5)), 1e-5));
}

TEST_CASE("tan(x + 25.3)", "Tangent") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Tangent>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "tan(x + 25.3)");
  CHECK(result->GetRPN({}) == "x 25.3 + tan");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(5 + 25.3), 1e-5));

  CHECK(derivative->GetInfix(0) == "(1 + 0) / cos(x + 25.3) ^ 2");
  CHECK(derivative->GetRPN({}) == "1 0 + x 25.3 + cos 2 ^ /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}),
               Catch::Matchers::WithinRel(1 / (std::cos(5 + 25.3) * std::cos(5 + 25.3)), 1e-5));
}

TEST_CASE("tan(x) + 12", "Tangent") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Tangent>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "tan(x) + 12");
  CHECK(result->GetRPN({}) == "x tan 12 +");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::tan(5) + 12, 1e-5));

  CHECK(derivative->GetInfix(0) == "1 / cos(x) ^ 2 + 0");
  CHECK(derivative->GetRPN({}) == "1 x cos 2 ^ / 0 +");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}),
               Catch::Matchers::WithinRel(1 / (std::cos(5) * std::cos(5)), 1e-5));
}

TEST_CASE("sin(1)", "Sin") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Sin>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sin(1)");
  CHECK(result->GetRPN({}) == "1 sin");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(1), 1e-5));

  CHECK(derivative->GetInfix(0) == "cos(1) * 0");
  CHECK(derivative->GetRPN({}) == "1 cos 0 *");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("sin(x)", "Sin") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Sin>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sin(x)");
  CHECK(result->GetRPN({}) == "x sin");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(5), 1e-5));

  CHECK(derivative->GetInfix(0) == "cos(x) * 1");
  CHECK(derivative->GetRPN({}) == "x cos 1 *");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5), 1e-5));
}

TEST_CASE("sin(x + 25.3)", "Sin") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Sin>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sin(x + 25.3)");
  CHECK(result->GetRPN({}) == "x 25.3 + sin");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(5 + 25.3), 1e-5));

  CHECK(derivative->GetInfix(0) == "cos(x + 25.3) * (1 + 0)");
  CHECK(derivative->GetRPN({}) == "x 25.3 + cos 1 0 + *");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5 + 25.3), 1e-5));
}

TEST_CASE("sin(x) + 12", "Sin") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Sin>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sin(x) + 12");
  CHECK(result->GetRPN({}) == "x sin 12 +");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sin(5) + 12, 1e-5));

  CHECK(derivative->GetInfix(0) == "cos(x) * 1 + 0");
  CHECK(derivative->GetRPN({}) == "x cos 1 * 0 +");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5), 1e-5));
}

TEST_CASE("cos(1)", "Cos") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Cos>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "cos(1)");
  CHECK(result->GetRPN({}) == "1 cos");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(1), 1e-5));

  CHECK(derivative->GetInfix(0) == "-sin(1) * 0");
  CHECK(derivative->GetRPN({}) == "1 sin 0 * ~");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("cos(x)", "Cos") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Cos>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "cos(x)");
  CHECK(result->GetRPN({}) == "x cos");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5), 1e-5));

  CHECK(derivative->GetInfix(0) == "-sin(x) * 1");
  CHECK(derivative->GetRPN({}) == "x sin 1 * ~");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-std::sin(5), 1e-5));
}

TEST_CASE("cos(x + 25.3)", "Cos") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Cos>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "cos(x + 25.3)");
  CHECK(result->GetRPN({}) == "x 25.3 + cos");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5 + 25.3), 1e-5));

  CHECK(derivative->GetInfix(0) == "-sin(x + 25.3) * (1 + 0)");
  CHECK(derivative->GetRPN({}) == "x 25.3 + sin 1 0 + * ~");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-std::sin(5 + 25.3), 1e-5));
}

TEST_CASE("cos(x) + 12", "Cos") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Cos>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "cos(x) + 12");
  CHECK(result->GetRPN({}) == "x cos 12 +");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::cos(5) + 12, 1e-5));

  CHECK(derivative->GetInfix(0) == "-sin(x) * 1 + 0");
  CHECK(derivative->GetRPN({}) == "x sin 1 * ~ 0 +");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-std::sin(5), 1e-5));
}

TEST_CASE("ln(1)", "Logarithm") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Logarithm>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "ln(1)");
  CHECK(result->GetRPN({}) == "1 ln");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(1), 1e-5));

  CHECK(derivative->GetInfix(0) == "0 / 1");
  CHECK(derivative->GetRPN({}) == "0 1 /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("ln(x)", "Logarithm") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Logarithm>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "ln(x)");
  CHECK(result->GetRPN({}) == "x ln");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(5), 1e-5));

  CHECK(derivative->GetInfix(0) == "1 / x");
  CHECK(derivative->GetRPN({}) == "1 x /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(0.2, 1e-5));
}

TEST_CASE("ln(x + 25.3)", "Logarithm") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Logarithm>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "ln(x + 25.3)");
  CHECK(result->GetRPN({}) == "x 25.3 + ln");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(5 + 25.3), 1e-5));

  CHECK(derivative->GetInfix(0) == "(1 + 0) / (x + 25.3)");
  CHECK(derivative->GetRPN({}) == "1 0 + x 25.3 + /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (5 + 25.3), 1e-5));
}

TEST_CASE("ln(x) + 12", "Logarithm") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Logarithm>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "ln(x) + 12");
  CHECK(result->GetRPN({}) == "x ln 12 +");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::log(5) + 12, 1e-5));

  CHECK(derivative->GetInfix(0) == "1 / x + 0");
  CHECK(derivative->GetRPN({}) == "1 x / 0 +");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(0.2, 1e-5));
}

TEST_CASE("sqrt(1)", "SquareRoot") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::SquareRoot>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sqrt(1)");
  CHECK(result->GetRPN({}) == "1 sqrt");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(1), 1e-5));

  CHECK(derivative->GetInfix(0) == "0 / (2 * sqrt(1))");
  CHECK(derivative->GetRPN({}) == "0 2 1 sqrt * /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (5), 1e-5));
}

TEST_CASE("sqrt(x)", "SquareRoot") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::SquareRoot>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sqrt(x)");
  CHECK(result->GetRPN({{'x', 12.25}}) == "12.25 sqrt");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(5), 1e-5));

  CHECK(derivative->GetInfix(0) == "1 / (2 * sqrt(x))");
  CHECK(derivative->GetRPN({}) == "1 2 x sqrt * /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (2 * sqrt(5)), 1e-5));
}

TEST_CASE("sqrt(x + 25.3)", "SquareRoot") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::SquareRoot>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sqrt(x + 25.3)");
  CHECK(result->GetRPN({}) == "x 25.3 + sqrt");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(5 + 25.3), 1e-5));

  CHECK(derivative->GetInfix(0) == "(1 + 0) / (2 * sqrt(x + 25.3))");
  CHECK(derivative->GetRPN({}) == "1 0 + 2 x 25.3 + sqrt * /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (2 * sqrt(5 + 25.3)), 1e-5));
}

TEST_CASE("sqrt(x) + 12", "SquareRoot") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::SquareRoot>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0) == "sqrt(x) + 12");
  CHECK(result->GetRPN({}) == "x sqrt 12 +");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(std::sqrt(5) + 12, 1e-5));

  CHECK(derivative->GetInfix(0) == "1 / (2 * sqrt(x)) + 0");
  CHECK(derivative->GetRPN({}) == "1 2 x sqrt * / 0 +");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(1 / (2 * sqrt(5)), 1e-5));
}