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
#include "utils/helper/helper.h"

namespace math {

class Calculator {
 public:
  double Calculate(std::string_view expression);
  void Reset();

  static bool IsEqual(double lhs, double rhs);

 private:
  void ExecuteOperation(constants::Operations operation);
  double GetOperand();

 private:
  std::stack<double> operands_;
};

}  // namespace math
