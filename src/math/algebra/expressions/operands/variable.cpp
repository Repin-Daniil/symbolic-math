#include "variable.h"

namespace math {

std::shared_ptr<Expression> Variable::GetDerivative() {
  return std::shared_ptr<Expression>(new Number(1));
}

std::string Variable::GetInfix() {
  return std::to_string(symbol_);
}

std::string Variable::GetRPN() {
  return std::to_string(symbol_);
}

}  // namespace math
