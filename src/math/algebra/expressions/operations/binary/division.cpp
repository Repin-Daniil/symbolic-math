#include "division.h"

namespace math {

std::string Division::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required = previous_priority >= priority_;

  return (brackets_required ? "(" : "") + left_argument_->GetInfix(priority_, variable_to_value) + " / " +
         right_argument_->GetInfix(priority_, variable_to_value) + (brackets_required ? ")" : "");
}

std::string Division::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetRPN(variable_to_value) + " " + right_argument_->GetRPN(variable_to_value) + " /";
}

std::shared_ptr<Expression> Division::GetDerivative() {
  auto numerator =
      std::make_shared<Subtraction>(std::make_shared<Multiplication>(left_argument_->GetDerivative(), right_argument_),
                                    std::make_shared<Multiplication>(left_argument_, right_argument_->GetDerivative()));
  auto denominator = std::make_shared<Exponentiation>(left_argument_, std::make_shared<Number>(2));
  return std::make_shared<Division>(numerator, denominator);
}
double Division::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto divisible = left_argument_->GetNumericResult(variable_to_value);
  auto divider = right_argument_->GetNumericResult(variable_to_value);

  if (std::abs(divider - 0) < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error(constants::ExceptionMessage::kZeroDivision.data());
  }

  return divisible / divider;
}

}  // namespace math
