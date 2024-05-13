#include "sqrt.h"

namespace math {

std::string SquareRoot::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kSquareRoot << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string SquareRoot::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kSquareRoot;
  return stream.str();
}

std::unique_ptr<Expression> SquareRoot::GetDerivative() {
  CheckArgument({});

  return std::make_unique<Division>(
      argument_->GetDerivative(),
      std::make_unique<Multiplication>(std::make_unique<Number>(2), std::make_unique<SquareRoot>(argument_->Clone())));
}

double SquareRoot::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto arg = *CheckArgument(variable_to_value);

  return std::sqrt(arg);
}

constants::Expressions SquareRoot::GetType() {
  return constants::Expressions::SQRT;
}

std::optional<std::unique_ptr<Expression>> SquareRoot::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  if (argument_->GetType() == constants::Expressions::NUMBER) {
    if (utils::Helper::IsEqual(argument_->GetNumericResult({}), 0)) {
      return std::make_unique<Number>(0);
    }

    if (utils::Helper::IsEqual(argument_->GetNumericResult({}), 1)) {
      return std::make_unique<Number>(1);
    }
  }

  return std::nullopt;
}

bool SquareRoot::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::optional<double> SquareRoot::CheckArgument(const std::unordered_map<char, double>& variable_to_value = {}) {
  std::optional<double> result;

  if (!argument_->IsContainVariable()) {
    result = argument_->GetNumericResult({});
  } else if (!variable_to_value.empty()) {
    result = argument_->GetNumericResult(variable_to_value);
  }

  if (result && result < 0) {
    throw std::runtime_error(constants::ExceptionMessage::kNegativeRoot.data());
  }

  return result;
}

std::unique_ptr<Expression> SquareRoot::Clone() {
  return std::make_unique<SquareRoot>(argument_->Clone());
}

}  // namespace math
