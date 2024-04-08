#include "substraction.h"

namespace math {

std::shared_ptr<Expression> Substraction::GetDerivative() {
  return std::shared_ptr<Expression>(
      new Substraction(left_argument_->GetDerivative(), right_argument_->GetDerivative()));
}

std::string Substraction::GetInfix() {
  return "(" + left_argument_->GetInfix() + " - " + right_argument_->GetInfix() + ")";
}

std::string Substraction::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " -";
}

}  // namespace math
