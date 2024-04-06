#include "substraction.h"

namespace math {

std::shared_ptr<Expression> Substraction::GetDerivative() {
  return std::shared_ptr<Expression>(
      new Substraction(left_argument_->GetDerivative(), right_argument_->GetDerivative()));
}

std::string Substraction::GetString() {
  return left_argument_->GetString() + " - " + right_argument_->GetString();
}

}  // namespace math
