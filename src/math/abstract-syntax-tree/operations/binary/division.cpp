#include "division.h"

namespace math {

std::string Division::GetInfix(int previous_priority,
                               const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  bool brackets_required = previous_priority >= priority_;
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "")
         << left_argument_->GetInfix(priority_, variable_to_value) << " " << constants::Labels::kDivision << " "
         << right_argument_->GetInfix(priority_, variable_to_value)
         << (brackets_required ? constants::Labels::kEndParen : "");
  return stream.str();
}

std::string Division::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << left_argument_->GetRPN(variable_to_value) << " " << right_argument_->GetRPN(variable_to_value) << " "
         << constants::Labels::kDivision;
  return stream.str();
}

std::unique_ptr<TreeNode> Division::GetDerivative() {
  CheckDivider({});

  auto numerator = std::make_unique<Subtraction>(
      std::make_unique<Multiplication>(left_argument_->GetDerivative(), right_argument_->Clone()),
      std::make_unique<Multiplication>(left_argument_->Clone(), right_argument_->GetDerivative()));
  auto denominator = std::make_unique<Exponentiation>(right_argument_->Clone(), std::make_unique<NumberNode>(2));
  return std::make_unique<Division>(std::move(numerator), std::move(denominator));
}

Number Division::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  auto divisible = left_argument_->GetNumericResult(variable_to_value);
  auto divider = *CheckDivider(variable_to_value);

  return divisible / divider;
}

constants::Expressions Division::GetType() {
  return constants::Expressions::DIVISION;
}

std::optional<std::unique_ptr<TreeNode>> Division::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(*simplified);
  }

  CheckDivider({});

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(*simplified);
  }

  if (left_argument_->GetRPN({}) == right_argument_->GetRPN({})) {
    return std::make_unique<NumberNode>(1);
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 0)) {
    return std::make_unique<NumberNode>(0);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 1)) {
    return ReleaseLeftArgument();
  }

  return std::nullopt;
}

bool Division::IsContainVariable() {
  return left_argument_->IsContainVariable() || right_argument_->IsContainVariable();
}

std::optional<Number> Division::CheckDivider(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::optional<Number> result;

  if (!right_argument_->IsContainVariable()) {
    result = right_argument_->GetNumericResult({});
  } else if (!variable_to_value.empty()) {
    result = right_argument_->GetNumericResult(variable_to_value);
  }

  if (result && utils::Helper::IsEqual(*result, 0)) {
    throw std::runtime_error(constants::ExceptionMessage::kZeroDivision.data());
  }

  return result;
}

std::unique_ptr<TreeNode> Division::Clone() {
  return std::make_unique<Division>(left_argument_->Clone(), right_argument_->Clone());
}

}  // namespace math
