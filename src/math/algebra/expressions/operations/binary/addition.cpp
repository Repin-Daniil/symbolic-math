#include "addition.h"
#include <sstream>

namespace math {

std::shared_ptr<Expression> Addition::GetDerivative() {
  return std::make_shared<Addition>(left_argument_->GetDerivative(), right_argument_->GetDerivative());
}

std::string Addition::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority > priority_;

  return (brackets_required ? "(" : "") + left_argument_->GetInfix(priority_) + " + " +
         right_argument_->GetInfix(priority_) + (brackets_required ? ")" : "");
}

std::string Addition::GetRPN() {
  return left_argument_->GetRPN() + " " + right_argument_->GetRPN() + " +";
}

double Addition::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return left_argument_->GetNumericResult(variable_to_value) + right_argument_->GetNumericResult(variable_to_value);
}

}  // namespace math
