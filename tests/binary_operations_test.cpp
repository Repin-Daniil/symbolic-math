#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

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
#include "math/algebra/expressions/operations/binary/substraction.h"
#include "math/algebra/expressions/operations/binary/substraction.h"  // check include guards

TEST_CASE("2 + 5", "Addition") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5);

  auto addition = std::make_shared<math::Addition>(left_operand, right_operand);
  auto derivative = addition->GetDerivative();

  CHECK(addition->GetInfix(false) == "2 + 5");
  CHECK(addition->GetRPN() == "2 5 +");

  CHECK(derivative->GetInfix(false) == "0 + 0");
  CHECK(derivative->GetRPN() == "0 0 +");
}

TEST_CASE("2 + x", "Addition") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Variable>('x');

  auto addition = std::make_shared<math::Addition>(left_operand, right_operand);
  auto derivative = addition->GetDerivative();

  CHECK(addition->GetInfix(false) == "2 + x");
  CHECK(addition->GetRPN() == "2 x +");

  CHECK(derivative->GetInfix(false) == "0 + 1");
  CHECK(derivative->GetRPN() == "0 1 +");
}

TEST_CASE("2 + (1.5 + x)", "Addition") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(1.5), std::make_shared<math::Variable>('x'));

  auto addition = std::make_shared<math::Addition>(left_operand, right_operand);
  auto derivative = addition->GetDerivative();

  CHECK(addition->GetInfix(false) == "2 + 1.5 + x");
  CHECK(addition->GetRPN() == "2 1.5 x + +");

  CHECK(derivative->GetInfix(false) == "0 + 0 + 1");
  CHECK(derivative->GetRPN() == "0 0 1 + +");
}

TEST_CASE("2 - 5.1", "Substraction") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto substraction = std::make_shared<math::Substraction>(left_operand, right_operand);
  auto derivative = substraction->GetDerivative();

  CHECK(substraction->GetInfix(false) == "2 - 5.1");
  CHECK(substraction->GetRPN() == "2 5.1 -");

  CHECK(derivative->GetInfix(false) == "0 - 0");
  CHECK(derivative->GetRPN() == "0 0 -");
}

TEST_CASE("x - 2", "Substraction") {
  auto left_operand = std::make_shared<math::Variable>('x');
  auto right_operand = std::make_shared<math::Number>(2);

  auto substraction = std::make_shared<math::Substraction>(left_operand, right_operand);
  auto derivative = substraction->GetDerivative();

  CHECK(substraction->GetInfix(false) == "x - 2");
  CHECK(substraction->GetRPN() == "x 2 -");

  CHECK(derivative->GetInfix(false) == "1 - 0");
  CHECK(derivative->GetRPN() == "1 0 -");
}

TEST_CASE("2 - (1.5 + x)", "Substraction") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(1.5), std::make_shared<math::Variable>('x'));

  auto substraction = std::make_shared<math::Substraction>(left_operand, right_operand);
  auto derivative = substraction->GetDerivative();

  CHECK(substraction->GetInfix(false) == "2 - (1.5 + x)");
  CHECK(substraction->GetRPN() == "2 1.5 x + -");

  CHECK(derivative->GetInfix(false) == "0 - (0 + 1)");
  CHECK(derivative->GetRPN() == "0 0 1 + -");
}

TEST_CASE("2 * 5.1", "Multiplication") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto multiplication = std::make_shared<math::Multiplication>(left_operand, right_operand);
  auto derivative = multiplication->GetDerivative();

  CHECK(multiplication->GetInfix(false) == "2 * 5.1");
  CHECK(multiplication->GetRPN() == "2 5.1 *");

  CHECK(derivative->GetInfix(false) == "2 * 0 + 0 * 5.1");
  CHECK(derivative->GetRPN() == "2 0 * 0 5.1 * +");
}

TEST_CASE("2 * x", "Multiplication") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Variable>('x');

  auto multiplication = std::make_shared<math::Multiplication>(left_operand, right_operand);
  auto derivative = multiplication->GetDerivative();

  CHECK(multiplication->GetInfix(false) == "2 * x");
  CHECK(multiplication->GetRPN() == "2 x *");

  CHECK(derivative->GetInfix(false) == "2 * 1 + 0 * x");
  CHECK(derivative->GetRPN() == "2 1 * 0 x * +");
}

TEST_CASE("2 * (x + 1)", "Multiplication") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(1));

  auto multiplication = std::make_shared<math::Multiplication>(left_operand, right_operand);
  auto derivative = multiplication->GetDerivative();

  CHECK(multiplication->GetInfix(false) == "2 * (x + 1)");
  CHECK(multiplication->GetRPN() == "2 x 1 + *");

  CHECK(derivative->GetInfix(false) == "2 * (1 + 0) + 0 * (x + 1)");
  CHECK(derivative->GetRPN() == "2 1 0 + * 0 x 1 + * +");
}

TEST_CASE("2 / 5.1", "Division") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto division = std::make_shared<math::Division>(left_operand, right_operand);
  auto derivative = division->GetDerivative();

  CHECK(division->GetInfix(false) == "2 / 5.1");
  CHECK(division->GetRPN() == "2 5.1 /");

  CHECK(derivative->GetInfix(false) == "(0 * 5.1 - (2 * 0)) / (2 ^ 2)");
  CHECK(derivative->GetRPN() == "0 5.1 * 2 0 * - 2 2 ^ /");
}

TEST_CASE("(2 + x) / 5.1", "Division") {
  auto left_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(2), std::make_shared<math::Variable>('x'));
  auto right_operand = std::make_shared<math::Number>(5.1);

  auto division = std::make_shared<math::Division>(left_operand, right_operand);
  auto derivative = division->GetDerivative();

  CHECK(division->GetInfix(false) == "(2 + x) / 5.1");
  CHECK(division->GetRPN() == "2 x + 5.1 /");

  CHECK(derivative->GetInfix(false) == "((0 + 1) * 5.1 - ((2 + x) * 0)) / ((2 + x) ^ 2)");
  CHECK(derivative->GetRPN() == "0 1 + 5.1 * 2 x + 0 * - 2 x + 2 ^ /");
}

TEST_CASE("2 ^ x", "Exponentiation") {
  auto left_operand = std::make_shared<math::Number>(2);
  auto right_operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Exponentiation>(left_operand, right_operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "2 ^ x");
  CHECK(result->GetRPN() == "2 x ^");

  CHECK(derivative->GetInfix(false) == "(2 ^ x) * (1 * ln(2) + (x * 0) / 2)");
  CHECK(derivative->GetRPN() == "2 x ^ 1 2 ln * x 0 * 2 / + *");
}

TEST_CASE("x ^ 2", "Exponentiation") {
  auto left_operand = std::make_shared<math::Variable>('x');
  auto right_operand = std::make_shared<math::Number>(2);

  auto result = std::make_shared<math::Exponentiation>(left_operand, right_operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "x ^ 2");
  CHECK(result->GetRPN() == "x 2 ^");

  CHECK(derivative->GetInfix(false) == "(x ^ 2) * (0 * ln(x) + (2 * 1) / x)");
  CHECK(derivative->GetRPN() == "x 2 ^ 0 x ln * 2 1 * x / + *");
}

TEST_CASE("x ^ (2 + 4)", "Exponentiation") {
  auto left_operand = std::make_shared<math::Variable>('x');
  auto right_operand =
      std::make_shared<math::Addition>(std::make_shared<math::Number>(2), std::make_shared<math::Number>(4));

  auto result = std::make_shared<math::Exponentiation>(left_operand, right_operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "x ^ (2 + 4)");
  CHECK(result->GetRPN() == "x 2 4 + ^");

  CHECK(derivative->GetInfix(false) == "(x ^ (2 + 4)) * ((0 + 0) * ln(x) + ((2 + 4) * 1) / x)");
  CHECK(derivative->GetRPN() == "x 2 4 + ^ 0 0 + x ln * 2 4 + 1 * x / + *");
}