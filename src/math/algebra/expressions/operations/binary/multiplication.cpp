#include "multiplication.h"

namespace math {

std::string Multiplication::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required = previous_priority > priority_;

  return (brackets_required ? "(" : "") + left_argument_->GetInfix(priority_, variable_to_value) + " * " +
         right_argument_->GetInfix(priority_, variable_to_value) + (brackets_required ? ")" : "");
}

std::string Multiplication::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetRPN(variable_to_value) + " " + right_argument_->GetRPN(variable_to_value) + " *";
}

std::shared_ptr<Expression> Multiplication::GetDerivative() {
  return std::make_shared<Addition>(std::make_shared<Multiplication>(left_argument_, right_argument_->GetDerivative()),
                                    std::make_shared<Multiplication>(left_argument_->GetDerivative(), right_argument_));
}
double Multiplication::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetNumericResult(variable_to_value) * right_argument_->GetNumericResult(variable_to_value);
}
Expressions Multiplication::GetType() {
  return Expressions::MULTIPLICATION;
}

std::optional<std::shared_ptr<Expression>> Multiplication::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = *simplified;
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = *simplified;
  }

  if (left_argument_->GetType() == right_argument_->GetType() && left_argument_->GetType() == Expressions::NUMBER) {
    return std::make_shared<Number>(GetNumericResult({}));
  }

  if (left_argument_->GetType() == Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 0)) {
    return std::make_shared<Number>(0);
  }

  if (right_argument_->GetType() == Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 0)) {
    return std::make_shared<Number>(0);
  }

  if (left_argument_->GetType() == Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 1)) {
    return right_argument_;
  }

  if (right_argument_->GetType() == Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 1)) {
    return left_argument_;
  }

  return std::nullopt;
}

bool Multiplication::IsContainVariable() {
  return left_argument_->IsContainVariable() || right_argument_->IsContainVariable();
}

}  // namespace math
