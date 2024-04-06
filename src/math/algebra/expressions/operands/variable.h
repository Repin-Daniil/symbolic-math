#pragma once

#include <memory>
#include <string>

#include "math/algebra/expression.h"
#include "number.h"

namespace math {

class Variable : public Expression {
 public:
  explicit Variable(std::string symbol) : symbol_(symbol) {
  }

  std::string GetString() override;
  std::unique_ptr<Expression> GetDerivative() override;

 private:
  std::string symbol_;
};

}  // namespace math
