#pragma once

#include <memory>
#include <string>
#include <utility>

#include "math/algebra/expressions/operations/binary-operation.h"

namespace math {

class Addition final : public BinaryOperation {
 public:
  Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetString() override;
  std::shared_ptr<Expression> GetDerivative() override;
};

}  // namespace math
