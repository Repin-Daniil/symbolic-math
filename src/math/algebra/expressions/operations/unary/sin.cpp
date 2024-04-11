#include "sin.h"

namespace math {

std::string Sin::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  return "sin(" + argument_->GetInfix(0, variable_to_value) + ")";
}

std::string Sin::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return argument_->GetRPN(variable_to_value) + " sin";
}

std::shared_ptr<Expression> Sin::GetDerivative() {
  return std::make_shared<Multiplication>(std::make_shared<Cos>(argument_), argument_->GetDerivative());
}

double Sin::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::sin(argument_->GetNumericResult(variable_to_value));
}
Expressions Sin::GetType() {
  return Expressions::SIN;
}
std::optional<std::shared_ptr<Expression>> Sin::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = *simplified;
  }

  return std::nullopt;
}

}  // namespace math
