#include "number_node.h"

namespace math {

using namespace std::literals;

std::string NumberNode::GetInfix(int previous_priority,
                                 const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;

  stream << (brackets_required && (value_ < 0) ? constants::Labels::kOpenParen : "")
         << (value_ < 0 ? constants::Labels::kMinus : "") << value_
         << (brackets_required && (value_ < 0) ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string NumberNode::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;

  stream << value_ << (value_ < 0 ? " "s.append(constants::Labels::kUnaryMinus) : "");

  return stream.str();
}

std::unique_ptr<TreeNode> NumberNode::GetDerivative() {
  return std::make_unique<NumberNode>(0);
}

Number NumberNode::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  return value_;
}

constants::Expressions NumberNode::GetType() {
  return constants::Expressions::NUMBER;
}

std::optional<std::unique_ptr<TreeNode>> NumberNode::Simplify() {
  return std::nullopt;
}

bool NumberNode::IsContainVariable() {
  return false;
}

std::unique_ptr<TreeNode> NumberNode::Clone() {
  return std::make_unique<NumberNode>(value_);
}

}  // namespace math
