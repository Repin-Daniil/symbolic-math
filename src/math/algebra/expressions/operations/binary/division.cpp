#include "division.h"
#include "exponentiation.h"
#include "math/algebra/expressions/operands/number.h"
#include "multiplication.h"
#include "substraction.h"

namespace math {

std::string Division::GetString() {
  return left_argument_->GetString() + " / " + right_argument_->GetString();
}

std::shared_ptr<Expression> Division::GetDerivative() {
  auto numerator = std::make_shared<Substraction>(
      std::make_shared<Multiplication>(left_argument_->GetDerivative(), right_argument_),
      std::make_shared<Multiplication>(left_argument_, right_argument_->GetDerivative()));
  auto denominator = std::make_shared<Exponentiation>(left_argument_, std::make_shared<Number>(2));
  return std::shared_ptr<Expression>(new Division(numerator, denominator));
}

}  // namespace math
