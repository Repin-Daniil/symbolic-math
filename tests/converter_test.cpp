#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "infrastructure/converter/converter.h"
#include "infrastructure/converter/converter.h"  // check include guards

using infrastructure::Converter;

TEST_CASE("3", "Converter") {
  std::string expression = "3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "3");
}

TEST_CASE("2 + 3", "Converter") {
  std::string expression = "2 + 3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "2 3 +");
}

TEST_CASE("(1 + 2)*4 + 3", "Converter") {
  std::string expression = "(1 + 2)*4 + 3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 2 + 4 × 3 +");
}