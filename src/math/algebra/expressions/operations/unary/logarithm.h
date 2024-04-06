#pragma once

#include <memory>
#include <string>
#include <utility>
#include "math/algebra/expressions/operations/unary-operation.h"

namespace math {

class Logarithm final : public UnaryOperation {
 public:
  explicit Logarithm(std::shared_ptr<Expression> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetString() override;
  std::shared_ptr<Expression> GetDerivative() override;
};

}  // namespace math
