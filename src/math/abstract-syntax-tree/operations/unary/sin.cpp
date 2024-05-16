#include "sin.h"

namespace math {

std::string SinNode::GetInfix(int previous_priority,
                              const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kSin << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string SinNode::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kSin;
  return stream.str();
}

std::unique_ptr<TreeNode> SinNode::GetDerivative() {
  return std::make_unique<Multiplication>(std::make_unique<CosNode>(argument_->Clone()), argument_->GetDerivative());
}

Number SinNode::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  return std::sin(argument_->GetNumericResult(variable_to_value).GetValue());  // FIXME Функция SinNode
}

constants::Expressions SinNode::GetType() {
  return constants::Expressions::SIN;
}

std::optional<std::unique_ptr<TreeNode>> SinNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  return std::nullopt;
}

bool SinNode::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::unique_ptr<TreeNode> SinNode::Clone() {
  return std::make_unique<SinNode>(argument_->Clone());
}

}  // namespace math
