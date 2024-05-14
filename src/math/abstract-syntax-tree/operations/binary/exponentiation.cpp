#include "exponentiation.h"

namespace math {

std::string Exponentiation::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  bool brackets_required = previous_priority >= priority_;

  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "")
         << left_argument_->GetInfix(priority_, variable_to_value) << " " << constants::Labels::kExponentiation << " "
         << right_argument_->GetInfix(priority_, variable_to_value)
         << (brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string Exponentiation::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << left_argument_->GetRPN(variable_to_value) << " " << right_argument_->GetRPN(variable_to_value) << " "
         << constants::Labels::kExponentiation;
  return stream.str();
}

std::unique_ptr<TreeNode> Exponentiation::GetDerivative() {
  if (left_argument_->IsContainVariable() && !right_argument_->IsContainVariable()) {
    auto first = std::make_unique<Multiplication>(right_argument_->Clone(), left_argument_->GetDerivative());
    auto second = std::make_unique<Exponentiation>(
        left_argument_->Clone(), std::make_unique<Subtraction>(right_argument_->Clone(), std::make_unique<Number>(1)));

    return std::make_unique<Multiplication>(std::move(first), std::move(second));
  } else if (!left_argument_->IsContainVariable() && right_argument_->IsContainVariable()) {
    auto first = std::make_unique<Multiplication>(right_argument_->GetDerivative(),
                                                  std::make_unique<Logarithm>(left_argument_->Clone()));
    auto second = std::make_unique<Exponentiation>(left_argument_->Clone(), right_argument_->Clone());

    return std::make_unique<Multiplication>(std::move(first), std::move(second));
  } else {
    auto first = std::make_unique<Exponentiation>(left_argument_->Clone(), right_argument_->Clone());
    auto second = std::make_unique<Addition>(
        std::make_unique<Multiplication>(right_argument_->GetDerivative(),
                                         std::make_unique<Logarithm>(left_argument_->Clone())),
        std::make_unique<Division>(
            std::make_unique<Multiplication>(right_argument_->Clone(), left_argument_->GetDerivative()),
            left_argument_->Clone()));

    return std::make_unique<Multiplication>(std::move(first), std::move(second));
  }
}

double Exponentiation::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::pow(left_argument_->GetNumericResult(variable_to_value),
                  right_argument_->GetNumericResult(variable_to_value));
}

constants::Expressions Exponentiation::GetType() {
  return constants::Expressions::EXPONENTIATION;
}

std::optional<std::unique_ptr<TreeNode>> Exponentiation::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = std::move(*simplified);
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = std::move(*simplified);
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<Number>(GetNumericResult({}));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 0)) {
    return std::make_unique<Number>(0);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 0)) {
    return std::make_unique<Number>(1);
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 1)) {
    return std::make_unique<Number>(1);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 1)) {
    return std::move(left_argument_);
  }

  return std::nullopt;
}

bool Exponentiation::IsContainVariable() {
  return left_argument_->IsContainVariable() || right_argument_->IsContainVariable();
}

std::unique_ptr<TreeNode> Exponentiation::Clone() {
  return std::make_unique<Exponentiation>(left_argument_->Clone(), right_argument_->Clone());
}

}  // namespace math