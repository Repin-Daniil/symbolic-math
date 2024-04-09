#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operands/number.h"  // check include guards
#include "math/algebra/expressions/operands/variable.h"
#include "math/algebra/expressions/operands/variable.h"  // check include guards

TEST_CASE("3", "Number") {
  math::Number number(3);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix();
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix() == "0");
}

TEST_CASE("Polymorphic 3", "Number") {
  std::shared_ptr<math::Expression> number = std::make_shared<math::Number>(3);

  auto rpn = number->GetRPN();
  auto infix = number->GetInfix();
  auto diff = number->GetDerivative();

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix() == "0");
}

TEST_CASE("3.14", "Number") {
  math::Number number(3.14);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix();
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "3.14");
  REQUIRE(infix == "3.14");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix() == "0");
}

TEST_CASE("-3.140", "Number") {
  math::Number number(-3.140);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix();
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "-3.14");
  REQUIRE(infix == "-3.14");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix() == "0");
}

TEST_CASE("5.0034", "Number") {
  math::Number number(5.0034);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix();
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "5.0034");
  REQUIRE(infix == "5.0034");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix() == "0");
}

TEST_CASE("5.0110", "Number") {
  math::Number number(5.0110);

  auto rpn = number.GetRPN();
  auto infix = number.GetInfix();
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "5.011");
  REQUIRE(infix == "5.011");
  REQUIRE(diff->GetRPN() == "0");
  REQUIRE(diff->GetInfix() == "0");
}

// TODO GetValue()

TEST_CASE("x", "Variable") {
  math::Variable var('x');

  auto rpn = var.GetRPN();
  auto infix = var.GetInfix();
  auto diff = var.GetDerivative();

  REQUIRE(rpn == "x");
  REQUIRE(infix == "x");
  REQUIRE(diff->GetRPN() == "1");
  REQUIRE(diff->GetInfix() == "1");
}

TEST_CASE("y", "Variable") {
  math::Variable var('y');

  auto rpn = var.GetRPN();
  auto infix = var.GetInfix();
  auto diff = var.GetDerivative();

  REQUIRE(rpn == "y");
  REQUIRE(infix == "y");
  REQUIRE(diff->GetRPN() == "1");
  REQUIRE(diff->GetInfix() == "1");
}
