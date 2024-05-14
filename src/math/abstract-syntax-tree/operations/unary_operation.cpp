#include "unary_operation.h"

namespace math {

std::unique_ptr<TreeNode> UnaryOperation::ReleaseArgument() {
  return std::move(argument_);
}

}  // namespace math
