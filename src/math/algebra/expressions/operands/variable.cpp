#include "variable.h"

namespace math {

std::shared_ptr<Expression> Variable::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(1));
}

std::string Variable::GetInfix() {
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

}  // namespace math
