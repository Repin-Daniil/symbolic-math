#include "addition.h"

namespace math {

std::shared_ptr<Expression> Addition::GetDerivative() {
  return std::shared_ptr<Expression>(new Addition(left_argument_->GetDerivative(), right_argument_->GetDerivative()));
}

std::string Addition::GetString() {
  return left_argument_->GetString() + " + " + right_argument_->GetString();
}

}  // namespace math
