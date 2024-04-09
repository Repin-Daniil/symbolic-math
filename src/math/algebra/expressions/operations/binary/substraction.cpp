#include "substraction.h"

namespace math {

std::shared_ptr<Expression> Substraction::GetDerivative() {
  return std::make_shared<Substraction>(left_argument_->GetDerivative(), right_argument_->GetDerivative());
}

std::string Substraction::GetInfix(bool brackets_required) {
  return (brackets_required ? "(" : "") + left_argument_->GetInfix(false) + " - " + right_argument_->GetInfix(true) +
         (brackets_required ? ")" : "");
}

std::string Substraction::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " -";
}

}  // namespace math
