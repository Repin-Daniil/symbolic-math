#include "logarithm.h"

namespace math {

std::string Logarithm::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  return "ln(" + argument_->GetInfix(0, variable_to_value) + ")";
}

std::string Logarithm::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return argument_->GetRPN(variable_to_value) + " ln";
}

std::shared_ptr<Expression> Logarithm::GetDerivative() {
  return std::make_shared<Division>(argument_->GetDerivative(), argument_);
}
double Logarithm::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto arg = argument_->GetNumericResult(variable_to_value);

  if (arg < 0 || std::abs(arg - 0) < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongLogarithm.data());
  }

  return std::log(arg);
}
Expressions Logarithm::GetType() {
  return Expressions::LOGARITHM;
}
std::optional<std::shared_ptr<Expression>> Logarithm::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = *simplified;
  }

  return std::nullopt;
}
bool Logarithm::IsContainVariable() {
  return argument_->IsContainVariable();
}

}  // namespace math
