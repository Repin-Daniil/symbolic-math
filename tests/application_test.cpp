#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "app/application.h"
#include "app/application.h"  // check include guards

TEST_CASE("Simple Test", "RPN") {
  app::Application application;
  std::string input = "3";

  auto ans = application.Calculate(input);

  REQUIRE(ans.answer == 3);
}

TEST_CASE("Minus with single operand is unary", "RPN") {
  app::Application application;
  std::string input_1 = "3";
  std::string input_2 = "-";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);

  REQUIRE(ans_1.answer == 3);
  REQUIRE(ans_2.answer == -3);
}

TEST_CASE("Correct expression with int", "RPN") {
  app::Application application;
  std::string input = "2 + 3";

  auto ans = application.Calculate(input);

  REQUIRE(ans.answer == 5);
}

TEST_CASE("Correct expression with double", "RPN") {
  app::Application application;
  std::string input = "2.5 + 3";

  auto ans = application.Calculate(input);

  REQUIRE_THAT(ans.answer, Catch::Matchers::WithinRel(5.5, 1e-5));
}

TEST_CASE("Three expressions", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "-3";  // Not Unary
  std::string input_3 = "1 + 1";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);
  auto ans_3 = application.Calculate(input_3);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_2.answer == 2);
  REQUIRE(ans_3.answer == 2);
}

TEST_CASE("Three different expressions", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "~3";
  std::string input_3 = "1 + 1";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);
  auto ans_3 = application.Calculate(input_3);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_2.answer == -3);
  REQUIRE(ans_3.answer == 2);
}

TEST_CASE("Unary minus at beginning", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "-3";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_2.answer == 2);
}

TEST_CASE("ln(e ^ 4) + sin(pi / 2) + cos(pi / 3)", "RPN") {
  app::Application application;
  std::string input_1 = "ln(e ^ 4) + sin(pi / 2)";
  std::string input_2 = " + cos(pi / 3)";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);

  REQUIRE(ans_1.answer == 5);
  REQUIRE_THAT(ans_2.answer, Catch::Matchers::WithinAbs(5.5, 1e-5));
}

TEST_CASE("2^2^3", "RPN") {
  app::Application application;
  std::string input_1 = "2^2^3";

  auto ans_1 = application.Calculate(input_1);

  REQUIRE(ans_1.answer == 256);
}

TEST_CASE("Test with mem", "RPN") {
  app::Application application;
  std::string input_1 = "-(-(-(-1)))";
  std::string input_2 = "2+3";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);

  REQUIRE(ans_1.answer == 1);
  REQUIRE(ans_2.answer == 5);
}

TEST_CASE("Reset test", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "Reset";
  std::string input_3 = "1 + 1";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);
  auto ans_3 = application.Calculate(input_3);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_3.answer == 2);
}

TEST_CASE("Expression with constants", "RPN") {
  app::Application application;
  std::string input_1 = "sin(pi)";
  std::string input_2 = "*pi";

  auto ans_1 = application.Calculate(input_1);
  auto ans_2 = application.Calculate(input_2);

  REQUIRE_THAT(ans_1.answer, Catch::Matchers::WithinAbs(0, 1e-5));
  REQUIRE_THAT(ans_2.answer, Catch::Matchers::WithinAbs(0, 1e-5));
}

TEST_CASE("EmptyExpression", "RPN") {
  app::Application application;
  std::string input = "";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kEmptyExpression);
}

TEST_CASE("ZeroDivision", "RPN") {
  app::Application application;
  std::string input = "1/0";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kZeroDivision);
}

TEST_CASE("NegativeRoot", "RPN") {
  app::Application application;
  std::string input = "sqrt(-1)";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kNegativeRoot);
}

TEST_CASE("Wrong Tangent", "RPN") {
  app::Application application;
  std::string input = "tan(pi/2)";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kWrongTangent);
}

TEST_CASE("Zero Logarithm", "RPN") {
  app::Application application;
  std::string input = "ln(0)";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kZeroLogarithm);
}

TEST_CASE("No Operands", "RPN") {
  app::Application application;
  std::string input = "+";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kNoOperands);
}

TEST_CASE("No Operands without brackets", "RPN") {
  app::Application application;
  std::string input = "sqrt";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kNoOperands);
}

TEST_CASE("No Operands in brackets", "RPN") {
  app::Application application;
  std::string input = "sin()";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kNoOperands);
}

TEST_CASE("Wrong Format", "RPN") {
  app::Application application;
  std::string input = "sin(p)";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == (std::string(constants::ExceptionMessage::kWrongFormat) + "p"));
}

TEST_CASE("Unbalanced Bracket", "RPN") {
  app::Application application;
  std::string input = "sin(pi";

  auto ans = application.Calculate(input);

  REQUIRE(ans.error.has_value());
  REQUIRE(ans.error == constants::ExceptionMessage::kUnbalancedBracket);
}

TEST_CASE("App alive after exception", "RPN") {
  app::Application application;
  std::string wrong_input = "tan(pi/2)";
  std::string correct_input = "sin(pi)";

  auto ans_1 = application.Calculate(wrong_input);
  auto ans_2 = application.Calculate(correct_input);

  REQUIRE(ans_1.error.has_value());
  REQUIRE(ans_1.error == constants::ExceptionMessage::kWrongTangent);
  REQUIRE_THAT(ans_2.answer, Catch::Matchers::WithinAbs(0, 1e-5));
}
