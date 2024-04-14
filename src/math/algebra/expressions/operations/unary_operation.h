#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "math/algebra/expressions/expression.h"

namespace math {

class UnaryOperation : public Expression {
 public:
  explicit UnaryOperation(std::shared_ptr<Expression> argument) : argument_(std::move(argument)) {
  }

  virtual std::shared_ptr<Expression> GetArgument();

  virtual ~UnaryOperation() = default;

 protected:
  std::shared_ptr<Expression> argument_;
};

}  // namespace math
