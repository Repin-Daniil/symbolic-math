#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>

#include "core/abstract-syntax-tree/node.h"
#include "core/abstract-syntax-tree/operands/number_node.h"

namespace symcpp::math {

class BinaryOperation : public TreeNode {
 public:
  BinaryOperation(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : left_argument_(std::move(left)), right_argument_(std::move(right)) {
  }

  bool IsContainVariable(const Symbol& variable) override;
  virtual std::unique_ptr<TreeNode> ReleaseLeftArgument();
  virtual std::unique_ptr<TreeNode> ReleaseRightArgument();
  std::unique_ptr<TreeNode> Substitute(
      const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) override;
  virtual ~BinaryOperation() = default;

 protected:
  virtual std::optional<Number> GetNumber(const std::unique_ptr<TreeNode>& result) const;

 protected:
  std::unique_ptr<TreeNode> left_argument_;
  std::unique_ptr<TreeNode> right_argument_;
};

}  // namespace symcpp::math
