#include "addition.h"

namespace symcpp::math {

std::unique_ptr<TreeNode> Addition::GetDerivative(const Symbol& d) {
  return std::make_unique<Addition>(left_argument_->GetDerivative(d), right_argument_->GetDerivative(d));
}

std::string Addition::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority > priority_;

  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "") << left_argument_->GetInfix(priority_) << " "
         << constants::Labels::kPlus << " " << right_argument_->GetInfix(priority_) << (brackets_required ? ")" : "");

  return stream.str();
}

std::string Addition::GetRPN() {
  std::stringstream stream;
  stream << left_argument_->GetRPN() << " " << right_argument_->GetRPN() << " " << constants::Labels::kPlus;
  return stream.str();
}

std::unique_ptr<TreeNode> Addition::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(simplified);
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(simplified);
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<NumberNode>(*GetNumber(left_argument_) + *GetNumber(right_argument_));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(left_argument_), 0)) {
    return std::move(right_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(right_argument_), 0)) {
    return std::move(left_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::UNARY_MINUS) {
    auto new_right = dynamic_cast<UnaryOperation*>(right_argument_.get())->ReleaseArgument();
    return std::make_unique<Subtraction>(std::move(left_argument_), std::move(new_right));
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER) {
    if (dynamic_cast<NumberNode*>(right_argument_.get())->GetValue() < 0) {
      return std::make_unique<Subtraction>(
          std::move(left_argument_), std::make_unique<NumberNode>(std::abs(
                                         dynamic_cast<NumberNode*>(right_argument_.get())->GetValue().GetValue())));
    }
  }

  return nullptr;
}

constants::Expressions Addition::GetType() {
  return constants::Expressions::ADDITION;
}

std::unique_ptr<TreeNode> Addition::Clone() {
  return std::make_unique<Addition>(left_argument_->Clone(), right_argument_->Clone());
}

std::unique_ptr<TreeNode> Addition::Evaluate() {
  auto left_result = left_argument_->Evaluate();
  auto right_result = right_argument_->Evaluate();

  if (auto left = GetNumber(left_result)) {
    if (auto right = GetNumber(right_result)) {
      return std::make_unique<NumberNode>(*left + *right);
    }
  }

  return std::make_unique<Addition>(std::move(left_result), std::move(right_result));
}

}  // namespace symcpp::math
