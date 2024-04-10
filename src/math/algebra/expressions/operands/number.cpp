#include "number.h"
#include <cmath>
#include "constants_storage.h"

namespace math {

std::string Number::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;

  stream << (brackets_required && (value_ < 0) ? "(" : "") << (value_ < 0 ? "-" : "") << GetString()
         << (brackets_required && value_ < 0 ? ")" : "");

  return stream.str();
}

std::string Number::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return GetString() + (value_ < 0 ? " ~" : "");
}

std::shared_ptr<Expression> Number::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(0));
}

std::string Number::GetString() const noexcept {
  auto str = std::to_string(std::abs(value_));

  int dot_position = str.find('.');

  if (dot_position == std::string::npos) {
    return str;
  }

  int last_non_zero = str.size() - 1;

  while (str[last_non_zero] == '0') {
    last_non_zero--;
  }

  if (str[last_non_zero] == '.') {
    last_non_zero--;
  }

  return str.substr(0, last_non_zero + 1);
}

double Number::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return value_;
}

}  // namespace math
