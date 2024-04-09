#include "exponentiation.h"

namespace math {

std::string Exponentiation::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;

  return (brackets_required ? "(" : "") + left_argument_->GetInfix(priority_) + " ^ " +
         right_argument_->GetInfix(priority_) + (brackets_required ? ")" : "");
}

std::string Exponentiation::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " ^";
}

std::shared_ptr<Expression> Exponentiation::GetDerivative() {
  auto first = std::make_shared<Exponentiation>(left_argument_, right_argument_);
  auto second = std::make_shared<Addition>(
      std::make_shared<Multiplication>(right_argument_->GetDerivative(), std::make_shared<Logarithm>(left_argument_)),
      std::make_shared<Division>(std::make_shared<Multiplication>(right_argument_, left_argument_->GetDerivative()),
                                 left_argument_));
  return std::make_shared<Multiplication>(first, second);
}
double Exponentiation::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::pow(left_argument_->GetNumericResult(variable_to_value),
                  right_argument_->GetNumericResult(variable_to_value));
}

}  // namespace math
