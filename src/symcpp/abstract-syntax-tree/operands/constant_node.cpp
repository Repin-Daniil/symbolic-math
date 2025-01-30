#include "constant_node.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "number_node.h"

namespace symcpp::math {

std::unique_ptr<TreeNode> Constant::GetDerivative(const Symbol& d) {
  return std::make_unique<NumberNode>(0);
}

std::string Constant::GetLatex(int previous_priority) {
  return symbol_.GetString();
}

std::string Constant::GetInfix(int previous_priority) {
  return symbol_.GetString();
}

std::string Constant::GetRPN() {
  return symbol_.GetString();
}

constants::Expressions Constant::GetType() {
  return constants::Expressions::CONSTANT;
}

std::unique_ptr<TreeNode> Constant::Simplify() {
  return nullptr;
}

bool Constant::IsContainVariable(const Symbol& variable) {
  return symbol_ == variable;
}

std::unique_ptr<TreeNode> Constant::Clone() {
  return std::make_unique<Constant>(symbol_);
}

std::unique_ptr<TreeNode> Constant::Substitute(
    const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) {
  if (variable_to_value.contains(symbol_)) {
    return variable_to_value.at(symbol_)->Clone();
  }

  return nullptr;
}

std::unique_ptr<TreeNode> Constant::Evaluate() {
  if (symbol_.GetValue() && symbol_.GetValue()->first) {
    return std::make_unique<NumberNode>(symbol_.GetValue()->second);
  }

  return Clone();
}

}  // namespace symcpp::math
