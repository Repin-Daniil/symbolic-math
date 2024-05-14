#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "math/abstract-syntax-tree/expression.h"

namespace math {

class BinaryOperation : public TreeNode {
 public:
  BinaryOperation(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : left_argument_(std::move(left)), right_argument_(std::move(right)) {
  }

  virtual std::unique_ptr<TreeNode> ReleaseLeftArgument();
  virtual std::unique_ptr<TreeNode> ReleaseRightArgument();

  virtual ~BinaryOperation() = default;

 protected:
  std::unique_ptr<TreeNode> left_argument_;
  std::unique_ptr<TreeNode> right_argument_;
};

}  // namespace math
