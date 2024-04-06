#include "variable.h"

namespace math {

std::shared_ptr<Expression> Variable::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(1));
}

std::string Variable::GetString() {
  return symbol_;
}

}  // namespace math
