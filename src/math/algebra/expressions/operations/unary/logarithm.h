#pragma once

#include <memory>
#include <string>
#include <utility>
#include "math/algebra/expressions/operations/binary/division.h"
#include "math/algebra/expressions/operations/unary_operation.h"

namespace math {

class Logarithm final : public UnaryOperation {
 public:
  explicit Logarithm(std::shared_ptr<Expression> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetInfix(bool brackets_required) override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;
};

}  // namespace math
