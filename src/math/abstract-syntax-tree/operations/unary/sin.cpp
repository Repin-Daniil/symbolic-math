#include "sin.h"

namespace math {

std::string Sin::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kSin << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string Sin::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kSin;
  return stream.str();
}

std::unique_ptr<TreeNode> Sin::GetDerivative() {
  return std::make_unique<Multiplication>(std::make_unique<Cos>(argument_->Clone()), argument_->GetDerivative());
}

double Sin::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::sin(argument_->GetNumericResult(variable_to_value));
}

constants::Expressions Sin::GetType() {
  return constants::Expressions::SIN;
}

std::optional<std::unique_ptr<TreeNode>> Sin::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  return std::nullopt;
}

bool Sin::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::unique_ptr<TreeNode> Sin::Clone() {
  return std::make_unique<Sin>(argument_->Clone());
}

}  // namespace math
