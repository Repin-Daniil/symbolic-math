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

std::shared_ptr<Expression> Cos::GetDerivative() {
  return std::make_shared<UnaryMinus>(
      std::make_shared<Multiplication>(std::make_shared<Sin>(argument_), argument_->GetDerivative()));
}

double Cos::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) {
  return std::cos(argument_->GetNumericResult(variable_to_value));
}

constants::Expressions Cos::GetType() {
  return constants::Expressions::COS;
}

std::optional<std::shared_ptr<Expression>> Cos::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = *simplified;
  }

  return std::nullopt;
}

bool Cos::IsContainVariable() {
  return argument_->IsContainVariable();
}

}  // namespace math
