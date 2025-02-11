#include "number_node.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace symcpp::math {

using namespace std::literals;

std::string NumberNode::GetLatex(int previous_priority) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;

  stream << (brackets_required && (value_ < 0) ? constants::Labels::kOpenParen : "") << value_
         << (brackets_required && (value_ < 0) ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string NumberNode::GetInfix(int previous_priority) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;

  stream << (brackets_required && (value_ < 0) ? constants::Labels::kOpenParen : "") << value_
         << (brackets_required && (value_ < 0) ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string NumberNode::GetRPN() {
  std::stringstream stream;

  stream << std::abs(value_.GetValue()) << (value_ < 0 ? " "s.append(constants::Labels::kUnaryMinus) : "");

  return stream.str();
}

std::unique_ptr<TreeNode> NumberNode::GetDerivative(const Symbol& d) {
  return std::make_unique<NumberNode>(0);
}

constants::Expressions NumberNode::GetType() {
  return constants::Expressions::NUMBER;
}

std::unique_ptr<TreeNode> NumberNode::Simplify() {
  return nullptr;
}

bool NumberNode::IsContainVariable(const Symbol& variable) {
  return false;
}

bool NumberNode::IsA(constants::Expressions node_type) {
  return node_type == constants::Expressions::OPERAND || GetType() == node_type;
}

std::unique_ptr<TreeNode> NumberNode::Clone() {
  return std::make_unique<NumberNode>(value_);
}

std::unique_ptr<TreeNode> NumberNode::Substitute(
    const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) {
  return nullptr;
}

std::unique_ptr<TreeNode> NumberNode::Evaluate() {
  return Clone();
}

Number NumberNode::GetValue() const {
  return value_;
}

}  // namespace symcpp::math
