#include "sin.h"

namespace math {

std::string Sin::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;
  return "sin(" + argument_->GetInfix(0) + ")";
}

std::string Sin::GetRPN() {
  return argument_->GetRPN() + " sin";
}

std::shared_ptr<Expression> Sin::GetDerivative() {
  return std::make_shared<Multiplication>(std::make_shared<Cos>(argument_), argument_->GetDerivative());
}

}  // namespace math
