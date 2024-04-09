#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

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

  CHECK(result->GetInfix(false) == "-5");
  CHECK(result->GetRPN() == "5 ~");

  CHECK(derivative->GetInfix(false) == "-0");
  CHECK(derivative->GetRPN() == "0 ~");
}

TEST_CASE("-x", "UnaryMinus") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::UnaryMinus>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "-x");
  CHECK(result->GetRPN() == "x ~");

  CHECK(derivative->GetInfix(false) == "-1");
  CHECK(derivative->GetRPN() == "1 ~");
}

TEST_CASE("-(x + 1)", "UnaryMinus") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::UnaryMinus>(std::make_shared<math::Addition>(operand, std::make_shared<math::Number>(1)));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "-(x + 1)");
  CHECK(result->GetRPN() == "x 1 + ~");

  CHECK(derivative->GetInfix(false) == "-(1 + 0)");
  CHECK(derivative->GetRPN() == "1 0 + ~");
}

TEST_CASE("tan(1)", "Tangent") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Tangent>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "tan(1)");
  CHECK(result->GetRPN() == "1 tan");

  CHECK(derivative->GetInfix(false) == "0 / cos(1) ^ 2");
  CHECK(derivative->GetRPN() == "0 1 cos 2 ^ /");
}

TEST_CASE("tan(x)", "Tangent") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Tangent>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "tan(x)");
  CHECK(result->GetRPN() == "x tan");

  CHECK(derivative->GetInfix(false) == "1 / cos(x) ^ 2");
  CHECK(derivative->GetRPN() == "1 x cos 2 ^ /");
}

TEST_CASE("tan(x + 25.3)", "Tangent") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Tangent>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "tan(x + 25.3)");
  CHECK(result->GetRPN() == "x 25.3 + tan");

  CHECK(derivative->GetInfix(false) == "(1 + 0) / cos(x + 25.3) ^ 2");
  CHECK(derivative->GetRPN() == "1 0 + x 25.3 + cos 2 ^ /");
}

TEST_CASE("tan(x) + 12", "Tangent") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Tangent>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "tan(x) + 12");
  CHECK(result->GetRPN() == "x tan 12 +");

  CHECK(derivative->GetInfix(false) == "1 / cos(x) ^ 2 + 0");
  CHECK(derivative->GetRPN() == "1 x cos 2 ^ / 0 +");
}

TEST_CASE("sin(1)", "Sin") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Sin>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sin(1)");
  CHECK(result->GetRPN() == "1 sin");

  CHECK(derivative->GetInfix(false) == "cos(1) * 0");
  CHECK(derivative->GetRPN() == "1 cos 0 *");
}

TEST_CASE("sin(x)", "Sin") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Sin>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sin(x)");
  CHECK(result->GetRPN() == "x sin");

  CHECK(derivative->GetInfix(false) == "cos(x) * 1");
  CHECK(derivative->GetRPN() == "x cos 1 *");
}

TEST_CASE("sin(x + 25.3)", "Sin") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Sin>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sin(x + 25.3)");
  CHECK(result->GetRPN() == "x 25.3 + sin");

  CHECK(derivative->GetInfix(false) == "cos(x + 25.3) * (1 + 0)");
  CHECK(derivative->GetRPN() == "x 25.3 + cos 1 0 + *");
}

TEST_CASE("sin(x) + 12", "Sin") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Sin>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sin(x) + 12");
  CHECK(result->GetRPN() == "x sin 12 +");

  CHECK(derivative->GetInfix(false) == "cos(x) * 1 + 0");
  CHECK(derivative->GetRPN() == "x cos 1 * 0 +");
}

TEST_CASE("cos(1)", "Cos") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Cos>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "cos(1)");
  CHECK(result->GetRPN() == "1 cos");

  CHECK(derivative->GetInfix(false) == "-sin(1) * 0");
  CHECK(derivative->GetRPN() == "1 sin 0 * ~");
}

TEST_CASE("cos(x)", "Cos") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Cos>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "cos(x)");
  CHECK(result->GetRPN() == "x cos");

  CHECK(derivative->GetInfix(false) == "-sin(x) * 1");
  CHECK(derivative->GetRPN() == "x sin 1 * ~");
}

TEST_CASE("cos(x + 25.3)", "Cos") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Cos>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "cos(x + 25.3)");
  CHECK(result->GetRPN() == "x 25.3 + cos");

  CHECK(derivative->GetInfix(false) == "-sin(x + 25.3) * (1 + 0)");
  CHECK(derivative->GetRPN() == "x 25.3 + sin 1 0 + * ~");
}

TEST_CASE("cos(x) + 12", "Cos") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Cos>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "cos(x) + 12");
  CHECK(result->GetRPN() == "x cos 12 +");

  CHECK(derivative->GetInfix(false) == "-sin(x) * 1 + 0");
  CHECK(derivative->GetRPN() == "x sin 1 * ~ 0 +");
}

TEST_CASE("ln(1)", "Logarithm") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::Logarithm>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "ln(1)");
  CHECK(result->GetRPN() == "1 ln");

  CHECK(derivative->GetInfix(false) == "0 / 1");
  CHECK(derivative->GetRPN() == "0 1 /");
}

TEST_CASE("ln(x)", "Logarithm") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::Logarithm>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "ln(x)");
  CHECK(result->GetRPN() == "x ln");

  CHECK(derivative->GetInfix(false) == "1 / x");
  CHECK(derivative->GetRPN() == "1 x /");
}

TEST_CASE("ln(x + 25.3)", "Logarithm") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::Logarithm>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "ln(x + 25.3)");
  CHECK(result->GetRPN() == "x 25.3 + ln");

  CHECK(derivative->GetInfix(false) == "(1 + 0) / (x + 25.3)");
  CHECK(derivative->GetRPN() == "1 0 + x 25.3 + /");
}

TEST_CASE("ln(x) + 12", "Logarithm") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::Logarithm>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "ln(x) + 12");
  CHECK(result->GetRPN() == "x ln 12 +");

  CHECK(derivative->GetInfix(false) == "1 / x + 0");
  CHECK(derivative->GetRPN() == "1 x / 0 +");
}

TEST_CASE("sqrt(1)", "SquareRoot") {
  auto operand = std::make_shared<math::Number>(1);

  auto result = std::make_shared<math::SquareRoot>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sqrt(1)");
  CHECK(result->GetRPN() == "1 sqrt");

  CHECK(derivative->GetInfix(false) == "0 / (2 * sqrt(1))");
  CHECK(derivative->GetRPN() == "0 2 1 sqrt * /");
}

TEST_CASE("sqrt(x)", "SquareRoot") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result = std::make_shared<math::SquareRoot>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sqrt(x)");
  CHECK(result->GetRPN() == "x sqrt");

  CHECK(derivative->GetInfix(false) == "1 / (2 * sqrt(x))");
  CHECK(derivative->GetRPN() == "1 2 x sqrt * /");
}

TEST_CASE("sqrt(x + 25.3)", "SquareRoot") {
  auto operand =
      std::make_shared<math::Addition>(std::make_shared<math::Variable>('x'), std::make_shared<math::Number>(25.3));

  auto result = std::make_shared<math::SquareRoot>(operand);
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sqrt(x + 25.3)");
  CHECK(result->GetRPN() == "x 25.3 + sqrt");

  CHECK(derivative->GetInfix(false) == "(1 + 0) / (2 * sqrt(x + 25.3))");
  CHECK(derivative->GetRPN() == "1 0 + 2 x 25.3 + sqrt * /");
}

TEST_CASE("sqrt(x) + 12", "SquareRoot") {
  auto operand = std::make_shared<math::Variable>('x');

  auto result =
      std::make_shared<math::Addition>(std::make_shared<math::SquareRoot>(operand), std::make_shared<math::Number>(12));
  auto derivative = result->GetDerivative();

  CHECK(result->GetInfix(false) == "sqrt(x) + 12");
  CHECK(result->GetRPN() == "x sqrt 12 +");

  CHECK(derivative->GetInfix(false) == "1 / (2 * sqrt(x)) + 0");
  CHECK(derivative->GetRPN() == "1 2 x sqrt * / 0 +");
}