#include "subtraction.h"

namespace symcpp::math {

std::unique_ptr<TreeNode> Subtraction::GetDerivative(const Symbol& d) {
  return std::make_unique<Subtraction>(left_argument_->GetDerivative(d), right_argument_->GetDerivative(d));
}

std::string Subtraction::GetLatex(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kLatexOpenParen : "") << left_argument_->GetLatex(priority_) << " "
         << constants::Labels::kMinus << " " << right_argument_->GetLatex(priority_)
         << (brackets_required ? constants::Labels::kLatexEndParen : "");

  return stream.str();
}

std::string Subtraction::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "") << left_argument_->GetInfix(priority_) << " "
         << constants::Labels::kMinus << " " << right_argument_->GetInfix(priority_)
         << (brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string Subtraction::GetRPN() {
  std::stringstream stream;
  stream << left_argument_->GetRPN() << " " << right_argument_->GetRPN() << " " << constants::Labels::kMinus;
  return stream.str();
}

constants::Expressions Subtraction::GetType() {
  return constants::Expressions::SUBTRACTION;
}

std::unique_ptr<TreeNode> Subtraction::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(simplified);
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(simplified);
  }

  if (left_argument_->GetRPN() == right_argument_->GetRPN()) {
    return std::make_unique<NumberNode>(0);
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<NumberNode>(*GetNumber(left_argument_) - *GetNumber(right_argument_));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(left_argument_), 0)) {
    return std::make_unique<UnaryMinus>(std::move(right_argument_));
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(right_argument_), 0)) {
    return std::move(left_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::UNARY_MINUS) {
    auto new_right = dynamic_cast<UnaryOperation*>(right_argument_.get())->ReleaseArgument();

    return std::make_unique<Addition>(std::move(left_argument_), std::move(new_right));
  }

  return nullptr;
}

std::unique_ptr<TreeNode> Subtraction::Clone() {
  return std::make_unique<Subtraction>(left_argument_->Clone(), right_argument_->Clone());
}

std::unique_ptr<TreeNode> Subtraction::Evaluate() {
  auto left_result = left_argument_->Evaluate();
  auto right_result = right_argument_->Evaluate();

  if (auto left = GetNumber(left_result)) {
    if (auto right = GetNumber(right_result)) {
      return std::make_unique<NumberNode>(*left - *right);
    }
  }

  return std::make_unique<Subtraction>(std::move(left_result), std::move(right_result));
}

}  // namespace symcpp::math
