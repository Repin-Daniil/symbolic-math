#include "binary-operation.h"

namespace math {

std::shared_ptr<Expression> BinaryOperation::GetLeftArgument() {
  return left_argument_;
}

std::shared_ptr<Expression> BinaryOperation::GetRightArgument() {
  return right_argument_;
}

}  // namespace math
