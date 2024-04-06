#pragma once

#include <memory>
#include <string>
#include "math/algebra/expression.h"

namespace math {

class Number : public Expression {
 public:
  explicit Number(double value) : value_(value) {
  }

  std::string GetString() override;
  std::unique_ptr<Expression> GetDerivative() override;

 private:
  double value_;
};

}  // namespace math
