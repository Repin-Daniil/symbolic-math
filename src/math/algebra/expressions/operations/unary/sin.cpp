#include "sin.h"

namespace math {

std::string Sin::GetInfix() {
  return "sin(" + argument_->GetInfix() + ")";
}

std::string Sin::GetRPN() {
  return argument_->GetInfix() + " sin";
}

std::shared_ptr<Expression> Sin::GetDerivative() {
  return std::make_shared<Multiplication>(std::make_shared<Cos>(argument_), argument_->GetDerivative());
}

}  // namespace math
