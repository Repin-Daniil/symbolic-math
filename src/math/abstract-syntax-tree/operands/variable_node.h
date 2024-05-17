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
  explicit Variable(const Symbol& symbol) : symbol_(symbol) {
  }

  bool IsContainVariable(const Symbol& variable) override;
  constants::Expressions GetType() override;

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;

  std::unique_ptr<TreeNode> Evaluate() override;
  std::unique_ptr<TreeNode> GetDerivative(const Symbol& d) override;
  std::unique_ptr<TreeNode> Substitute(
      const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) override;

  std::unique_ptr<TreeNode> Simplify() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  Symbol symbol_;  // FIXME const Symbol - это константа, Symbol - переменная. Может через VariableBase
};

}  // namespace math
