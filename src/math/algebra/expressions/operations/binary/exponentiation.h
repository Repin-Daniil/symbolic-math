#pragma once

#include <memory>
#include <string>
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

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::EXPONENTIATION);
};

}  // namespace math
