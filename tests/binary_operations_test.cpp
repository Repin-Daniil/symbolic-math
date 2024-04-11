#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operands/variable.h"

#include "math/algebra/expressions/operations/binary/addition.h"
#include "math/algebra/expressions/operations/binary/addition.h"  // check include guards
#include "math/algebra/expressions/operations/binary/division.h"
#include "math/algebra/expressions/operations/binary/division.h"  // check include guards
#include "math/algebra/expressions/operations/binary/exponentiation.h"
#include "math/algebra/expressions/operations/binary/exponentiation.h"  // check include guards
#include "math/algebra/expressions/operations/binary/multiplication.h"
#include "math/algebra/expressions/operations/binary/multiplication.h"  // check include guards
#include "math/algebra/expressions/operations/binary/subtraction.h"
#include "math/algebra/expressions/operations/binary/subtraction.h"  // check include guards

TEST_CASE("2 + 5", "Addition") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5);

  auto addition = std::make_shared<math::Addition>(left_operand, right_operand);
  auto derivative = addition->GetDerivative();

  CHECK(addition->GetInfix(0, {}) == "2 + 5");
  CHECK(addition->GetRPN({}) == "2 5 +");
  CHECK(addition->GetNumericResult({}) == 7);

  CHECK(derivative->GetInfix(0, {}) == "0 + 0");
  CHECK(derivative->GetRPN({}) == "0 0 +");
  CHECK(derivative->GetNumericResult({}) == 0);
}

TEST_CASE("2 + x", "Addition") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Variable>('x');

  auto addition = std::make_shared<math::Addition>(left_operand, right_operand);
  auto derivative = addition->GetDerivative();

  CHECK(addition->GetInfix(0, {}) == "2 + x");
  CHECK(addition->GetRPN({}) == "2 x +");
  CHECK(addition->GetNumericResult({{'x', 5}}) == 7);

  CHECK(derivative->GetInfix(0, {}) == "0 + 1");
  CHECK(derivative->GetRPN({}) == "0 1 +");
  CHECK(derivative->GetNumericResult({}) == 1);
}

TEST_CASE("2 + (1.5 + x)", "Addition") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(1.5), std::make_shared<math::Variable>('x'));

  auto addition = std::make_shared<math::Addition>(left_operand, right_operand);
  auto derivative = addition->GetDerivative();

  CHECK(addition->GetInfix(0, {}) == "2 + 1.5 + x");
  CHECK(addition->GetRPN({{'x', 1}}) == "2 1.5 1 + +");
  REQUIRE_THAT(addition->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(8.5, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "0 + 0 + 1");
  CHECK(derivative->GetRPN({{'x', 1}}) == "0 0 1 + +");
  CHECK(derivative->GetNumericResult({}) == 1);
}

TEST_CASE("2 - 5.1", "Substraction") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto substraction = std::make_shared<math::Subtraction>(left_operand, right_operand);
  auto derivative = substraction->GetDerivative();

  CHECK(substraction->GetInfix(0, {}) == "2 - 5.1");
  CHECK(substraction->GetRPN({}) == "2 5.1 -");
  REQUIRE_THAT(substraction->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(-3.1, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "0 - 0");
  CHECK(derivative->GetRPN({}) == "0 0 -");
  CHECK(derivative->GetNumericResult({}) == 0);
}

TEST_CASE("x - 2", "Substraction") {
  auto left_operand = std::make_shared<math::Variable>('x');
  auto right_operand = std::make_shared<math::Number>(2);

  auto substraction = std::make_shared<math::Subtraction>(left_operand, right_operand);
  auto derivative = substraction->GetDerivative();

  CHECK(substraction->GetInfix(0, {}) == "x - 2");
  CHECK(substraction->GetRPN({{'y', 1}}) == "x 2 -");
  REQUIRE_THAT(substraction->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(3.5, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "1 - 0");
  CHECK(derivative->GetRPN({}) == "1 0 -");
  CHECK(derivative->GetNumericResult({}) == 1);
}

TEST_CASE("2 - (1.5 + x)", "Substraction") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(1.5), std::make_shared<math::Variable>('x'));

  auto substraction = std::make_shared<math::Subtraction>(left_operand, right_operand);
  auto derivative = substraction->GetDerivative();

  CHECK(substraction->GetInfix(0, {}) == "2 - (1.5 + x)");
  CHECK(substraction->GetRPN({}) == "2 1.5 x + -");
  REQUIRE_THAT(substraction->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(-5, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "0 - (0 + 1)");
  CHECK(derivative->GetRPN({}) == "0 0 1 + -");
  CHECK(derivative->GetNumericResult({}) == -1);
}

TEST_CASE("2 * 5.1", "Multiplication") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto multiplication = std::make_shared<math::Multiplication>(left_operand, right_operand);
  auto derivative = multiplication->GetDerivative();

  CHECK(multiplication->GetInfix(0, {}) == "2 * 5.1");
  CHECK(multiplication->GetRPN({}) == "2 5.1 *");
  REQUIRE_THAT(multiplication->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(10.2, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "2 * 0 + 0 * 5.1");
  CHECK(derivative->GetRPN({}) == "2 0 * 0 5.1 * +");
  CHECK(derivative->GetNumericResult({}) == 0);
}

TEST_CASE("2 * x", "Multiplication") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Variable>('x');

  auto multiplication = std::make_shared<math::Multiplication>(left_operand, right_operand);
  auto derivative = multiplication->GetDerivative();

  CHECK(multiplication->GetInfix(0, {}) == "2 * x");
  CHECK(multiplication->GetRPN({}) == "2 x *");
  REQUIRE_THAT(multiplication->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(11, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "2 * 1 + 0 * x");
  CHECK(derivative->GetRPN({}) == "2 1 * 0 x * +");
  CHECK(derivative->GetNumericResult({{'x', 5.5}}) == 2);
}

TEST_CASE("2 * (x + 1)", "Multiplication") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(1));

  auto multiplication = std::make_shared<math::Multiplication>(left_operand, right_operand);
  auto derivative = multiplication->GetDerivative();

  CHECK(multiplication->GetInfix(0, {}) == "2 * (x + 1)");
  CHECK(multiplication->GetRPN({}) == "2 x 1 + *");
  REQUIRE_THAT(multiplication->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(13, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "2 * (1 + 0) + 0 * (x + 1)");
  CHECK(derivative->GetRPN({}) == "2 1 0 + * 0 x 1 + * +");
  CHECK(derivative->GetNumericResult({{'x', 5.5}}) == 2);
}

TEST_CASE("2 / 5.1", "Division") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto division = std::make_shared<math::Division>(left_operand, right_operand);
  auto derivative = division->GetDerivative();

  CHECK(division->GetInfix(0, {}) == "2 / 5.1");
  CHECK(division->GetRPN({}) == "2 5.1 /");
  REQUIRE_THAT(division->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(0.392, 1e-2));

  CHECK(derivative->GetInfix(0, {}) == "(0 * 5.1 - 2 * 0) / 5.1 ^ 2");
  CHECK(derivative->GetRPN({}) == "0 5.1 * 2 0 * - 5.1 2 ^ /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("(2 + x) / 5.1", "Division") {
  auto left_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(2), std::make_shared<math::Variable>('x'));
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto division = std::make_shared<math::Division>(left_operand, right_operand);
  auto derivative = division->GetDerivative();

  CHECK(division->GetInfix(0, {}) == "(2 + x) / 5.1");
  CHECK(division->GetRPN({}) == "2 x + 5.1 /");
  REQUIRE_THAT(division->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(1.47, 1e-2));

  CHECK(derivative->GetInfix(0, {}) == "((0 + 1) * 5.1 - (2 + x) * 0) / 5.1 ^ 2");
  CHECK(derivative->GetRPN({}) == "0 1 + 5.1 * 2 x + 0 * - 5.1 2 ^ /");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5.5}}), Catch::Matchers::WithinRel(1 / 5.1, 1e-2));
}

TEST_CASE("2 ^ x", "Exponentiation") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Exponentiation>(left_operand, right_operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0, {}) == "2 ^ x");
  CHECK(result->GetRPN({}) == "2 x ^");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(32, 1e-2));

  CHECK(derivative->GetInfix(0, {}) == "2 ^ x * ln(2)");
  CHECK(derivative->GetRPN({}) == "2 x ^ 2 ln *");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(32 * std::log(2), 1e-2));
}

TEST_CASE("x ^ 2", "Exponentiation") {
  auto left_operand = std::make_shared<math::Variable>('x');
  auto right_operand = std::make_shared<math::Number>(2);

  auto result = std::make_shared<math::Exponentiation>(left_operand, right_operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0, {}) == "x ^ 2");
  CHECK(result->GetRPN({}) == "x 2 ^");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(25, 1e-2));

  CHECK(derivative->GetInfix(0, {}) == "2 * x ^ (2 - 1)");
  CHECK(derivative->GetRPN({}) == "2 x 2 1 - ^ *");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(10, 1e-2));
}

TEST_CASE("x ^ (2 + 4)", "Exponentiation") {
  auto left_operand = std::make_shared<math::Variable>('x');
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(2), std::make_shared<math::Number>(4));

  auto result = std::make_shared<math::Exponentiation>(left_operand, right_operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(0, {}) == "x ^ (2 + 4)");
  CHECK(result->GetRPN({}) == "x 2 4 + ^");
  REQUIRE_THAT(result->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(15625, 1e-5));

  CHECK(derivative->GetInfix(0, {}) == "(2 + 4) * x ^ ((2 + 4) - 1)");
  CHECK(derivative->GetRPN({}) == "2 4 + x 2 4 + 1 - ^ *");
  REQUIRE_THAT(derivative->GetNumericResult({{'x', 5}}), Catch::Matchers::WithinRel(18750, 1e-5));
}
