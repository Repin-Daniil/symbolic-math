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
  Labels() = delete;

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

const std::unordered_map<Operations, int> operations_to_priority{{Operations::TANGENT, 6},
                                                                 {Operations::COS, 6},
                                                                 {Operations::SIN, 6},
                                                                 {Operations::SQRT, 6},
                                                                 {Operations::NATURAL_LOGARITHM, 6},
                                                                 {Operations::EXPONENTIATION, 5},
                                                                 {Operations::UNARY_MINUS, 4},
                                                                 {Operations::DIVISION, 4},
                                                                 {Operations::MULTIPLICATION, 3},
                                                                 {Operations::SUBTRACTION, 2},
                                                                 {Operations::ADDITION, 1}};
struct ExceptionMessage {
  ExceptionMessage() = delete;

  constexpr static std::string_view kEmptyExpression = "Empty expression!"sv;
  constexpr static std::string_view kZeroDivision = "Zero division!"sv;
  constexpr static std::string_view kNegativeRoot = "Negative square root"sv;
  constexpr static std::string_view kWrongTangent = "Tangent of pi/2"sv;
  constexpr static std::string_view kWrongLogarithm = "Ln argument must be positive"sv;
  constexpr static std::string_view kNoOperands = "No operands entered!"sv;
  constexpr static std::string_view kWrongFormat = "Unknown operator or variable: "sv;
  constexpr static std::string_view kUnbalancedBracket = "Wrong expression: Unbalanced bracket sequence"sv;
};

}  // namespace constants
