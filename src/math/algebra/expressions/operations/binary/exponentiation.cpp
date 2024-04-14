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

std::shared_ptr<Expression> Exponentiation::GetDerivative() {
  if (left_argument_->IsContainVariable() && !right_argument_->IsContainVariable()) {
    auto first = std::make_shared<Multiplication>(right_argument_, left_argument_->GetDerivative());
    auto second = std::make_shared<Exponentiation>(
        left_argument_, std::make_shared<Subtraction>(right_argument_, std::make_shared<Number>(1)));

    return std::make_shared<Multiplication>(first, second);
  } else if (!left_argument_->IsContainVariable() && right_argument_->IsContainVariable()) {
    auto first =
        std::make_shared<Multiplication>(right_argument_->GetDerivative(), std::make_shared<Logarithm>(left_argument_));
    auto second = std::make_shared<Exponentiation>(left_argument_, right_argument_);

    return std::make_shared<Multiplication>(first, second);
  } else {
    auto first = std::make_shared<Exponentiation>(left_argument_, right_argument_);
    auto second = std::make_shared<Addition>(
        std::make_shared<Multiplication>(right_argument_->GetDerivative(), std::make_shared<Logarithm>(left_argument_)),
        std::make_shared<Division>(std::make_shared<Multiplication>(right_argument_, left_argument_->GetDerivative()),
                                   left_argument_));

    return std::make_shared<Multiplication>(first, second);
  }
}

double Exponentiation::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::pow(left_argument_->GetNumericResult(variable_to_value),
                  right_argument_->GetNumericResult(variable_to_value));
}

constants::Expressions Exponentiation::GetType() {
  return constants::Expressions::EXPONENTIATION;
}

std::optional<std::shared_ptr<Expression>> Exponentiation::Simplify() {
  if (auto simplified = left_argument_->Simplify()) {
    left_argument_ = *simplified;
  }

  if (auto simplified = right_argument_->Simplify()) {
    right_argument_ = *simplified;
  }

  if (left_argument_->GetType() == right_argument_->GetType() &&
      left_argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_shared<Number>(GetNumericResult({}));
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 0)) {
    return std::make_shared<Number>(0);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 0)) {
    return std::make_shared<Number>(1);
  }

  if (left_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(left_argument_->GetNumericResult({}), 1)) {
    return std::make_shared<Number>(1);
  }

  if (right_argument_->GetType() == constants::Expressions::NUMBER &&
      utils::Helper::IsEqual(right_argument_->GetNumericResult({}), 1)) {
    return left_argument_;
  }

  return std::nullopt;
}

bool Exponentiation::IsContainVariable() {
  return left_argument_->IsContainVariable() || right_argument_->IsContainVariable();
}

}  // namespace math
