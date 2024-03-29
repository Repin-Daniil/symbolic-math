#pragma once

#include <optional>
#include <string>
#include <string_view>

#include "constants_storage.h"

namespace calc {

class Parser {
 public:
  static bool IsOperator(std::string_view) noexcept;
  static bool IsFunction(constants::Operations operation) noexcept;
  static bool IsUnaryOperation(constants::Operations operation) noexcept;
  static bool IsBinaryOperation(constants::Operations operation) noexcept;
  static std::optional<double> ParseOperand(std::string_view) noexcept;
  static std::optional<constants::Operations> ParseOperation(std::string_view) noexcept;
};

}  // namespace calc
