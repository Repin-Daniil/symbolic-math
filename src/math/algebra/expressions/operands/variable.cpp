#include "variable.h"

namespace math {

std::unique_ptr<Expression> Variable::GetDerivative() {
  return std::make_unique<Number>(1);
}

std::string Variable::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  if (variable_to_value.contains(symbol_)) {
    return math::Number(variable_to_value.at(symbol_)).GetInfix(previous_priority, {});
  }

  return GetString();
}

std::string Variable::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  if (variable_to_value.contains(symbol_)) {
    return math::Number(variable_to_value.at(symbol_)).GetRPN({});
  }

  return GetString();
}

std::string Variable::GetString() const noexcept {
  return {symbol_};
}

double Variable::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  if (!variable_to_value.contains(symbol_)) {
    throw std::runtime_error(std::string(constants::ExceptionMessage::kWrongFormat.data()) + symbol_);
  }

  return variable_to_value.at(symbol_);
}

constants::Expressions Variable::GetType() {
  return constants::Expressions::VARIABLE;
}

std::optional<std::unique_ptr<Expression>> Variable::Simplify() {
  return std::nullopt;
}

bool Variable::IsContainVariable() {
  return true;
}

std::unique_ptr<Expression> Variable::Clone() {
  return std::make_unique<Variable>(symbol_);
}

}  // namespace math
