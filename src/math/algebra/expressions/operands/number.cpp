#include "number.h"

namespace math {

std::string Number::GetString() {
  return std::to_string(value_);
}

std::shared_ptr<Expression> Number::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(0));
}

}  // namespace math
