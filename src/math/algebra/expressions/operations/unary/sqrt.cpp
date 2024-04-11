#include "sqrt.h"

namespace math {

std::string SquareRoot::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  return "sqrt(" + argument_->GetInfix(0, variable_to_value) + ")";
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
Expressions SquareRoot::GetType() {
  return Expressions::SQRT;
}
std::optional<std::shared_ptr<Expression>> SquareRoot::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = *simplified;
  }

  if (argument_->GetType() == Expressions::NUMBER) {
    if (argument_->GetNumericResult({}) == 0) {
      return std::make_shared<Number>(0);
    }

    if (argument_->GetNumericResult({}) == 1) {
      return std::make_shared<Number>(1);
    }
  }

  return std::nullopt;
}

}  // namespace math
