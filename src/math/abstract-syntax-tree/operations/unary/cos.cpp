#include "cos.h"

namespace math {

std::string CosNode::GetInfix(int previous_priority,
                              const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kCos << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;

  return stream.str();
}

std::string CosNode::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kCos;
  return stream.str();
}

std::unique_ptr<TreeNode> CosNode::GetDerivative() {
  return std::make_unique<UnaryMinus>(
      std::make_unique<Multiplication>(std::make_unique<SinNode>(argument_->Clone()), argument_->GetDerivative()));
}

Number CosNode::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  return std::cos(argument_->GetNumericResult(variable_to_value).GetValue());  // FIXME Функция CosNode
}

constants::Expressions CosNode::GetType() {
  return constants::Expressions::COS;
}

std::optional<std::unique_ptr<TreeNode>> CosNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  return std::nullopt;
}

bool CosNode::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::unique_ptr<TreeNode> CosNode::Clone() {
  return std::make_unique<CosNode>(argument_->Clone());
}

}  // namespace math
