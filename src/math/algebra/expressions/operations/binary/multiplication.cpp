#include "multiplication.h"

namespace math {

std::string Multiplication::GetInfix(bool brackets_required) {
  return (brackets_required ? "(" : "") + left_argument_->GetInfix(true) + " * " + right_argument_->GetInfix(true) +
         (brackets_required ? ")" : "");
}

std::string Multiplication::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " *";
}

std::shared_ptr<Expression> Multiplication::GetDerivative() {
  return std::make_shared<Addition>(std::make_shared<Multiplication>(left_argument_, right_argument_->GetDerivative()),
                                    std::make_shared<Multiplication>(left_argument_->GetDerivative(), right_argument_));
}

}  // namespace math
