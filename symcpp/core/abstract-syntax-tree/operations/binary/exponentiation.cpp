#include "exponentiation.h"

#include <memory>
#include <string>
#include <utility>

#include "core/abstract-syntax-tree/operations/unary/logarithm.h"
#include "symcpp.h"

namespace symcpp::math {

std::string Exponentiation::GetInfix(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;

  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "") << left_argument_->GetInfix(priority_)
         << constants::Labels::kExponentiation << right_argument_->GetInfix(priority_)
         << (brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string Exponentiation::GetLatex(int previous_priority) {
  bool brackets_required = previous_priority >= priority_;

  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kLatexOpenParen : "") << constants::Labels::kLatexOpenCurlyBrace
         << left_argument_->GetLatex(priority_) << constants::Labels::kLatexEndCurlyBrace << " "
         << constants::Labels::kExponentiation << " " << constants::Labels::kLatexOpenCurlyBrace
         << right_argument_->GetLatex(priority_) << constants::Labels::kLatexEndCurlyBrace
         << (brackets_required ? constants::Labels::kLatexEndParen : "");

  return stream.str();
}

std::string Exponentiation::GetRPN() {
  std::stringstream stream;
  stream << left_argument_->GetRPN() << " " << right_argument_->GetRPN() << " " << constants::Labels::kExponentiation;
  return stream.str();
}

std::unique_ptr<TreeNode> Exponentiation::GetDerivative(const Symbol& d) {
  if (left_argument_->IsContainVariable(d) && !right_argument_->IsContainVariable(d)) {
    auto first = std::make_unique<Multiplication>(right_argument_->Clone(), left_argument_->GetDerivative(d));
    auto second = std::make_unique<Exponentiation>(
        left_argument_->Clone(),
        std::make_unique<Subtraction>(right_argument_->Clone(), std::make_unique<NumberNode>(1)));

    return std::make_unique<Multiplication>(std::move(first), std::move(second));
  } else if (!left_argument_->IsContainVariable(d) && right_argument_->IsContainVariable(d)) {
    auto first = std::make_unique<Multiplication>(right_argument_->GetDerivative(d),
                                                  std::make_unique<LogarithmNode>(left_argument_->Clone()));
    auto second = std::make_unique<Exponentiation>(left_argument_->Clone(), right_argument_->Clone());

    return std::make_unique<Multiplication>(std::move(first), std::move(second));
  } else {
    auto first = std::make_unique<Exponentiation>(left_argument_->Clone(), right_argument_->Clone());
    auto second = std::make_unique<Addition>(
        std::make_unique<Multiplication>(right_argument_->GetDerivative(d),
                                         std::make_unique<LogarithmNode>(left_argument_->Clone())),
        std::make_unique<Division>(
            std::make_unique<Multiplication>(right_argument_->Clone(), left_argument_->GetDerivative(d)),
            left_argument_->Clone()));

    return std::make_unique<Multiplication>(std::move(first), std::move(second));
  }
}

constants::Expressions Exponentiation::GetType() {
  return constants::Expressions::EXPONENTIATION;
}

std::unique_ptr<TreeNode> Exponentiation::Simplify() {
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
      utils::Helper::IsEqual(*GetNumber(right_argument_), 0)) {
    return std::make_unique<NumberNode>(1);
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(left_argument_), 1)) {
    return std::make_unique<NumberNode>(1);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(*GetNumber(right_argument_), 1)) {
    return std::move(left_argument_);
  }

  if (right_argument_->GetType() == constants::Expressions::LOGARITHM &&
      ((left_argument_->GetType() == constants::Expressions::NUMBER &&
        utils::Helper::IsEqual(Number(left_argument_->Evaluate()), std::numbers::e)) ||
       (left_argument_->GetType() == constants::Expressions::CONSTANT && left_argument_->IsContainVariable('e')))) {
    return dynamic_cast<UnaryOperation*>(right_argument_.get())->ReleaseArgument();
  }

  return nullptr;
}

std::unique_ptr<TreeNode> Exponentiation::Clone() {
  return std::make_unique<Exponentiation>(left_argument_->Clone(), right_argument_->Clone());
}

std::unique_ptr<TreeNode> Exponentiation::Evaluate() {
  auto left_result = left_argument_->Evaluate();
  auto right_result = right_argument_->Evaluate();

  if (auto left = GetNumber(left_result)) {
    if (auto right = GetNumber(right_result)) {
      return std::make_unique<NumberNode>(std::pow(left->GetValue(), right->GetValue()));
    }
  }

  return std::make_unique<Exponentiation>(std::move(left_result), std::move(right_result));
}

}  // namespace symcpp::math
