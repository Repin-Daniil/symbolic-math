#include "addition.h"

namespace math {

std::shared_ptr<Expression> Addition::GetDerivative() {
  return std::shared_ptr<Expression>(new Addition(left_argument_->GetDerivative(), right_argument_->GetDerivative()));
}

std::string Addition::GetInfix() {
  return left_argument_->GetInfix() + " + " + right_argument_->GetInfix();
}

std::string Addition::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " +";
}

}  // namespace math
