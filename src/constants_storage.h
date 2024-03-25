#pragma once

#include <string_view>
#include <unordered_map>

namespace constants {

using namespace std::literals;

enum class Operations {
  ADDITION,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  EXPONENTIATION,
  SINE,
  COSINE,
  NATURAL_LOGARITHM
};

struct ConstantsLabels {
  constexpr static std::string_view kPi = "pi"sv;
  constexpr static std::string_view kE = "e"sv;
};

const std::unordered_map<std::string_view, Operations> char_to_operations{
    {"+"sv, Operations::ADDITION}, {"-"sv, Operations::SUBTRACTION},       {"*"sv, Operations::MULTIPLICATION},
    {"/"sv, Operations::DIVISION}, {"^"sv, Operations::EXPONENTIATION},    {"sin"sv, Operations::SINE},
    {"cos"sv, Operations::COSINE}, {"ln"sv, Operations::NATURAL_LOGARITHM}};

struct ExceptionMessage {
  ExceptionMessage() = delete;

  constexpr static std::string_view kEmptyExpression = "Empty expression!"sv;
  constexpr static std::string_view kZeroDivision = "Zero division!"sv;
  constexpr static std::string_view kZeroLogarithm = "ln(0) = -inf"sv;
  constexpr static std::string_view kNoOperands = "No operands entered!"sv;
  constexpr static std::string_view kWrongFormat = "Wrong operator or operand format"sv;
};

}  // namespace constants
