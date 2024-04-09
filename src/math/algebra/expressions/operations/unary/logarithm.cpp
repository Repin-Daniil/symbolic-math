#include "logarithm.h"

namespace math {

std::string Logarithm::GetInfix(int previous_priority) {
  return "ln(" + argument_->GetInfix(0) + ")";
}

std::string Logarithm::GetRPN() {
  return argument_->GetRPN() + " ln";
}

std::shared_ptr<Expression> Logarithm::GetDerivative() {
  return std::make_shared<Division>(argument_->GetDerivative(), argument_);
}
double Logarithm::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto arg = argument_->GetNumericResult(variable_to_value);

  if (std::abs(arg - 0) < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error(constants::ExceptionMessage::kZeroLogarithm.data());
  }

  return std::log(arg);
}

}  // namespace math
