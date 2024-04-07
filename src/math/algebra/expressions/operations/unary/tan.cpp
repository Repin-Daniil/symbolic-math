#include "tan.h"

namespace math {

std::string Tan::GetInfix() {
  return "tan(" + argument_->GetInfix() + ")";
}

std::string Sin::GetRPN() {
  return argument_->GetInfix() + " tan";
}

std::shared_ptr<Expression> Sin::GetDerivative() {
  return std::make_shared<Division>(
      argument_->GetDerivative(),
      std::make_shared<Exponentiation>(std::make_shared<Cos>(argument_), std::make_shared<Number>(2)));
}

}  // namespace math
