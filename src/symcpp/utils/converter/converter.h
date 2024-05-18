#pragma once

#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>

#include "symcpp/utils/helper/helper.h"

namespace symcpp::utils {

class Converter {
 public:
  static std::string ConvertInfixToRPN(std::string_view infix_expression);

 private:
  static bool IsPrefixFunction(std::size_t i, std::string_view infix_expression);
  static bool IsEndOfOperand(std::size_t i, std::string_view infix_expression);
  static bool IsUnary(std::size_t i, std::string_view infix_expression);

  static std::optional<std::string_view> ParseFunction(std::size_t i, std::string_view infix_expression);
  static bool IsEqual(std::size_t i, std::string_view infix_expression, std::string_view candidate);
};

}  // namespace symcpp::utils
