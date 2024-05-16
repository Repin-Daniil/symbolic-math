#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>

#include "math/abstract-syntax-tree/node.h"
#include "math/constants_storage.h"
#include "math/symbol.h"
#include "number_node.h"

namespace math {

class Variable final : public TreeNode {
 public:
  explicit Variable(Symbol symbol) : symbol_(std::move(symbol)) {
  }

  std::string GetInfix(int previous_priority,
                       const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  constants::Expressions GetType() override;
  Number GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  Symbol symbol_;  // FIXME const Symbol - это константа, Symbol - переменная. Может через VariableBase
};

}  // namespace math
