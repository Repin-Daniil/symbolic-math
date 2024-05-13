#include "unary_minus.h"

namespace math {

std::string UnaryMinus::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "") << constants::Labels::kMinus
         << argument_->GetInfix(constants::operations_to_priority.at(constants::Operations::SUBTRACTION),
                                variable_to_value)
         << std::string(brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string UnaryMinus::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return argument_->GetRPN(variable_to_value) + " ~";
}

std::unique_ptr<Expression> UnaryMinus::GetDerivative() {
  return std::make_unique<UnaryMinus>(argument_->GetDerivative());
}

double UnaryMinus::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return -argument_->GetNumericResult(variable_to_value);
}

constants::Expressions UnaryMinus::GetType() {
  return constants::Expressions::UNARY_MINUS;
}

std::optional<std::unique_ptr<Expression>> UnaryMinus::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  if (argument_->GetType() == constants::Expressions::UNARY_MINUS) {
    return dynamic_cast<UnaryOperation*>(argument_.get())->ReleaseArgument();
  }

  if (argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<Number>(-argument_->GetNumericResult({}));
  }

  return std::nullopt;
}

bool UnaryMinus::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::unique_ptr<Expression> UnaryMinus::Clone() {
  return std::make_unique<UnaryMinus>(argument_->Clone());
}

}  // namespace math
