#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "addition.h"
#include "division.h"
#include "math/algebra/expressions/operations/binary_operation.h"
#include "math/algebra/expressions/operations/unary/logarithm.h"
#include "multiplication.h"

namespace math {

class Exponentiation final : public BinaryOperation {
 public:
  Exponentiation(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
 public:
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::EXPONENTIATION);
};

}  // namespace math
