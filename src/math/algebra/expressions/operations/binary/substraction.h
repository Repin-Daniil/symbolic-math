#pragma once

#include <memory>
#include <string>
#include <utility>

#include "constants_storage.h"
#include "math/algebra/expressions/operations/binary_operation.h"

namespace math {

class Substraction final : public BinaryOperation {
 public:
  Substraction(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::SUBSTRACTION);
};

}  // namespace math
