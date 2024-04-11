#include "variable.h"

namespace math {

std::shared_ptr<Expression> Variable::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(1));
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
  std::stringstream stream;
  stream << symbol_;
  return stream.str();
}
double Variable::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  if (!variable_to_value.contains(symbol_)) {
    throw std::runtime_error(std::string(constants::ExceptionMessage::kWrongFormat.data()) + symbol_);
  }

  return variable_to_value.at(symbol_);
}

Expressions Variable::GetType() {
  return Expressions::VARIABLE;
}

std::optional<std::shared_ptr<Expression>> Variable::Simplify() {
  return std::nullopt;
}

bool Variable::IsContainVariable() {
  return true;
}

}  // namespace math
