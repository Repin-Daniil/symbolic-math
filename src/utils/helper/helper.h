#pragma once

#include <limits>
#include <optional>
#include <string>
#include <string_view>

#include "constants_storage.h"

namespace utils {

class Helper {
 public:
  static std::optional<int> GetPriority(std::string_view operation);
  static bool ComparePriorities(std::string_view lhs, std::string_view rhs);

  static bool IsEqual(double lhs, double rhs);
  static bool IsOperator(std::string_view input) noexcept;
  static bool IsOperandPart(char symbol) noexcept;
  static bool IsDecimalDelimiter(char symbol) noexcept;
  static bool IsSign(std::string_view operation) noexcept;
  static bool IsUnaryOperation(constants::Operations operation) noexcept;
  static bool IsBinaryOperation(constants::Operations operation) noexcept;

  static std::optional<double> ParseOperand(std::string_view) noexcept;
  static std::optional<constants::Operations> ParseOperation(std::string_view) noexcept;
};

}  // namespace utils
