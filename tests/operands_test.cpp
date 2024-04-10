#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "constants_storage.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operands/number.h"  // check include guards
#include "math/algebra/expressions/operands/variable.h"
#include "math/algebra/expressions/operands/variable.h"  // check include guards

TEST_CASE("3", "Number") {
  math::Number number(3);

  auto rpn = number.GetRPN({});
  auto infix = number.GetInfix(0, {});
  auto diff = number.GetDerivative();
  auto result = number.GetNumericResult({});

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  REQUIRE(result == 3);
  REQUIRE(diff->GetRPN({}) == "0");
  REQUIRE(diff->GetInfix(0, {}) == "0");
}

TEST_CASE("Polymorphic 3", "Number") {
  std::shared_ptr<math::Expression> number = std::make_shared<math::Number>(3);

  auto rpn = number->GetRPN({});
  auto infix = number->GetInfix(0, {});
  auto diff = number->GetDerivative();
  auto result = number->GetNumericResult({});

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  REQUIRE(result == 3);
  REQUIRE(diff->GetRPN({}) == "0");
  REQUIRE(diff->GetInfix(0, {}) == "0");
}

TEST_CASE("3.14", "Number") {
  math::Number number(3.14);

  auto rpn = number.GetRPN({});
  auto infix = number.GetInfix(0, {});
  auto diff = number.GetDerivative();
  auto result = number.GetNumericResult({});

  REQUIRE(rpn == "3.14");
  REQUIRE(infix == "3.14");
  REQUIRE(result == 3.14);
  REQUIRE(diff->GetRPN({}) == "0");
  REQUIRE(diff->GetInfix(0, {}) == "0");
}

TEST_CASE("-3.140", "Number") {
  math::Number number(-3.140);

  auto rpn = number.GetRPN({});
  auto infix = number.GetInfix(0, {});
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "3.14 ~");
  REQUIRE(infix == "-3.14");
  REQUIRE(diff->GetRPN({}) == "0");
  REQUIRE(diff->GetInfix(0, {}) == "0");
}

TEST_CASE("5.0034", "Number") {
  math::Number number(5.0034);

  auto rpn = number.GetRPN({});
  auto infix = number.GetInfix(0, {});
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "5.0034");
  REQUIRE(infix == "5.0034");
  REQUIRE(diff->GetRPN({}) == "0");
  REQUIRE(diff->GetInfix(0, {}) == "0");
}

TEST_CASE("-5.0034", "Number") {
  math::Number number(-5.0034);

  auto rpn = number.GetRPN({});
  auto infix = number.GetInfix(0, {});
  auto diff = number.GetDerivative();

  REQUIRE(rpn == "5.0034 ~");
  REQUIRE(infix == "-5.0034");
  REQUIRE(diff->GetRPN({}) == "0");
  REQUIRE(diff->GetInfix(0, {}) == "0");
}

TEST_CASE("5.0110", "Number") {
  math::Number number(5.0110);

  auto rpn = number.GetRPN({});
  auto infix = number.GetInfix(0, {});
  auto diff = number.GetDerivative();
  auto result = number.GetNumericResult({});

  REQUIRE(rpn == "5.011");
  REQUIRE(infix == "5.011");
  REQUIRE(result == 5.011);
  REQUIRE(diff->GetRPN({}) == "0");
  REQUIRE(diff->GetInfix(0, {}) == "0");
}

TEST_CASE("x", "Variable") {
  math::Variable var('x');

  auto rpn = var.GetRPN({{'x', 3}});
  auto infix = var.GetInfix(0, {{'x', 3}});
  auto diff = var.GetDerivative();
  auto result = var.GetNumericResult({{'x', 36}, {'y', 13.45}});

  REQUIRE(rpn == "3");
  REQUIRE(infix == "3");
  REQUIRE(result == 36);
  REQUIRE(diff->GetRPN({}) == "1");
  REQUIRE(diff->GetInfix(0, {}) == "1");
}

TEST_CASE("Polymorphic y", "Variable") {
  std::shared_ptr<math::Expression> var = std::make_shared<math::Variable>('y');

  auto rpn = var->GetRPN({});
  auto infix = var->GetInfix(0, {});
  auto result = var->GetNumericResult({{'x', 36}, {'y', 13.46}});
  auto diff = var->GetDerivative();

  REQUIRE(rpn == "y");
  REQUIRE(infix == "y");
  REQUIRE_THAT(result, Catch::Matchers::WithinRel(13.46, 1e-5));
  REQUIRE(diff->GetRPN({}) == "1");
  REQUIRE(diff->GetInfix(0, {}) == "1");
}

TEST_CASE("Unknown variable exception", "Variable") {
  math::Variable var('z');

  auto rpn = var.GetRPN({});
  auto infix = var.GetInfix(0, {});
  auto diff = var.GetDerivative();

  REQUIRE(rpn == "z");
  REQUIRE(infix == "z");
  REQUIRE(diff->GetRPN({}) == "1");
  REQUIRE(diff->GetInfix(0, {}) == "1");
  CHECK_THROWS_WITH(var.GetNumericResult({{'x', 36}, {'y', 13.46}}),
                    (std::string(constants::ExceptionMessage::kWrongFormat) + "z"));
}