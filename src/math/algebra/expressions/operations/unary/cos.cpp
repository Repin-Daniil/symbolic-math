#include "cos.h"

namespace math {

std::string Cos::GetInfix(bool brackets_required) {
  return "cos(" + argument_->GetInfix(false) + ")";
}

std::string Cos::GetRPN() {
  return argument_->GetRPN() + " cos";
}

std::shared_ptr<Expression> Cos::GetDerivative() {
  return std::make_shared<UnaryMinus>(
      std::make_shared<Multiplication>(std::make_shared<Sin>(argument_), argument_->GetDerivative()));
}

}  // namespace math
