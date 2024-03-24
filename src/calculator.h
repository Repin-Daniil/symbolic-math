#pragma once

#include <limits>
#include <optional>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "constants_storage.h"

namespace calc {

class RPN {
 public:
  double Calculate(std::string_view expression);
  void Reset();

  static double CalculateOperation(double lhs, double rhs, constants::Operations operation);

  static bool IsOperator(std::string_view) noexcept;
  static std::optional<double> ParseOperand(std::string_view) noexcept;
  static std::optional<constants::Operations> ParseOperation(std::string_view) noexcept;

 private:
  std::stack<double> operands_;
};

}  // namespace calc
