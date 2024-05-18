#include "multiplication.h"

namespace symcpp::math {

std::string Multiplication::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority > priority_;

  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "") << left_argument_->GetInfix(priority_) << " "
         << constants::Labels::kMultiplication << " " << right_argument_->GetInfix(priority_)
         << (brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string Multiplication::GetRPN() {
  std::stringstream stream;
  stream << left_argument_->GetRPN() + " " + right_argument_->GetRPN() << " " << constants::Labels::kMultiplication;
  return stream.str();
}

std::unique_ptr<TreeNode> Multiplication::GetDerivative(const Symbol& d) {
  return std::make_unique<Addition>(
      std::make_unique<Multiplication>(left_argument_->Clone(), right_argument_->GetDerivative(d)),
      std::make_unique<Multiplication>(left_argument_->GetDerivative(d), right_argument_->Clone()));
}

constants::Expressions Multiplication::GetType() {
  return constants::Expressions::MULTIPLICATION;
}

std::unique_ptr<TreeNode> Multiplication::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(simplified);
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(simplified);
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<NumberNode>(*GetNumber(left_argument_) * *GetNumber(right_argument_));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(left_argument_), 0)) {
    return std::make_unique<NumberNode>(0);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(right_argument_), 0)) {
    return std::make_unique<NumberNode>(0);
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(left_argument_), 1)) {
    return std::move(right_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(right_argument_), 1)) {
    return std::move(left_argument_);
  }

  return nullptr;
}

std::unique_ptr<TreeNode> Multiplication::Clone() {
  return std::make_unique<Multiplication>(left_argument_->Clone(), right_argument_->Clone());
}

std::unique_ptr<TreeNode> Multiplication::Evaluate() {
  auto left_result = left_argument_->Evaluate();
  auto right_result = right_argument_->Evaluate();

  if (auto left = GetNumber(left_result)) {
    if (auto right = GetNumber(right_result)) {
      return std::make_unique<NumberNode>(*left * *right);
    }
  }

  return std::make_unique<Multiplication>(std::move(left_result), std::move(right_result));
}

}  // namespace symcpp::math
