#include "tangent.h"

namespace math {

std::string Tangent::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kTan << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string Tangent::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kTan;
  return stream.str();
}

std::unique_ptr<Expression> Tangent::GetDerivative() {
  CheckArgument({});

  return std::make_unique<Division>(
      argument_->GetDerivative(),
      std::make_unique<Exponentiation>(std::make_unique<Cos>(argument_->Clone()), std::make_unique<Number>(2)));
}

double Tangent::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  auto arg = CheckArgument(variable_to_value);

  return std::tan(*arg);
}

constants::Expressions Tangent::GetType() {
  return constants::Expressions::TANGENT;
}

std::optional<std::unique_ptr<Expression>> Tangent::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  return std::nullopt;
}

bool Tangent::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::optional<double> Tangent::CheckArgument(const std::unordered_map<char, double>& variable_to_value = {}) {
  std::optional<double> result;

  if (!argument_->IsContainVariable()) {
    result = argument_->GetNumericResult({});
  } else if (!variable_to_value.empty()) {
    result = argument_->GetNumericResult(variable_to_value);
  }

  if (result && (std::abs(std::numbers::pi / 2.0 - std::fmod(*result, std::numbers::pi)) <
                 std::numeric_limits<double>::epsilon())) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongTangent.data());
  }

  return result;
}

std::unique_ptr<Expression> Tangent::Clone() {
  return std::make_unique<Tangent>(argument_->Clone());
}

}  // namespace math
