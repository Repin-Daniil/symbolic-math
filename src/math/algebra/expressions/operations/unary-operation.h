#pragma once

#include <memory>
#include "math/algebra/expression.h"

namespace math {

class UnaryOperation : public Expression {
 public:
  virtual Expression& GetArgument();

  virtual ~UnaryOperation() = default;

 protected:
  std::unique_ptr<Expression> argument_;
};

}  // namespace math
