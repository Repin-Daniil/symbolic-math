#include "multiplication.h"

namespace math {

std::string Multiplication::GetString() {
  return left_argument_->GetString() + " * " + right_argument_->GetString();
}

std::shared_ptr<Expression> Multiplication::GetDerivative() {
  return std::shared_ptr<Expression>(
      new Addition(std::make_shared<Multiplication>(left_argument_, right_argument_->GetDerivative()),
                   std::make_shared<Multiplication>(left_argument_->GetDerivative(), right_argument_)));
}

}  // namespace math
