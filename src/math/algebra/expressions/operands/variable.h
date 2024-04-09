#pragma once

#include <memory>
#include <string>

#include "math/algebra/expressions/expression.h"
#include "number.h"

namespace math {

class Variable : public Expression {
 public:
  explicit Variable(char symbol) : symbol_(symbol) {
  }

  std::string GetInfix(bool brackets_required) override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
  std::string GetString() const noexcept;

 private:
  char symbol_;
};

}  // namespace math
