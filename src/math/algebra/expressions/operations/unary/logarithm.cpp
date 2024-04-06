#include "logarithm.h"
#include "math/algebra/expressions/operations/binary/division.h"

namespace math {

std::string Logarithm::GetString() {
  return " ln(" + argument_->GetString() + ") ";
}

std::shared_ptr<Expression> Logarithm::GetDerivative() {
  return std::make_shared<Division>(argument_->GetDerivative(), argument_);
}

}  // namespace math
