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
  SIN,
  COS,
  TANGENT,
  NATURAL_LOGARITHM,
};

struct Labels {
  constexpr static std::string_view kPlus = "+"sv;
  constexpr static std::string_view kMinus = "-"sv;
  constexpr static std::string_view kMultiplication = "*"sv;
  constexpr static std::string_view kDivision = "/"sv;
  constexpr static std::string_view kUnaryMinus = "~"sv;
  constexpr static std::string_view kExponentiation = "^"sv;
  constexpr static std::string_view kSin = "sin"sv;
  constexpr static std::string_view kCos = "cos"sv;
  constexpr static std::string_view kTan = "tan"sv;
  constexpr static std::string_view kTg = "tg"sv;
  constexpr static std::string_view kSquareRoot = "sqrt"sv;
  constexpr static std::string_view kLogarithm = "ln"sv;

  constexpr static std::string_view kOpenParen = "("sv;
  constexpr static std::string_view kEndParen = "("sv;

  constexpr static std::string_view kPi = "pi"sv;
  constexpr static std::string_view kE = "e"sv;

  constexpr static char kOpenParenChar = '(';
  constexpr static char kEndParenChar = ')';
  constexpr static char kDecimalComma = ',';
  constexpr static char kDecimalPoint = '.';
};

const std::unordered_map<std::string_view, Operations> char_to_operations{
    {Labels::kPlus, Operations::ADDITION},
    {Labels::kMinus, Operations::SUBTRACTION},
    {Labels::kMultiplication, Operations::MULTIPLICATION},
    {Labels::kDivision, Operations::DIVISION},
    {Labels::kExponentiation, Operations::EXPONENTIATION},
    {Labels::kLogarithm, Operations::NATURAL_LOGARITHM},
    {Labels::kSin, Operations::SIN},
    {Labels::kCos, Operations::COS},
    {Labels::kTan, Operations::TANGENT},
    {Labels::kTg, Operations::TANGENT},
    {Labels::kUnaryMinus, Operations::UNARY_MINUS},
    {Labels::kSquareRoot, Operations::SQRT}};

const std::unordered_map<Operations, int> operations_to_priority{{Operations::TANGENT, 4},
                                                                 {Operations::COS, 4},
                                                                 {Operations::SIN, 4},
                                                                 {Operations::SQRT, 4},
                                                                 {Operations::NATURAL_LOGARITHM, 4},
                                                                 {Operations::EXPONENTIATION, 3},
                                                                 {Operations::UNARY_MINUS, 2},
                                                                 {Operations::MULTIPLICATION, 1},
                                                                 {Operations::DIVISION, 1},
                                                                 {Operations::ADDITION, 0},
                                                                 {Operations::SUBTRACTION, 0}};

struct ExceptionMessage {
  ExceptionMessage() = delete;

  constexpr static std::string_view kEmptyExpression = "Empty expression!"sv;
  constexpr static std::string_view kZeroDivision = "Zero division!"sv;
  constexpr static std::string_view kNegativeRoot = "Negative square root"sv;
  constexpr static std::string_view kWrongTangent = "Tangent of pi/2"sv;
  constexpr static std::string_view kZeroLogarithm = "ln(0) = -inf"sv;
  constexpr static std::string_view kNoOperands = "No operands entered!"sv;
  constexpr static std::string_view kWrongFormat = "Wrong operator or operand format"sv;
  constexpr static std::string_view kUnbalancedBracket = "Wrong expression: Unbalanced bracket sequence"sv;
};

}  // namespace constants
