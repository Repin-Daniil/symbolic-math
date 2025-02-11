#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "constants_storage.h"
#include <symcpp/number.h>
#include <symcpp/symbol.h>

namespace symcpp::math {

class TreeNode {
 public:
  virtual bool IsContainVariable(const Symbol& variable) = 0;

  virtual constants::Expressions GetType() = 0;
  virtual bool IsA(constants::Expressions node_type) = 0;

  virtual std::string GetLatex(int previous_priority) = 0;
  virtual std::string GetInfix(int previous_priority) = 0;
  virtual std::string GetRPN() = 0;

  virtual std::unique_ptr<TreeNode> Evaluate() = 0;
  virtual std::unique_ptr<TreeNode> GetDerivative(const Symbol& d) = 0;
  virtual std::unique_ptr<TreeNode> Substitute(
      const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) = 0;

  virtual std::unique_ptr<TreeNode> Simplify() = 0;
  virtual std::unique_ptr<TreeNode> Clone() = 0;

  virtual ~TreeNode() = default;
};

}  // namespace symcpp::math
