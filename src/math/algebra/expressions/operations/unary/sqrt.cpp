#include "sqrt.h"

namespace math {

std::string SquareRoot::GetInfix(int previous_priority) {
  return "sqrt(" + argument_->GetInfix(0) + ")";
}

std::string SquareRoot::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return argument_->GetRPN(variable_to_value) + " sqrt";
}

std::shared_ptr<Expression> SquareRoot::GetDerivative() {
  return std::make_shared<Division>(
      argument_->GetDerivative(),
      std::make_shared<Multiplication>(std::make_shared<Number>(2), std::make_shared<SquareRoot>(argument_)));
}

double SquareRoot::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto arg = argument_->GetNumericResult(variable_to_value);

  if (arg < 0) {
    throw std::runtime_error(constants::ExceptionMessage::kNegativeRoot.data());
  }

  return std::sqrt(arg);
}

}  // namespace math
