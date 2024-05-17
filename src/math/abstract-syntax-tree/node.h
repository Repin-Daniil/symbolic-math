#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "math/constants_storage.h"
#include "math/number.h"
#include "math/symbol.h"

namespace math {

class TreeNode {
 public:
  virtual bool IsContainVariable(const Symbol& variable) = 0;
  virtual constants::Expressions GetType() = 0;

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

}  // namespace math
