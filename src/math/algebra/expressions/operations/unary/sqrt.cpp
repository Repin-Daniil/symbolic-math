#include "sqrt.h"

namespace math {

std::string SquareRoot::GetInfix(bool brackets_required) {
  return "sqrt(" + argument_->GetInfix(false) + ")";
}

std::string SquareRoot::GetRPN() {
  return argument_->GetRPN() + " sqrt";
}

std::shared_ptr<Expression> SquareRoot::GetDerivative() {
  return std::make_shared<Division>(
      argument_->GetDerivative(),
      std::make_shared<Multiplication>(std::make_shared<Number>(2), std::make_shared<SquareRoot>(argument_)));
}

}  // namespace math
