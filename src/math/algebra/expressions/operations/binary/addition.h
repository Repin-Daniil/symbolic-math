#pragma once

#include <memory>
#include <string>
#include <utility>

#include "math/algebra/expressions/operations/binary-operation.h"

namespace math {

class Addition final : public BinaryOperation {
 public:
  Addition(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetString() override;
  std::unique_ptr<Expression> GetDerivative() override;
};

}  // namespace math
