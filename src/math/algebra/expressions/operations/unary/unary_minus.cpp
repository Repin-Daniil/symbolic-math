#include "unary_minus.h"

namespace math {

std::string UnaryMinus::GetInfix(bool brackets_required) {
  return "-" + argument_->GetInfix(true);
}

std::string UnaryMinus::GetRPN() {
  return argument_->GetRPN() + " ~";
}

std::shared_ptr<Expression> UnaryMinus::GetDerivative() {
  return std::make_shared<UnaryMinus>(argument_->GetDerivative());
}

}  // namespace math
