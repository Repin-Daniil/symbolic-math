#include <limits>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/calc/calculator.h"
#include "math/calc/calculator.h"  // check include guards

TEST_CASE("3", "RPN") {
  math::Calculator calc;
  std::string expression = "3";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("3.15", "RPN") {
  math::Calculator calc;
  std::string expression = "3.15";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(3.15, 1e-5));
}

TEST_CASE("3.", "RPN") {
  math::Calculator calc;
  std::string expression = "3.";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(3., 1e-5));
}

TEST_CASE("3,", "RPN") {
  math::Calculator calc;
  std::string expression = "3,";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(3., 1e-5));
}

TEST_CASE("3 4", "RPN") {
  math::Calculator calc;
  std::string expression = "3 4";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 4);
}

TEST_CASE("3 ~", "RPN") {
  math::Calculator calc;
  std::string expression = "3 ~";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == -3);
}

TEST_CASE("3 -", "RPN") {
  math::Calculator calc;
  std::string expression = "3 -";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == -3);
}

TEST_CASE("3 +", "RPN") {
  math::Calculator calc;
  std::string expression = "3 +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("3 + +", "RPN") {
  math::Calculator calc;
  std::string expression = "3 + +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("3 ~ ~", "RPN") {
  math::Calculator calc;
  std::string expression = "3 ~ ~";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("3 - -", "RPN") {
  math::Calculator calc;
  std::string expression = "3 - -";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("3 ~ -", "RPN") {
  math::Calculator calc;
  std::string expression = "3 ~ -";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("pi", "RPN") {
  math::Calculator calc;
  std::string expression = "pi";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == std::numbers::pi);
}

TEST_CASE("e", "RPN") {
  math::Calculator calc;
  std::string expression = "e";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == std::numbers::e);
}

TEST_CASE("3 4 +", "[RPN]") {
  math::Calculator calc;
  std::string expression = "3 4 +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 7);
}

TEST_CASE("3.5 4.25 +", "[RPN]") {
  math::Calculator calc;
  std::string expression = "3.5 4.25 +";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(7.75, 1e-5));
}

TEST_CASE("1 2 + 4 * 3 +", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 2 + 4 * 3 +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 15);
}

TEST_CASE("7 2 3 * −", "[RPN]") {
  math::Calculator calc;
  std::string expression = "7 2 3 * -";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 1);
}

TEST_CASE("8 9 + 1 7 - *", "[RPN]") {
  math::Calculator calc;
  std::string expression = "8 9 + 1 7 - *";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == -102);
}

TEST_CASE("1 2 /", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 2 /";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 0.5);
}

TEST_CASE("1 2 *", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 2 *";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 2);
}

TEST_CASE("1 2 +", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 2 +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("1 2 -", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 2 -";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == -1);
}

TEST_CASE("1.5 2 /", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1.5 2 /";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(0.75, 1e-5));
}

TEST_CASE("1.5 1.5 *", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1.5 1.5 *";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(2.25, 1e-5));
}

TEST_CASE("1.5 0.75 -", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1.5 0.75 /";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(2., 1e-5));
}

TEST_CASE("2 3 ^", "[RPN]") {
  math::Calculator calc;
  std::string expression = "2 3 ^";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 8);
}

TEST_CASE("1.5 2 ^", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1.5 2 ^";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(2.25, 1e-5));
}

TEST_CASE("2 0 ^", "[RPN]") {
  math::Calculator calc;
  std::string expression = "2 0 ^";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 1);
}

TEST_CASE("4 0.5 ^", "[RPN]") {
  math::Calculator calc;
  std::string expression = "4 0.5 ^";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 2);
}

TEST_CASE("2 0 1 - ^", "[RPN]") {
  math::Calculator calc;
  std::string expression = "2 0 1 - ^";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 0.5);
}

TEST_CASE("4 sqrt", "[RPN]") {
  math::Calculator calc;
  std::string expression = "4 sqrt";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 2);
}

TEST_CASE("2.25 sqrt", "[RPN]") {
  math::Calculator calc;
  std::string expression = "2.25 sqrt";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinAbs(1.5, 1e-5));
}

TEST_CASE("0 sqrt", "[RPN]") {
  math::Calculator calc;
  std::string expression = "0 sqrt";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 0);
}

TEST_CASE("0 sin", "[RPN]") {
  math::Calculator calc;
  std::string expression = "0 sin";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 0);
}

TEST_CASE("pi sin", "[RPN]") {
  math::Calculator calc;
  std::string expression = "pi sin";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinAbs(0., 1e-5));
}

TEST_CASE("pi cos", "[RPN]") {
  math::Calculator calc;
  std::string expression = "pi cos";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(-1.0, 1e-5));
}

TEST_CASE("0 cos", "[RPN]") {
  math::Calculator calc;
  std::string expression = "0 cos";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 1);
}

TEST_CASE("pi 4 / tg", "[RPN]") {
  math::Calculator calc;
  std::string expression = "pi 4 / tg";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinRel(1.0, 1e-5));
}

TEST_CASE("pi tg", "[RPN]") {
  math::Calculator calc;
  std::string expression = "pi tg";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("pi tan", "[RPN]") {
  math::Calculator calc;
  std::string expression = "pi tan";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("0 tg", "[RPN]") {
  math::Calculator calc;
  std::string expression = "0 tg";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("1 ln", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 ln";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 0);
}

TEST_CASE("2.71 ln", "[RPN]") {
  math::Calculator calc;
  std::string expression = "2.71 ln";

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinAbs(1., 0.1));
}

TEST_CASE("x ln, x = e", "[RPN]") {
  math::Calculator calc;
  std::string expression = "x ln";
  calc.AddVariable('x', std::numbers::e);

  auto ans = calc.Calculate(expression);

  REQUIRE_THAT(ans, Catch::Matchers::WithinAbs(1., 0.1));
}

TEST_CASE("a b ^, a = 2, b = 3", "[RPN]") {
  math::Calculator calc;
  std::string expression = "a b ^";
  calc.AddVariable('a', 2.);
  calc.AddVariable('b', 3.);

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 8);
}

TEST_CASE("2 3 ^, a = 4, b = 3", "[RPN]") {
  math::Calculator calc;
  std::string expression = "2 3 ^";
  calc.AddVariable('a', 4.);
  calc.AddVariable('b', 3.);

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 8);
}

TEST_CASE("CheckCalcMemory", "[RPN]") {
  math::Calculator calc;
  std::string expression_1 = "1 2 +";
  std::string expression_2 = "1 -";

  auto ans_1 = calc.Calculate(expression_1);
  REQUIRE(ans_1 == 3);
  auto ans_2 = calc.Calculate(expression_2);
  REQUIRE(ans_2 == 2);
}

TEST_CASE("ZeroAddition", "[RPN]") {
  math::Calculator calc;
  std::string expression_1 = "1 1 -";
  std::string expression_2 = "0 +";

  auto ans_1 = calc.Calculate(expression_1);
  REQUIRE(ans_1 == 0);
  auto ans_2 = calc.Calculate(expression_2);
  REQUIRE(ans_2 == 0);
}

TEST_CASE("ResetTest", "[RPN]") {
  math::Calculator calc;
  std::string expression_1 = "1 5 -";
  std::string expression_2 = "1 2 +";

  auto ans_1 = calc.Calculate(expression_1);
  REQUIRE(ans_1 == -4);

  calc.Reset();

  auto ans_2 = calc.Calculate(expression_2);
  REQUIRE(ans_2 == 3);
}

TEST_CASE("EmptyString", "[RPN]") {
  math::Calculator calc;
  std::string expression;

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kEmptyExpression.data());
}

TEST_CASE("NoOperandsEntered", "[RPN]") {
  math::Calculator calc;
  std::string expression = "+";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kNoOperands.data());
}

TEST_CASE("OnlyOneOperandEntered", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 *";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kNoOperands.data());
}

TEST_CASE("WrongOperandFormat", "[RPN]") {
  math::Calculator calc;
  std::string expression = "bca abc +";

  CHECK_THROWS_WITH(calc.Calculate(expression), std::string(constants::ExceptionMessage::kWrongFormat.data()) + "bca");
}

TEST_CASE("ZeroDivision", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 0 /";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kZeroDivision.data());
}

TEST_CASE("ZeroInLogarithm", "[RPN]") {
  math::Calculator calc;
  std::string expression = "0 ln";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kZeroLogarithm.data());
}

TEST_CASE("TangensPi/2", "[RPN]") {
  math::Calculator calc;
  std::string expression = "pi 2 / tg";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kWrongTangent.data());
}

TEST_CASE("NegativeSQRT", "[RPN]") {
  math::Calculator calc;
  std::string expression = "1 ~ sqrt";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kNegativeRoot.data());
}