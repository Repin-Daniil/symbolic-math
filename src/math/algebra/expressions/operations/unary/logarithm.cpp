#include "logarithm.h"

namespace math {

std::string Logarithm::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;
  return "ln(" + argument_->GetInfix(0) + ")";
}

std::string Logarithm::GetRPN() {
  return argument_->GetRPN() + " ln";
}

std::shared_ptr<Expression> Logarithm::GetDerivative() {
  return std::make_shared<Division>(argument_->GetDerivative(), argument_);
}

}  // namespace math
