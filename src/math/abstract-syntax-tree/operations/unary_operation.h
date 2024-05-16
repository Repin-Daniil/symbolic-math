#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "math/abstract-syntax-tree/node.h"

namespace math {

class UnaryOperation : public TreeNode {
 public:
  explicit UnaryOperation(std::unique_ptr<TreeNode> argument) : argument_(std::move(argument)) {
  }

  virtual std::unique_ptr<TreeNode> ReleaseArgument();

  virtual ~UnaryOperation() = default;

 protected:
  std::unique_ptr<TreeNode> argument_;
};

}  // namespace math
