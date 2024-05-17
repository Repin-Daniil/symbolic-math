#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>

#include "math/abstract-syntax-tree/node.h"

namespace math {

class UnaryOperation : public TreeNode {
 public:
  explicit UnaryOperation(std::unique_ptr<TreeNode> argument) : argument_(std::move(argument)) {
  }

  bool IsContainVariable(const Symbol& variable) override;
  virtual std::unique_ptr<TreeNode> ReleaseArgument();
  std::unique_ptr<TreeNode> Substitute(
      const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) override;
  virtual ~UnaryOperation() = default;

 protected:
  virtual std::optional<Number> GetNumber(const std::unique_ptr<TreeNode>& result) const;

 protected:
  std::unique_ptr<TreeNode> argument_;
};

}  // namespace math
