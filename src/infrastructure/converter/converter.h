#pragma once

#include <sstream>
#include <stack>
#include <string>

#include "calc/parser/parser.h"

namespace infrastructure {

class Converter {
 public:
  static std::string ConvertInfixToRPN(std::string_view infix_expression);

 private:
  static int GetPriority(std::string_view operation);

  static bool IsPrefixFunction(size_t i, std::string_view infix_expression);
  static bool IsOperator(size_t i, std::string_view infix_expression);
  static bool IsEndOfOperand(size_t i, std::string_view infix_expression);
  static bool IsEndOfConstant(size_t i, std::string_view infix_expression);

  static std::optional<std::string_view> ParseFunction(size_t i, std::string_view infix_expression);
};

}  // namespace infrastructure
