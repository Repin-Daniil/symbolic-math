#pragma once

#include <memory>
#include <string>
#include <utility>
#include "exponentiation.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operations/binary_operation.h"
#include "multiplication.h"
#include "substraction.h"

namespace math {

class Division final : public BinaryOperation {
 public:
  Division(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(bool brackets_required) override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;
};

}  // namespace math
