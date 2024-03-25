#pragma once

#include <string>

namespace infrastructure {

class Converter {
 public:
  static std::string ConvertInfixToRPN(std::string_view infix_expression);
};

}  // namespace infrastructure
