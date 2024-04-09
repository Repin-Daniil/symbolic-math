#pragma once

#include <cmath>
#include <limits>
#include <optional>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "constants_storage.h"
#include "utils/helper/helper.h"

namespace math {

class Calculator {
 public:
  double Calculate(std::string_view rpn_expression);
  void AddVariable(char symbol, double value);
  void Reset();

 private:
  void ExecuteOperation(constants::Operations operation);
  double GetOperand();
  static bool IsEqual(double lhs, double rhs);

 private:
  std::stack<double> operands_;
  std::unordered_map<char, double> variables_;
};

}  // namespace math
