#include "tangent.h"

namespace math {

std::string TangentNode::GetInfix(int previous_priority,
                                  const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kTan << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string TangentNode::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kTan;
  return stream.str();
}

std::unique_ptr<TreeNode> TangentNode::GetDerivative() {
  CheckArgument({});

  return std::make_unique<Division>(
      argument_->GetDerivative(),
      std::make_unique<Exponentiation>(std::make_unique<CosNode>(argument_->Clone()), std::make_unique<NumberNode>(2)));
}

Number TangentNode::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  auto arg = CheckArgument(variable_to_value);

  return std::tan(arg->GetValue());  // FIXME Заменить на Tan
}

constants::Expressions TangentNode::GetType() {
  return constants::Expressions::TANGENT;
}

std::optional<std::unique_ptr<TreeNode>> TangentNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  return std::nullopt;
}

bool TangentNode::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::optional<Number> TangentNode::CheckArgument(
    const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value = {}) {
  std::optional<Number> result;

  if (!argument_->IsContainVariable()) {
    result = argument_->GetNumericResult({});
  } else if (!variable_to_value.empty()) {
    result = argument_->GetNumericResult(variable_to_value);
  }

  if (result && (std::abs(std::numbers::pi / 2.0 - std::fmod(result->GetValue(), std::numbers::pi)) <
                 std::numeric_limits<double>::epsilon())) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongTangent.data());
  }

  return result;
}

std::unique_ptr<TreeNode> TangentNode::Clone() {
  return std::make_unique<TangentNode>(argument_->Clone());
}

}  // namespace math
