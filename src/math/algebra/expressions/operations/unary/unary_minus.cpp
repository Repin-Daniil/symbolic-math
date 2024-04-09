#include "unary_minus.h"

namespace math {

std::string UnaryMinus::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;
  return "-" + argument_->GetInfix(2);
}

std::string UnaryMinus::GetRPN() {
  return argument_->GetRPN() + " ~";
}

std::shared_ptr<Expression> UnaryMinus::GetDerivative() {
  return std::make_shared<UnaryMinus>(argument_->GetDerivative());
}

}  // namespace math
