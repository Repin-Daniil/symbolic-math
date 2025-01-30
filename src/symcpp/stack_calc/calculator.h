#pragma once

#include <cmath>
#include <limits>
#include <numbers>
#include <optional>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "symcpp/constants_storage.h"
#include "symcpp/utils/helper/helper.h"

namespace symcpp::math {

class Calculator {
 public:
  double Calculate(std::string_view rpn_expression);
  void AddVariable(char symbol, double value);
  void Reset();

 private:
  void ExecuteOperation(constants::Operations operation);
  double GetOperand();

 private:
  std::stack<double> operands_;
  std::unordered_map<char, double> variables_;
};

}  // namespace symcpp::math
