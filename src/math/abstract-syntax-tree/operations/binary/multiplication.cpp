#include "multiplication.h"

namespace math {

std::string Multiplication::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required = previous_priority > priority_;

  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "")
         << left_argument_->GetInfix(priority_, variable_to_value) << " " << constants::Labels::kMultiplication << " "
         << right_argument_->GetInfix(priority_, variable_to_value)
         << (brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string Multiplication::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << left_argument_->GetRPN(variable_to_value) + " " + right_argument_->GetRPN(variable_to_value) << " "
         << constants::Labels::kMultiplication;
  return stream.str();
}

std::unique_ptr<TreeNode> Multiplication::GetDerivative() {
  return std::make_unique<Addition>(
      std::make_unique<Multiplication>(left_argument_->Clone(), right_argument_->GetDerivative()),
      std::make_unique<Multiplication>(left_argument_->GetDerivative(), right_argument_->Clone()));
}

double Multiplication::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetNumericResult(variable_to_value) * right_argument_->GetNumericResult(variable_to_value);
}

constants::Expressions Multiplication::GetType() {
  return constants::Expressions::MULTIPLICATION;
}

std::optional<std::unique_ptr<TreeNode>> Multiplication::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(*simplified);
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(*simplified);
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<Number>(GetNumericResult({}));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 0)) {
    return std::make_unique<Number>(0);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 0)) {
    return std::make_unique<Number>(0);
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 1)) {
    return std::move(right_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 1)) {
    return std::move(left_argument_);
  }

  return std::nullopt;
}

bool Multiplication::IsContainVariable() {
  return left_argument_->IsContainVariable() || right_argument_->IsContainVariable();
}

std::unique_ptr<TreeNode> Multiplication::Clone() {
  return std::make_unique<Multiplication>(left_argument_->Clone(), right_argument_->Clone());
}

}  // namespace math
