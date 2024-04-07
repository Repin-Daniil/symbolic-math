#include "division.h"

namespace math {

std::string Division::GetInfix() {
  return left_argument_->GetInfix() + " / " + right_argument_->GetInfix();
}

std::string Division::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " /";
}

std::shared_ptr<Expression> Division::GetDerivative() {
  auto numerator = std::make_shared<Substraction>(
      std::make_shared<Multiplication>(left_argument_->GetDerivative(), right_argument_),
      std::make_shared<Multiplication>(left_argument_, right_argument_->GetDerivative()));
  auto denominator = std::make_shared<Exponentiation>(left_argument_, std::make_shared<Number>(2));
  return std::shared_ptr<Expression>(new Division(numerator, denominator));
}

}  // namespace math
