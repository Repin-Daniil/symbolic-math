#pragma once

#include <cmath>
#include <limits>
#include <optional>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "constants_storage.h"
#include "parser/parser.h"

namespace calc {

class Calculator {
 public:
  double Calculate(std::string_view expression);
  void Reset();

  static bool IsEqual(double lhs, double rhs);

 private:
  void ExecuteOperation(constants::Operations operation);
  double GetOperand();
  static bool IsUnaryOperation(constants::Operations operation) noexcept;

 private:
  std::stack<double> operands_;
};

}  // namespace calc
