#include "division.h"

namespace math {

std::string Division::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "") << left_argument_->GetInfix(priority_) << " "
         << constants::Labels::kDivision << " " << right_argument_->GetInfix(priority_)
         << (brackets_required ? constants::Labels::kEndParen : "");
  return stream.str();
}

std::string Division::GetRPN() {
  std::stringstream stream;
  stream << left_argument_->GetRPN() << " " << right_argument_->GetRPN() << " " << constants::Labels::kDivision;
  return stream.str();
}

std::unique_ptr<TreeNode> Division::GetDerivative(const Symbol& d) {
  auto numerator = std::make_unique<Subtraction>(
      std::make_unique<Multiplication>(left_argument_->GetDerivative(d), right_argument_->Clone()),
      std::make_unique<Multiplication>(left_argument_->Clone(), right_argument_->GetDerivative(d)));
  auto denominator = std::make_unique<Exponentiation>(right_argument_->Clone(), std::make_unique<NumberNode>(2));
  return std::make_unique<Division>(std::move(numerator), std::move(denominator));
}

constants::Expressions Division::GetType() {
  return constants::Expressions::DIVISION;
}

std::unique_ptr<TreeNode> Division::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(simplified);
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(simplified);
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(left_argument_), 0)) {
    return std::make_unique<NumberNode>(0);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(right_argument_), 1)) {
    return ReleaseLeftArgument();
  }

  return nullptr;
}

std::unique_ptr<TreeNode> Division::Clone() {
  return std::make_unique<Division>(left_argument_->Clone(), right_argument_->Clone());
}

std::unique_ptr<TreeNode> Division::Evaluate() {
  auto left_result = left_argument_->Evaluate();
  auto right_result = right_argument_->Evaluate();

  if (auto denominator = GetNumber(right_result)) {
    if (utils::Helper::IsEqual(*denominator, 0)) {
      throw std::runtime_error(constants::ExceptionMessage::kZeroDivision.data());
    }

    if (auto numerator = GetNumber(left_result)) {
      return std::make_unique<NumberNode>(*numerator / *denominator);
    }
  }

  return std::make_unique<Division>(std::move(left_result), std::move(right_result));
}

}  // namespace math
