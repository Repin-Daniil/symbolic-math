#include "sin.h"

namespace math {

std::string Sin::GetInfix(bool brackets_required) {
  return "sin(" + argument_->GetInfix(false) + ")";
}

std::string Sin::GetRPN() {
  return argument_->GetRPN() + " sin";
}

std::shared_ptr<Expression> Sin::GetDerivative() {
  return std::make_shared<Multiplication>(std::make_shared<Cos>(argument_), argument_->GetDerivative());
}

}  // namespace math
