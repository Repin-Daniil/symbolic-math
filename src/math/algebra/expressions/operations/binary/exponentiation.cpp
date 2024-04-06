#include "exponentiation.h"
#include "addition.h"
#include "division.h"
#include "math/algebra/expressions/operations/unary/logarithm.h"
#include "multiplication.h"

namespace math {

std::string Exponentiation::GetString() {
  return left_argument_->GetString() + " ^ " + right_argument_->GetString();
}

std::shared_ptr<Expression> Exponentiation::GetDerivative() {
  auto first = std::make_shared<Exponentiation>(left_argument_, right_argument_);
  auto second = std::make_shared<Addition>(
      std::make_shared<Multiplication>(right_argument_->GetDerivative(), std::make_shared<Logarithm>(left_argument_)),
      std::make_shared<Division>(std::make_shared<Multiplication>(right_argument_, left_argument_->GetDerivative()),
                                 left_argument_));
  return std::make_shared<Multiplication>(first, second);
}

}  // namespace math
