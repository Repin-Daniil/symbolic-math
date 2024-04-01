#pragma once

#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>

#include "utils/helper/helper.h"

namespace utils {

class Converter {
 public:
  static std::string ConvertInfixToRPN(std::string_view infix_expression);

 private:
  static bool IsPrefixFunction(size_t i, std::string_view infix_expression);
  static bool IsEndOfOperand(size_t i, std::string_view infix_expression);
  static bool IsEndOfConstant(size_t i, std::string_view infix_expression);
  static bool IsUnary(size_t i, std::string_view infix_expression);

  static bool ComparePriorities(std::string_view, std::string_view);

  static std::optional<std::string_view> ParseFunction(size_t i, std::string_view infix_expression);
};

}  // namespace utils
