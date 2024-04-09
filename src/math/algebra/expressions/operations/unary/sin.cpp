#include "sin.h"

namespace math {

std::string Sin::GetInfix(int previous_priority) {
  return "sin(" + argument_->GetInfix(0) + ")";
}

std::string Sin::GetRPN() {
  return argument_->GetRPN() + " sin";
}

std::shared_ptr<Expression> Sin::GetDerivative() {
  return std::make_shared<Multiplication>(std::make_shared<Cos>(argument_), argument_->GetDerivative());
}

double Sin::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::sin(argument_->GetNumericResult(variable_to_value));
}

}  // namespace math
