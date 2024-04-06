#include "unary-operation.h"

namespace math {

std::shared_ptr<Expression> UnaryOperation::GetArgument() {
  return argument_;
}

}  // namespace math
