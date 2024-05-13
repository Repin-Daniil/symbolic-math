#include "cos.h"

namespace math {

std::string Cos::GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kCos << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;

  return stream.str();
}

std::string Cos::GetRPN(const std::unordered_map<char, double>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kCos;
  return stream.str();
}

std::unique_ptr<Expression> Cos::GetDerivative() {
  return std::make_unique<UnaryMinus>(
      std::make_unique<Multiplication>(std::make_unique<Sin>(argument_->Clone()), argument_->GetDerivative()));
}

double Cos::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::cos(argument_->GetNumericResult(variable_to_value));
}

constants::Expressions Cos::GetType() {
  return constants::Expressions::COS;
}

std::optional<std::unique_ptr<Expression>> Cos::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  return std::nullopt;
}

bool Cos::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::unique_ptr<Expression> Cos::Clone() {
  return std::make_unique<Cos>(argument_->Clone());
}

}  // namespace math
