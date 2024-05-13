#include "logarithm.h"

namespace math {

std::string Logarithm::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kLogarithm << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string Logarithm::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kLogarithm;
  return stream.str();
}

std::unique_ptr<Expression> Logarithm::GetDerivative() {
  CheckArgument({});

  return std::make_unique<Division>(argument_->GetDerivative(), argument_->Clone());
}

double Logarithm::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto arg = CheckArgument(variable_to_value);

  return std::log(*arg);
}

constants::Expressions Logarithm::GetType() {
  return constants::Expressions::LOGARITHM;
}

std::optional<std::unique_ptr<Expression>> Logarithm::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  } else if (argument_->GetType() == constants::Expressions::NUMBER &&
             utils::Helper::IsEqual(argument_->GetNumericResult({}), std::numbers::e)) {
    return std::make_unique<Number>(1);
  }

  return std::nullopt;
}

bool Logarithm::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::optional<double> Logarithm::CheckArgument(const std::unordered_map<char, double>& variable_to_value = {}) {
  std::optional<double> result;

  if (!argument_->IsContainVariable()) {
    result = argument_->GetNumericResult({});
  }

  if (!variable_to_value.empty()) {
    result = argument_->GetNumericResult(variable_to_value);
  }

  if (result && (*result < 0 || std::abs(*result - 0) < std::numeric_limits<double>::epsilon())) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongLogarithm.data());
  }

  return result;
}

std::unique_ptr<Expression> Logarithm::Clone() {
  return std::make_unique<Logarithm>(argument_->Clone());
}

}  // namespace math
