#include "number.h"
#include <cmath>

namespace math {

std::string Number::GetInfix() {
  return GetString();
}

std::string Number::GetRPN() {
  return GetString();
}

std::shared_ptr<Expression> Number::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(0));
}

std::string Number::GetString() const noexcept {
  auto str = std::to_string(value_);

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

}  // namespace math
