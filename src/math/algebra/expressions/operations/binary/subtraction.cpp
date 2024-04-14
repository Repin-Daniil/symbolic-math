#include "subtraction.h"

namespace math {

std::shared_ptr<Expression> Subtraction::GetDerivative() {
  return std::make_shared<Subtraction>(left_argument_->GetDerivative(), right_argument_->GetDerivative());
}

std::string Subtraction::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required = previous_priority >= priority_;
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "")
         << left_argument_->GetInfix(priority_, variable_to_value) << " " << constants::Labels::kMinus << " "
         << right_argument_->GetInfix(priority_, variable_to_value)
         << (brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string Subtraction::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << left_argument_->GetRPN(variable_to_value) << " " << right_argument_->GetRPN(variable_to_value) << " "
         << constants::Labels::kMinus;
  return stream.str();
}

double Subtraction::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetNumericResult(variable_to_value) - right_argument_->GetNumericResult(variable_to_value);
}

constants::Expressions Subtraction::GetType() {
  return constants::Expressions::SUBTRACTION;
}

std::optional<std::shared_ptr<Expression>> Subtraction::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = *simplified;
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = *simplified;
  }

  if (left_argument_->GetRPN({}) == right_argument_->GetRPN({})) {
    return std::make_shared<Number>(0);
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_shared<Number>(left_argument_->GetNumericResult({}) - right_argument_->GetNumericResult({}));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 0)) {
    return std::make_shared<UnaryMinus>(right_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 0)) {
    return left_argument_;
  }

  if (right_argument_->GetType() == constants::Expressions::UNARY_MINUS) {
    auto new_right = std::dynamic_pointer_cast<UnaryOperation>(right_argument_)->GetArgument();

    return std::make_shared<Addition>(left_argument_, new_right);
  }

  return std::nullopt;
}

bool Subtraction::IsContainVariable() {
  return left_argument_->IsContainVariable() || right_argument_->IsContainVariable();
}

}  // namespace math
