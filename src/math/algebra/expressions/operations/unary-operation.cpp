#include "unary-operation.h"

namespace math {

Expression& UnaryOperation::GetArgument() {
  return *argument_;
}

}  // namespace math
