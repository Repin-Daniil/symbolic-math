#include "unary_minus.h"

namespace math {

std::string UnaryMinus::GetInfix(int previous_priority) {
  return "-" + argument_->GetInfix(constants::operations_to_priority.at(constants::Operations::SUBTRACTION));
}

std::string UnaryMinus::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return argument_->GetRPN(variable_to_value) + " ~";
}

std::shared_ptr<Expression> UnaryMinus::GetDerivative() {
  return std::make_shared<UnaryMinus>(argument_->GetDerivative());
}

double UnaryMinus::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return -argument_->GetNumericResult(variable_to_value);
}

}  // namespace math
