#include "addition.h"
#include <sstream>

namespace math {

std::shared_ptr<Expression> Addition::GetDerivative() {
  return std::make_shared<Addition>(left_argument_->GetDerivative(), right_argument_->GetDerivative());
}

std::string Addition::GetInfix(bool brackets_required) {
  return (brackets_required ? "(" : "") + left_argument_->GetInfix(false) + " + " + right_argument_->GetInfix(false) +
         (brackets_required ? ")" : "");
}

std::string Addition::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " +";
}

}  // namespace math
