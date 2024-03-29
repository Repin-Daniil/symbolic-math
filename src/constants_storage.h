#pragma once

#include <string_view>
#include <unordered_map>

namespace constants {

using namespace std::literals;

enum class Operations {
  UNARY_MINUS,
  ADDITION,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  EXPONENTIATION,
  SQRT,
  SINE,
  COSINE,
  TANGENS,
  NATURAL_LOGARITHM,
};

struct ConstantsLabels {
  constexpr static std::string_view kPi = "pi"sv;
  constexpr static std::string_view kE = "e"sv;
};

const std::unordered_map<std::string_view, Operations> char_to_operations{
    {"+"sv, Operations::ADDITION},       {"-"sv, Operations::SUBTRACTION},        {"*"sv, Operations::MULTIPLICATION},
    {"×"sv, Operations::MULTIPLICATION}, {"/"sv, Operations::DIVISION},           {"÷"sv, Operations::DIVISION},
    {"^"sv, Operations::EXPONENTIATION}, {"ln"sv, Operations::NATURAL_LOGARITHM}, {"sin"sv, Operations::SINE},
    {"cos"sv, Operations::COSINE},       {"tg"sv, Operations::TANGENS},           {"tan"sv, Operations::TANGENS},
    {"~"sv, Operations::UNARY_MINUS},    {"±"sv, Operations::UNARY_MINUS},        {"√"sv, Operations::SQRT},
    {"sqrt"sv, Operations::SQRT}};

const std::unordered_map<Operations, int> operations_to_priority{
      {Operations::EXPONENTIATION, 10},
      {Operations::UNARY_MINUS, 9},
      {Operations::MULTIPLICATION, 8},
      {Operations::DIVISION, 8},
      {Operations::ADDITION, 7},
      {Operations::SUBTRACTION, 7}
};

struct ExceptionMessage {
  ExceptionMessage() = delete;

  constexpr static std::string_view kEmptyExpression = "Empty expression!"sv;
  constexpr static std::string_view kZeroDivision = "Zero division!"sv;
  constexpr static std::string_view kNegativeRoot = "Negative square root"sv;
  constexpr static std::string_view kWrongTangens = "Tangens of pi/2"sv;
  constexpr static std::string_view kZeroLogarithm = "ln(0) = -inf"sv;
  constexpr static std::string_view kNoOperands = "No operands entered!"sv;
  constexpr static std::string_view kWrongFormat = "Wrong operator or operand format"sv;
};

}  // namespace constants
