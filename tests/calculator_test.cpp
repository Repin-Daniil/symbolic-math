#include "calculator.h"
#include "calculator.h"  // check include guards

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

TEST_CASE("3 4 +", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "3 4 +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 7);
}

TEST_CASE("1 2 + 4 × 3 +", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "1 2 + 4 * 3 +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 15);
}

TEST_CASE("7 2 3 × −", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "7 2 3 * -";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 1);
}

TEST_CASE("8 9 + 1 7 - ×", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "8 9 + 1 7 - *";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == -102);
}

TEST_CASE("1 2 /", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "1 2 /";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 0.5);
}

TEST_CASE("1 2 ×", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "1 2 *";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 2);
}

TEST_CASE("1 2 +", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "1 2 +";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == 3);
}

TEST_CASE("1 2 -", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "1 2 -";

  auto ans = calc.Calculate(expression);

  REQUIRE(ans == -1);
}

TEST_CASE("CheckCalcMemory", "[RPN]") {
  calc::Calculator calc;
  std::string expression_1 = "1 2 +";
  std::string expression_2 = "1 -";

  auto ans_1 = calc.Calculate(expression_1);
  REQUIRE(ans_1 == 3);
  auto ans_2 = calc.Calculate(expression_2);
  REQUIRE(ans_2 == 2);
}

TEST_CASE("ZeroAddition", "[RPN]") {
  calc::Calculator calc;
  std::string expression_1 = "1 1 -";
  std::string expression_2 = "0 +";

  auto ans_1 = calc.Calculate(expression_1);
  REQUIRE(ans_1 == 0);
  auto ans_2 = calc.Calculate(expression_2);
  REQUIRE(ans_2 == 0);
}

TEST_CASE("ResetTest", "[RPN]") {
  calc::Calculator calc;
  std::string expression_1 = "1 5 -";
  std::string expression_2 = "1 2 +";

  auto ans_1 = calc.Calculate(expression_1);
  REQUIRE(ans_1 == -4);

  calc.Reset();

  auto ans_2 = calc.Calculate(expression_2);
  REQUIRE(ans_2 == 3);
}

TEST_CASE("EmptyString", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kEmptyExpression.data());
}

TEST_CASE("NoOperandsEntered", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "+";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kNoOperands.data());
}

TEST_CASE("OnlyOneOperandEntered", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "1 +";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kNoOperands.data());
}

TEST_CASE("WrongOperandFormat", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "bca abc +";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kWrongFormat.data());
}

TEST_CASE("ZeroDivision", "[RPN]") {
  calc::Calculator calc;
  std::string expression = "1 0 /";

  CHECK_THROWS_WITH(calc.Calculate(expression), constants::ExceptionMessage::kZeroDivision.data());
}
