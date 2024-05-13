#include "binary_operation.h"

namespace math {

std::unique_ptr<Expression> BinaryOperation::ReleaseLeftArgument() {
  return std::move(left_argument_);
}

std::unique_ptr<Expression> BinaryOperation::ReleaseRightArgument() {
  return std::move(right_argument_);
}

}  // namespace math
