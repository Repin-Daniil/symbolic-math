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

 private:
  static double CalculateOperation(double lhs, double rhs, char op);

  static std::optional<double> ParseOperand(std::string_view);
  static bool IsDelimeter(char) noexcept;
  static bool IsOperator(char) noexcept;

 private:
  std::stack<double> operands_;
};

}  // namespace calc
