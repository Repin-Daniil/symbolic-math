#include "unary_minus.h"

namespace math {

std::string UnaryMinus::GetInfix(int previous_priority) {
  return "-" + argument_->GetInfix(constants::operations_to_priority.at(constants::Operations::SUBSTRACTION));
}

std::string UnaryMinus::GetRPN() {
  return argument_->GetRPN() + " ~";
}

std::shared_ptr<Expression> UnaryMinus::GetDerivative() {
  return std::make_shared<UnaryMinus>(argument_->GetDerivative());
}

}  // namespace math
