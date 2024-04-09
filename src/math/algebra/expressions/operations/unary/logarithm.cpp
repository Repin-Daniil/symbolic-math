#include "logarithm.h"

namespace math {

std::string Logarithm::GetInfix(bool brackets_required) {
  return "ln(" + argument_->GetInfix(false) + ")";
}

std::string Logarithm::GetRPN() {
  return argument_->GetRPN() + " ln";
}

std::shared_ptr<Expression> Logarithm::GetDerivative() {
  return std::make_shared<Division>(argument_->GetDerivative(), argument_);
}

}  // namespace math
