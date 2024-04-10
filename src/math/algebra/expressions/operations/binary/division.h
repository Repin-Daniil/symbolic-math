#pragma once

#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "exponentiation.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operations/binary_operation.h"
#include "multiplication.h"
#include "subtraction.h"

namespace math {

class Division final : public BinaryOperation {
 public:
  Division(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::DIVISION);
};

}  // namespace math
