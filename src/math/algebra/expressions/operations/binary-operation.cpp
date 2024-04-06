#include "binary-operation.h"

namespace math {

Expression& BinaryOperation::GetLeftArgument() {
  return *left_argument_;
}

Expression& BinaryOperation::GetRightArgument() {
  return *right_argument_;
}

}  // namespace math
