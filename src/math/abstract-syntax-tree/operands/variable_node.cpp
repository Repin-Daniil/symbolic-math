#include "variable_node.h"

namespace math {

std::unique_ptr<TreeNode> Variable::GetDerivative() {
  if (symbol_.GetValue()) {
    return std::make_unique<NumberNode>(0);
  }

  return std::make_unique<NumberNode>(1);
}

std::string Variable::GetInfix(int previous_priority,
                               const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  if (variable_to_value.contains(symbol_)) {
    return variable_to_value.at(symbol_).GetString();
  }

  return symbol_.GetString();
}

std::string Variable::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  return symbol_.GetString();
}

Number Variable::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  if (symbol_.GetValue() && symbol_.GetValue()->first) {
    return symbol_.GetValue()->second;
  }
  // FIXME Починить везде GetNumericResult под новую логику
  if (!variable_to_value.contains(symbol_)) {
    throw std::runtime_error(std::string(constants::ExceptionMessage::kWrongFormat.data()) + symbol_.GetSymbol());
  }

  return variable_to_value.at(symbol_);
}

constants::Expressions Variable::GetType() {
  return constants::Expressions::VARIABLE;
}

std::optional<std::unique_ptr<TreeNode>> Variable::Simplify() {
  return std::nullopt;
}

bool Variable::IsContainVariable() {
  //  return true;
  return !symbol_.GetValue()->first;  // FIXME может отвалиться
}

std::unique_ptr<TreeNode> Variable::Clone() {
  return std::make_unique<Variable>(symbol_);
}

}  // namespace math
