#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "utils/converter/converter.h"
#include "utils/converter/converter.h"  // check include guards

using utils::Converter;

TEST_CASE("3", "Converter") {
  std::string expression = "3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "3 ");
}

TEST_CASE("-1", "Converter") {
  std::string expression = "-1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 - "); // Calculator should interpret minus as unary
}

TEST_CASE("~1", "Converter") {
  std::string expression = "~1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 ~ ");
}

TEST_CASE("+1", "Converter") {
  std::string expression = "+1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 + ");
}

TEST_CASE("- 1", "Converter") {
  std::string expression = "- 1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 - "); // Calculator should interpret minus as unary
}

TEST_CASE("+ 1", "Converter") {
  std::string expression = "+ 1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 + "); // Calculator should interpret plus as unary
}

TEST_CASE("(- - 1)", "Converter") {
  std::string expression = "(- - 1)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 ~ ~ ");
}

TEST_CASE("- - 1", "Converter") {
  std::string expression = "- - 1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 ~ - "); // Calculator should interpret both minuses as unary
}

TEST_CASE("~-1", "Converter") {
  std::string expression = "~-1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 ~ ~ ");
}

TEST_CASE("+ + 1", "Converter") {
  std::string expression = "+ + 1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 + ");
}

TEST_CASE("- + 1", "Converter") {
  std::string expression = "- + 1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 - ");
}

TEST_CASE("+ - 1", "Converter") {
  std::string expression = "+ - 1";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 ~ + ");
}

TEST_CASE("(- + 1.25)", "Converter") {
  std::string expression = "(- + 1.25)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1.25 ~ ");
}

TEST_CASE("- + 1.25", "Converter") {
  std::string expression = "- + 1.25";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1.25 - ");
}

TEST_CASE("137", "Converter") {
  std::string expression = "137";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "137 ");
}

TEST_CASE("pi", "Converter") {
  std::string expression = "pi";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi ");
}

TEST_CASE("(-pi)", "Converter") {
  std::string expression = "(-pi)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi ~ ");
}

TEST_CASE("e", "Converter") {
  std::string expression = "e";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "e ");
}

TEST_CASE("(-e)", "Converter") {
  std::string expression = "(-e)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "e ~ ");
}

TEST_CASE("pi*e", "Converter") {
  std::string expression = "pi*e";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi e * ");
}

TEST_CASE("pi*-e", "Converter") {
  std::string expression = "pi*-e";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi e ~ * ");
}

TEST_CASE("1.25", "Converter") {
  std::string expression = "1.25";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1.25 ");
}

TEST_CASE("(-1.25)", "Converter") {
  std::string expression = "(-1.25)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1.25 ~ ");
}

TEST_CASE("1,25", "Converter") {
  std::string expression = "1,25";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1.25 ");
}

TEST_CASE("(-1,25)", "Converter") {
  std::string expression = "(-1,25)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1.25 ~ ");
}

TEST_CASE("1. ", "Converter") {
  std::string expression = "1. ";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1. ");
}

TEST_CASE("(-1. )", "Converter") {
  std::string expression = "(-1. )";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1. ~ ");
}

TEST_CASE("1, ", "Converter") {
  std::string expression = "1, ";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1. ");
}

TEST_CASE("2 + 3", "Converter") {
  std::string expression = "2 + 3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "2 3 + ");
}

TEST_CASE("(1 + 2)*4 + 3", "Converter") {
  std::string expression = "(1 + 2)*4 + 3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "1 2 + 4 * 3 + ");
}

TEST_CASE("5 - -3", "Converter") {
  std::string expression = "5 - -3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "5 3 ~ - ");
}

TEST_CASE("5^-3", "Converter") {
  std::string expression = "5^-3";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "5 3 ~ ^ ");
}

TEST_CASE("12^(sin(pi))", "Converter") {
  std::string expression = "12^(sin(pi))";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "12 pi sin ^ ");
}

TEST_CASE("3 + 4 * 2 / (1 - 5)^2", "Converter") {
  std::string expression = "3 + 4 * 2 / (1 - 5)^2";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "3 4 2 * 1 5 - 2 ^ / + ");
}

TEST_CASE("x", "Converter") {
  std::string expression = "x";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "x ");
}

TEST_CASE("(a + b)", "Converter") {
  std::string expression = "(a + b)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "a b + ");
}

TEST_CASE("(-(a + b))", "Converter") {
  std::string expression = "(-(a + b))";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "a b + ~ ");
}

TEST_CASE("(c-d)", "Converter") {
  std::string expression = "(c-d)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "c d - ");
}

TEST_CASE("(-(c-d))", "Converter") {
  std::string expression = "(-(c-d))";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "c d - ~ ");
}

TEST_CASE("h-i-j", "Converter") {
  std::string expression = "h-i-j";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "h i - j - ");
}

TEST_CASE("h-i--j", "Converter") {
  std::string expression = "h-i--j";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "h i - j ~ - ");
}

TEST_CASE("e * f", "Converter") {
  std::string expression = "e * f";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "e f * ");
}

TEST_CASE("e * -f", "Converter") {
  std::string expression = "e * -f";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "e f ~ * ");
}

TEST_CASE("(-e) * -f", "Converter") {
  std::string expression = "(-e) * -f";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "e ~ f ~ * ");
}

TEST_CASE("l/(m^n)", "Converter") {
  std::string expression = "l/(m^n)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "l m n ^ / ");
}

TEST_CASE("l/(m^-n)", "Converter") {
  std::string expression = "l/(m^-n)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "l m n ~ ^ / ");
}

TEST_CASE("o*p*q-r-s-t", "Converter") {
  std::string expression = "o*p*q-r-s-t";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "o p * q * r - s - t - ");
}

TEST_CASE("u-v/w/x-y-z", "Converter") {
  std::string expression = "u-v/w/x-y-z";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "u v w / x / - y - z - ");
}

TEST_CASE("((l/(m^n))*o)-p", "Converter") {
  std::string expression = "((l/(m^n))*o)-p";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "l m n ^ / o * p - ");
}

TEST_CASE("((v/w)^x)*(y-z)", "Converter") {
  std::string expression = "((v/w)^x)*(y-z)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "v w / x ^ y z - * ");
}

TEST_CASE("(a+g)*(((b-a)+c)^(c+(e*(d^f))))", "Converter") {
  std::string expression = "(a+g)*(((b-a)+c)^(c+(e*(d^f))))";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "a g + b a - c + c e d f ^ * + ^ * ");
}

TEST_CASE("((((a+b))))", "Converter") {
  std::string expression = "((((a+b))))";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "a b + ");
}

TEST_CASE("sin(pi)", "Converter") {
  std::string expression = "sin(pi)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi sin ");
}

TEST_CASE("sin(-pi)", "Converter") {
  std::string expression = "sin(-pi)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi ~ sin ");
}

TEST_CASE("sin(--pi)", "Converter") {
  std::string expression = "sin(--pi)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi ~ ~ sin ");
}

TEST_CASE("sin(pi/2)", "Converter") {
  std::string expression = "sin(pi/2)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi 2 / sin ");
}

TEST_CASE("sin(3,14)", "Converter") {
  std::string expression = "sin(3,14)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "3.14 sin ");
}

TEST_CASE("sin(3.14)", "Converter") {
  std::string expression = "sin(3.14)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "3.14 sin ");
}

TEST_CASE("sin(3.14/ pi)", "Converter") {
  std::string expression = "sin(3.14/ pi)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "3.14 pi / sin ");
}

TEST_CASE("tan(pi)", "Converter") {
  std::string expression = "tan(pi)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi tan ");
}

TEST_CASE("tg(pi)", "Converter") {
  std::string expression = "tg(pi)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi tg ");
}

TEST_CASE("ln(e)", "Converter") {
  std::string expression = "ln(e)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "e ln ");
}

TEST_CASE("ln(265)", "Converter") {
  std::string expression = "ln(265)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "265 ln ");
}

TEST_CASE("sin(cos(pi))", "Converter") {
  std::string expression = "sin(cos(pi))";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi cos sin ");
}

TEST_CASE("sin((cos(pi))^2)", "Converter") {
  std::string expression = "sin((cos(pi))^2)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi cos 2 ^ sin ");
}

TEST_CASE("sin(cos(pi)^2)", "Converter") {
  std::string expression = "sin(cos(pi)^2)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi cos 2 ^ sin ");
}

TEST_CASE("sin(cos(pi))^2", "Converter") {
  std::string expression = "sin((cos(pi)))^2";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi cos sin 2 ^ ");
}

TEST_CASE("13*ln(e)*(2+1)", "Converter") {
  std::string expression = "13*ln(e)*(2+1)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "13 e ln * 2 1 + * ");
}

TEST_CASE("ln(sin(pi)^2)", "Converter") {
  std::string expression = "ln(sin(pi)^2)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "pi sin 2 ^ ln ");
}

TEST_CASE("sqrt(4)", "Converter") {
  std::string expression = "sqrt(4)";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "4 sqrt ");
}

TEST_CASE("sqrt(4^2)^2", "Converter") {
  std::string expression = "sqrt(4^2)^2";

  auto rpn = Converter::ConvertInfixToRPN(expression);

  REQUIRE(rpn == "4 2 ^ sqrt 2 ^ ");
}

TEST_CASE("((a)", "Converter") {
  std::string expression = "((a)";

  CHECK_THROWS_WITH(Converter::ConvertInfixToRPN(expression), constants::ExceptionMessage::kUnbalancedBracket.data());
}

TEST_CASE("(a + b))*c", "Converter") {
  std::string expression = "(a + b))*c";

  CHECK_THROWS_WITH(Converter::ConvertInfixToRPN(expression), constants::ExceptionMessage::kUnbalancedBracket.data());
}

TEST_CASE(")*c", "Converter") {
  std::string expression = ")*c";

  CHECK_THROWS_WITH(Converter::ConvertInfixToRPN(expression), constants::ExceptionMessage::kUnbalancedBracket.data());
}