#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "math/algebra/expressions/expression.h"

namespace math {

class BinaryOperation : public Expression {
 public:
  BinaryOperation(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
      : left_argument_(std::move(left)), right_argument_(std::move(right)) {
  }

  virtual std::unique_ptr<Expression> ReleaseLeftArgument();
  virtual std::unique_ptr<Expression> ReleaseRightArgument();

  virtual ~BinaryOperation() = default;

 protected:
  std::unique_ptr<Expression> left_argument_;
  std::unique_ptr<Expression> right_argument_;
};

}  // namespace math
