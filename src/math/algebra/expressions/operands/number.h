#pragma once

#include <memory>
#include <string>
#include "math/algebra/expressions/expression.h"

namespace math {

class Number : public Expression {
 public:
  explicit Number(double value) : value_(value) {
  }

  std::string GetInfix() override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
  double value_;
};

}  // namespace math
