#include "unary_minus.h"

namespace math {

std::string UnaryMinus::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);

  return std::string(brackets_required ? "(" : "") + "-" +
         argument_->GetInfix(constants::operations_to_priority.at(constants::Operations::SUBTRACTION),
                             variable_to_value) +
         std::string(brackets_required ? ")" : "");
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
Expressions UnaryMinus::GetType() {
  return Expressions::UNARY_MINUS;
}
std::optional<std::shared_ptr<Expression>> UnaryMinus::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = *simplified;
  }

  if (argument_->GetType() == Expressions::UNARY_MINUS) {
    return std::dynamic_pointer_cast<UnaryOperation>(argument_)->GetArgument();
  }

  if (argument_->GetType() == Expressions::NUMBER && argument_->GetNumericResult({}) < 0) {
    return std::make_shared<Number>(std::abs(argument_->GetNumericResult({})));
  }

  return std::nullopt;
}

bool UnaryMinus::IsContainVariable() {
  return argument_->IsContainVariable();
}

}  // namespace math
