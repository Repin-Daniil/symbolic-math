#include "variable.h"
#include "constants_storage.h"

namespace math {

std::shared_ptr<Expression> Variable::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(1));
}

std::string Variable::GetInfix(int previous_priority) {
  return GetString();
}

std::string Variable::GetRPN() {
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

}  // namespace math
