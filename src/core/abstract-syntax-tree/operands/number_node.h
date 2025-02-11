#pragma once

#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "constants_storage.h"
#include "core/abstract-syntax-tree/node.h"
#include "number.h"
#include "symbol.h"

namespace symcpp::math {

class NumberNode final : public TreeNode {
 public:
  explicit NumberNode(const Number& value) : value_(value) {
  }

  [[nodiscard]] Number GetValue() const;
  constants::Expressions GetType() override;

  bool IsContainVariable(const Symbol& variable) override;
  bool IsA(constants::Expressions node_type) override;

  std::string GetLatex(int previous_priority) override;
  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;

  std::unique_ptr<TreeNode> GetDerivative(const Symbol& d) override;
  std::unique_ptr<TreeNode> Evaluate() override;
  std::unique_ptr<TreeNode> Substitute(
      const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) override;

  std::unique_ptr<TreeNode> Simplify() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  Number value_;
};

}  // namespace symcpp::math
