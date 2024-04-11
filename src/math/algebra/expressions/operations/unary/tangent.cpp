#include "tangent.h"

namespace math {

std::string Tangent::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  return "tan(" + argument_->GetInfix(0, variable_to_value) + ")";
}

std::string Tangent::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return argument_->GetRPN(variable_to_value) + " tan";
}

std::shared_ptr<Expression> Tangent::GetDerivative() {
  return std::make_shared<Division>(
      argument_->GetDerivative(),
      std::make_shared<Exponentiation>(std::make_shared<Cos>(argument_), std::make_shared<Number>(2)));
}

double Tangent::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto arg = argument_->GetNumericResult(variable_to_value);

  if (std::abs(std::numbers::pi / 2.0 - std::fmod(arg, std::numbers::pi)) < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongTangent.data());
  }

  return std::tan(arg);
}

Expressions Tangent::GetType() {
  return Expressions::TANGENT;
}
std::optional<std::shared_ptr<Expression>> Tangent::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = *simplified;
  }

  return std::nullopt;
}

}  // namespace math
