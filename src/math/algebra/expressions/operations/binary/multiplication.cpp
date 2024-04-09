#include "multiplication.h"

namespace math {

std::string Multiplication::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;

  return (brackets_required ? "(" : "") + left_argument_->GetInfix(priority_) + " * " +
         right_argument_->GetInfix(priority_) + (brackets_required ? ")" : "");
}

std::string Multiplication::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " *";
}

std::shared_ptr<Expression> Multiplication::GetDerivative() {
  return std::make_shared<Addition>(std::make_shared<Multiplication>(left_argument_, right_argument_->GetDerivative()),
                                    std::make_shared<Multiplication>(left_argument_->GetDerivative(), right_argument_));
}

}  // namespace math
