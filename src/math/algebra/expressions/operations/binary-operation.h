#pragma once

#include <memory>
#include <utility>
#include "math/algebra/expression.h"

namespace math {

class BinaryOperation : public Expression {
 public:
  BinaryOperation(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
      : left_argument_(std::move(left)), right_argument_(std::move(right)) {
  }
  virtual Expression& GetLeftArgument();  // TODO Законстантить бы все это и ссылку, и метод
  virtual Expression& GetRightArgument();

  virtual ~BinaryOperation() = default;

 protected:
  std::unique_ptr<Expression> left_argument_;
  std::unique_ptr<Expression> right_argument_;
};

}  // namespace math
