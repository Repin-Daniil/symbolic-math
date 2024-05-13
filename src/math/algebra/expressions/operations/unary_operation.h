#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "math/algebra/expressions/expression.h"

namespace math {

class UnaryOperation : public Expression {
 public:
  explicit UnaryOperation(std::unique_ptr<Expression> argument) : argument_(std::move(argument)) {
  }

  virtual std::unique_ptr<Expression> ReleaseArgument();

  virtual ~UnaryOperation() = default;

 protected:
  std::unique_ptr<Expression> argument_;
};

}  // namespace math
