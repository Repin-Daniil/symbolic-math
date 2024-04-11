#include "cos.h"

namespace math {

std::string Cos::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  return "cos(" + argument_->GetInfix(0, variable_to_value) + ")";
}

std::string Cos::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return argument_->GetRPN(variable_to_value) + " cos";
}

std::shared_ptr<Expression> Cos::GetDerivative() {
  return std::make_shared<UnaryMinus>(
      std::make_shared<Multiplication>(std::make_shared<Sin>(argument_), argument_->GetDerivative()));
}
double Cos::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::cos(argument_->GetNumericResult(variable_to_value));
}

Expressions Cos::GetType() {
  return Expressions::COS;
}

std::optional<std::shared_ptr<Expression>> Cos::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = *simplified;
  }

  return std::nullopt;
}

}  // namespace math
