#include "addition.h"

namespace math {

std::unique_ptr<TreeNode> Addition::GetDerivative() {
  return std::make_unique<Addition>(left_argument_->GetDerivative(), right_argument_->GetDerivative());
}

std::string Addition::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required = previous_priority > priority_;

  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "")
         << left_argument_->GetInfix(priority_, variable_to_value) << " " << constants::Labels::kPlus << " "
         << right_argument_->GetInfix(priority_, variable_to_value) << (brackets_required ? ")" : "");

  return stream.str();
}

std::string Addition::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << left_argument_->GetRPN(variable_to_value) << " " << right_argument_->GetRPN(variable_to_value) << " "
         << constants::Labels::kPlus;
  return stream.str();
}

double Addition::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetNumericResult(variable_to_value) + right_argument_->GetNumericResult(variable_to_value);
}

std::optional<std::unique_ptr<TreeNode>> Addition::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(*simplified);
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(*simplified);
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<Number>(left_argument_->GetNumericResult({}) + right_argument_->GetNumericResult({}));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 0)) {
    return std::move(right_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 0)) {
    return std::move(left_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::UNARY_MINUS) {
    auto new_right = dynamic_cast<UnaryOperation*>(right_argument_.get())->ReleaseArgument();

    return std::make_unique<Subtraction>(std::move(left_argument_), std::move(new_right));
  }

  return std::nullopt;
}

constants::Expressions Addition::GetType() {
  return constants::Expressions::ADDITION;
}

bool Addition::IsContainVariable() {
  return left_argument_->IsContainVariable() || right_argument_->IsContainVariable();
}

std::unique_ptr<TreeNode> Addition::Clone() {
  return std::make_unique<Addition>(left_argument_->Clone(), right_argument_->Clone());
}

}  // namespace math
