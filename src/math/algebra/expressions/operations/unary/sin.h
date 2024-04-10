#pragma once

#include <cmath>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "cos.h"
#include "math/algebra/expressions/operations/binary/multiplication.h"
#include "math/algebra/expressions/operations/unary_operation.h"

namespace math {

class Sin final : public UnaryOperation {
 public:
  explicit Sin(std::shared_ptr<Expression> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
 public:
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::SIN);
};

}  // namespace math
