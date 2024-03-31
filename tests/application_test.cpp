#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "app/application.h"
#include "app/application.h"  // check include guards

TEST_CASE("Simple Test", "RPN") {
  app::Application application;
  std::string input = "3";

  auto ans = application.Handle(input);

  REQUIRE(ans.answer == 3);
}

TEST_CASE("Minus with single operand is unary", "RPN") {
  app::Application application;
  std::string input_1 = "3";
  std::string input_2 = "-";

  auto ans_1 = application.Handle(input_1);
  auto ans_2 = application.Handle(input_2);

  REQUIRE(ans_1.answer == 3);
  REQUIRE(ans_2.answer == -3);
}

TEST_CASE("Correct expression with int", "RPN") {
  app::Application application;
  std::string input = "2 + 3";

  auto ans = application.Handle(input);

  REQUIRE(ans.answer == 5);
}

TEST_CASE("Correct expression with double", "RPN") {
  app::Application application;
  std::string input = "2.5 + 3";

  auto ans = application.Handle(input);

  REQUIRE_THAT(*ans.answer, Catch::Matchers::WithinRel(5.5, 1e-5));
}

TEST_CASE("Three expressions", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "-3"; // Not Unary
  std::string input_3 = "1 + 1";

  auto ans_1 = application.Handle(input_1);
  auto ans_2 = application.Handle(input_2);
  auto ans_3 = application.Handle(input_3);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_2.answer == 2);
  REQUIRE(ans_3.answer == 2);
}

TEST_CASE("Three different expressions", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "~3";
  std::string input_3 = "1 + 1";

  auto ans_1 = application.Handle(input_1);
  auto ans_2 = application.Handle(input_2);
  auto ans_3 = application.Handle(input_3);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_2.answer == -3);
  REQUIRE(ans_3.answer == 2);
}

TEST_CASE("Unary minus at beginning", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "-3";

  auto ans_1 = application.Handle(input_1);
  auto ans_2 = application.Handle(input_2);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_2.answer == 2);
}

TEST_CASE("ln(e ^ 4) + sin(pi / 2) + cos(pi / 3)", "RPN") {
  app::Application application;
  std::string input_1 = "ln(e ^ 4) + sin(pi / 2)";
  std::string input_2 = " + cos(pi / 3)";

  auto ans_1 = application.Handle(input_1);
  auto ans_2 = application.Handle(input_2);

  REQUIRE(ans_1.answer == 5);
  REQUIRE_THAT(*ans_2.answer, Catch::Matchers::WithinAbs(5.5, 1e-5));
}

TEST_CASE("Reset test", "RPN") {
  app::Application application;
  std::string input_1 = "2 + 3";
  std::string input_2 = "Reset";
  std::string input_3 = "1 + 1";

  auto ans_1 = application.Handle(input_1);
  auto ans_2 = application.Handle(input_2);
  auto ans_3 = application.Handle(input_3);

  REQUIRE(ans_1.answer == 5);
  REQUIRE(ans_2.answer == std::nullopt);
  REQUIRE(ans_3.answer == 2);
}

TEST_CASE("Expression with constants", "RPN") {
  app::Application application;
  std::string input_1 = "sin(pi)";
  std::string input_2 = "*pi";

  auto ans_1 = application.Handle(input_1);
  auto ans_2 = application.Handle(input_2);

  REQUIRE_THAT(*ans_1.answer, Catch::Matchers::WithinAbs(0, 1e-5));
  REQUIRE_THAT(*ans_2.answer, Catch::Matchers::WithinAbs(0, 1e-5));
}