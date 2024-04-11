#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "math/algebra/expressions/expression.h"

namespace math {

class BinaryOperation : public Expression {
 public:
  BinaryOperation(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : left_argument_(std::move(left)), right_argument_(std::move(right)) {
  }

  virtual std::shared_ptr<Expression> GetLeftArgument();  // TODO Законстантить бы все это и ссылку, и метод
  virtual std::shared_ptr<Expression> GetRightArgument();

  virtual ~BinaryOperation() = default;

 protected:
  std::shared_ptr<Expression> left_argument_;
  std::shared_ptr<Expression> right_argument_;
};

}  // namespace math
