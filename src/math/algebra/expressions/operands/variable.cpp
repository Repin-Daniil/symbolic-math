#include "variable.h"

namespace math {

std::unique_ptr<Expression> Variable::GetDerivative() {
  return std::unique_ptr<Expression>(new Number(1));
}

std::string Variable::GetString() {
  return symbol_;
}

}  // namespace math
