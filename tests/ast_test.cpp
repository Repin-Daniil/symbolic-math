#define CATCH_CONFIG_MAIN
#include "utils/abstract-syntax-tree/ast.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operands/variable.h"
#include "math/algebra/expressions/operations/binary/addition.h"
#include "math/algebra/expressions/operations/binary/multiplication.h"
#include "utils/converter/converter.h"

TEST_CASE("Simple shared_ptr constructor test", "AST") {
  auto left_operand = std::make_unique<math::Number>(2);
  auto right_operand =
      std::make_unique<math::Addition>(std::make_unique<math::Variable>('x'), std::make_unique<math::Number>(1));

  std::unique_ptr<math::Expression> root =
      std::make_unique<math::Multiplication>(std::move(left_operand), std::move(right_operand));

  utils::AbstractSyntaxTree ast(std::move(root));
  CHECK(ast.GetInfixExpression({}) == "2 * (x + 1)");
  CHECK(ast.GetRPNExpression({}) == "2 x 1 + *");
  CHECK(ast.GetNumericResult({{'x', 12}}) == 26);
  CHECK(ast.GetDerivative().GetNumericResult({{'x', 0}}) == 2);
}

TEST_CASE("y = kx + b", "AST") {
  std::string parab = "x^2";
  std::string tan = "k*x + b";
  utils::AbstractSyntaxTree parabola(utils::Converter::ConvertInfixToRPN(parab));
  utils::AbstractSyntaxTree tangent(utils::Converter::ConvertInfixToRPN(tan));

  CHECK(parabola.GetNumericResult({{'x', 0}}) == 0);
  CHECK(parabola.GetNumericResult({{'x', 4}}) == 16);

  double x1 = 4;
  double k1 = parabola.GetDerivative().GetNumericResult({{'x', x1}});
  double b1 = parabola.GetNumericResult({{'x', x1}}) - k1 * x1;

  CHECK(tangent.GetNumericResult({{'x', x1}, {'k', k1}, {'b', b1}}) == 16);

  double x2 = 1;
  double k2 = parabola.GetDerivative().GetNumericResult({{'x', x2}});
  double b2 = parabola.GetNumericResult({{'x', x2}}) - k2 * x2;
  CHECK(tangent.GetNumericResult({{'x', x2}, {'k', k2}, {'b', b2}}) == 1);
}

TEST_CASE("EmptyString", "[RPN]") {
  std::string expression;

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression), constants::ExceptionMessage::kEmptyExpression.data());
}

TEST_CASE("NoOperandsEntered", "[RPN]") {
  std::string expression = "+";

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression), constants::ExceptionMessage::kNoOperands.data());
}

TEST_CASE("OnlyOneOperandEntered", "[RPN]") {
  std::string expression = "1 *";

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression), constants::ExceptionMessage::kNoOperands.data());
}

TEST_CASE("WrongOperandFormat", "[RPN]") {
  std::string expression = "bca abc +";

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression),
                    std::string(constants::ExceptionMessage::kWrongFormat.data()) + "bca");
}

TEST_CASE("ZeroDivision", "[RPN]") {
  std::string expression = "1 0 /";

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression).GetNumericResult({}),
                    constants::ExceptionMessage::kZeroDivision.data());
}

TEST_CASE("ZeroInLogarithm", "[RPN]") {
  std::string expression = "0 ln";

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression).GetNumericResult({}),
                    constants::ExceptionMessage::kWrongLogarithm.data());
}

TEST_CASE("TangensPi/2", "[RPN]") {
  std::string expression = "pi 2 / tg";

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression).GetNumericResult({}),
                    constants::ExceptionMessage::kWrongTangent.data());
}

TEST_CASE("NegativeSQRT", "[RPN]") {
  std::string expression = "1 ~ sqrt";

  CHECK_THROWS_WITH(utils::AbstractSyntaxTree(expression).GetNumericResult({}),
                    constants::ExceptionMessage::kNegativeRoot.data());
}