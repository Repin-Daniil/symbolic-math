#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "symcpp/abstract-syntax-tree/operands/number_node.h"
#include "symcpp/abstract-syntax-tree/operands/number_node.h"  // check include guards
#include "symcpp/abstract-syntax-tree/operands/variable_node.h"
#include "symcpp/abstract-syntax-tree/operands/variable_node.h"  // check include guards
#include "symcpp/constants_storage.h"

TEST_CASE("3", "NumberNode") {
  symcpp::math::NumberNode number(3);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix(0);
  auto diff = number.GetDerivative('x');
  //  auto result = number.GetNumericResult({});

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  //  REQUIRE(result == 3);
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix(0) == "0");
}

TEST_CASE("Polymorphic 3", "NumberNode") {
  std::unique_ptr<symcpp::math::TreeNode> number = std::make_unique<symcpp::math::NumberNode>(3);

  auto rpn = number->GetRPN();
  auto infix = number->GetInfix(0);
  auto diff = number->GetDerivative('x');
  ////  auto result = number->GetNumericResult({});

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  ////  REQUIRE(result == 3);
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix(0) == "0");
}

TEST_CASE("3.14", "NumberNode") {
  symcpp::math::NumberNode number(3.14);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix(0);
  auto diff = number.GetDerivative('x');
  ////  auto result = number.GetNumericResult({});

  REQUIRE(rpn == "3.14");
  REQUIRE(infix == "3.14");
  //  REQUIRE(result == 3.14);
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix(0) == "0");
}

TEST_CASE("-3.140", "NumberNode") {
  symcpp::math::NumberNode number(-3.140);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix(0);
  auto diff = number.GetDerivative('x');

  REQUIRE(rpn == "3.14 ~");
  REQUIRE(infix == "-3.14");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix(0) == "0");
}

TEST_CASE("5.0034", "NumberNode") {
  symcpp::math::NumberNode number(5.0034);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix(0);
  auto diff = number.GetDerivative('x');

  REQUIRE(rpn == "5.0034");
  REQUIRE(infix == "5.0034");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix(0) == "0");
}

TEST_CASE("-5.0034", "NumberNode") {
  symcpp::math::NumberNode number(-5.0034);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix(0);
  auto diff = number.GetDerivative('x');

  REQUIRE(rpn == "5.0034 ~");
  REQUIRE(infix == "-5.0034");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix(0) == "0");
}

TEST_CASE("5.0110", "NumberNode") {
  symcpp::math::NumberNode number(5.0110);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix(0);
  auto diff = number.GetDerivative('x');
  //  auto result = number.GetNumericResult({});

  REQUIRE(rpn == "5.011");
  REQUIRE(infix == "5.011");
  //  REQUIRE(result == 5.011);
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix(0) == "0");
}

TEST_CASE("x", "Variable") {
  symcpp::Symbol x('x');
  symcpp::math::Variable var(x);
  x = 3;

  auto rpn = var.GetRPN();
  auto infix = var.GetInfix(0);
  auto diff = var.GetDerivative('x');
  //  auto result = var.GetNumericResult({{'x', 36}, {'y', 13.45}});

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  //  REQUIRE(result == 36);
  REQUIRE(diff->GetRPN() == "1");
  REQUIRE(diff->GetInfix(0) == "1");
}

TEST_CASE("Polymorphic y", "Variable") {
  std::unique_ptr<symcpp::math::TreeNode> var = std::make_unique<symcpp::math::Variable>('y');

  auto rpn = var->GetRPN();
  auto infix = var->GetInfix(0);
  //  auto result = var->GetNumericResult({{'x', 36}, {'y', 13.46}});
  auto diff = var->GetDerivative('y');

  REQUIRE(rpn == "y");
  REQUIRE(infix == "y");
  //  REQUIRE_THAT(result, Catch::Matchers::WithinRel(13.46, 1e-5));
  REQUIRE(diff->GetRPN() == "1");
  REQUIRE(diff->GetInfix(0) == "1");
}

TEST_CASE("Unknown variable exception", "Variable") {
  symcpp::math::Variable var('z');

  auto rpn = var.GetRPN();
  auto infix = var.GetInfix(0);
  auto diff = var.GetDerivative('z');

  REQUIRE(rpn == "z");
  REQUIRE(infix == "z");
  REQUIRE(diff->GetRPN() == "1");
  REQUIRE(diff->GetInfix(0) == "1");
  //  CHECK_THROWS_WITH(var.GetNumericResult({{'x', 36}, {'y', 13.46}}),
  //                    (std::string(constants::ExceptionMessage::kWrongFormat) + "z"));
}