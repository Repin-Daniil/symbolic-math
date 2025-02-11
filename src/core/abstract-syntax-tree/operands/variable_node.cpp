#include "variable_node.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "core/abstract-syntax-tree/operations/binary_operation.h"

namespace symcpp::math {

std::unique_ptr<TreeNode> Variable::GetDerivative(const Symbol& d) {
  if (symbol_ == d) {
    return std::make_unique<NumberNode>(1);
  }

  return std::make_unique<NumberNode>(0);
}

std::string Variable::GetLatex(int previous_priority) {
  return symbol_.GetString();
}

std::string Variable::GetInfix(int previous_priority) {
  return symbol_.GetString();
}

std::string Variable::GetRPN() {
  return symbol_.GetString();
}

constants::Expressions Variable::GetType() {
  return constants::Expressions::VARIABLE;
}

bool Variable::IsA(constants::Expressions node_type) {
  return node_type == constants::Expressions::OPERAND || GetType() == node_type;
}

std::unique_ptr<TreeNode> Variable::Simplify() {
  return nullptr;
}

bool Variable::IsContainVariable(const Symbol& variable) {
  return symbol_ == variable;
}

std::unique_ptr<TreeNode> Variable::Clone() {
  return std::make_unique<Variable>(symbol_);
}

std::unique_ptr<TreeNode> Variable::Substitute(
    const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) {
  if (variable_to_value.contains(symbol_)) {
    return variable_to_value.at(symbol_)->Clone();
  }

  return nullptr;
}

std::unique_ptr<TreeNode> Variable::Evaluate() {
  if (symbol_.GetValue() && symbol_.GetValue()->first) {
    return std::make_unique<NumberNode>(symbol_.GetValue()->second);
  }

  return Clone();
}

}  // namespace symcpp::math
