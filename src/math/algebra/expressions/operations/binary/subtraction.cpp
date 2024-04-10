#include "subtraction.h"

namespace math {

std::shared_ptr<Expression> Subtraction::GetDerivative() {
  return std::make_shared<Subtraction>(left_argument_->GetDerivative(), right_argument_->GetDerivative());
}

std::string Subtraction::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;

  return (brackets_required ? "(" : "") + left_argument_->GetInfix(priority_) + " - " +
         right_argument_->GetInfix(priority_) + (brackets_required ? ")" : "");
}

std::string Subtraction::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " -";
}

double Subtraction::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetNumericResult(variable_to_value) - right_argument_->GetNumericResult(variable_to_value);
}

}  // namespace math
