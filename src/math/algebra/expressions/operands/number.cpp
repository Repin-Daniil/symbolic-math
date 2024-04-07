#include "number.h"

namespace math {

std::string Number::GetInfix() {
  return std::to_string(value_);
}

std::string Number::GetRPN() {
  return std::to_string(value_);
}

std::shared_ptr<Expression> Number::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(0));
}

}  // namespace math
