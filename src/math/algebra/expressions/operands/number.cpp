#include "number.h"

namespace math {

using namespace std::literals;

std::string Number::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;

  stream << (brackets_required && (value_ < 0) ? constants::Labels::kOpenParen : "")
         << (value_ < 0 ? constants::Labels::kMinus : "") << GetString()
         << (brackets_required && (value_ < 0) ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string Number::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  return GetString() + (value_ < 0 ? " "s.append(constants::Labels::kUnaryMinus) : "");
}

std::shared_ptr<Expression> Number::GetDerivative() {
  return std::make_shared<Number>(0);
}

std::string Number::GetString() const noexcept {
  auto str = std::to_string(std::abs(value_));

  int dot_position = str.find(constants::Labels::kDecimalPoint);

  if (dot_position == std::string::npos) {
    return str;
  }

  int last_non_zero = str.size() - 1;

  while (str[last_non_zero] == constants::Labels::kZero) {
    last_non_zero--;
  }

  if (str[last_non_zero] == constants::Labels::kDecimalPoint) {
    last_non_zero--;
  }

  return str.substr(0, last_non_zero + 1);
}

double Number::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return value_;
}

constants::Expressions Number::GetType() {
  return constants::Expressions::NUMBER;
}

std::optional<std::shared_ptr<Expression>> Number::Simplify() {
  return std::nullopt;
}

bool Number::IsContainVariable() {
  return false;
}

}  // namespace math
