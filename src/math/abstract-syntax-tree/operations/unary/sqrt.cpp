#include "sqrt.h"

namespace math {

std::string SquareRootNode::GetInfix(int previous_priority,
                                     const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kSquareRoot << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string SquareRootNode::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kSquareRoot;
  return stream.str();
}

std::unique_ptr<TreeNode> SquareRootNode::GetDerivative() {
  CheckArgument({});

  return std::make_unique<Division>(
      argument_->GetDerivative(),
      std::make_unique<Multiplication>(std::make_unique<NumberNode>(2),
                                       std::make_unique<SquareRootNode>(argument_->Clone())));
}

Number SquareRootNode::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  auto arg = *CheckArgument(variable_to_value);

  return std::sqrt(arg.GetValue());  // FIXME Функция Sqrt
}

constants::Expressions SquareRootNode::GetType() {
  return constants::Expressions::SQRT;
}

std::optional<std::unique_ptr<TreeNode>> SquareRootNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  }

  if (argument_->GetType() == constants::Expressions::NUMBER) {
    if (utils::Helper::IsEqual(argument_->GetNumericResult({}), 0)) {
      return std::make_unique<NumberNode>(0);
    }

    if (utils::Helper::IsEqual(argument_->GetNumericResult({}), 1)) {
      return std::make_unique<NumberNode>(1);
    }
  }

  return std::nullopt;
}

bool SquareRootNode::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::optional<Number> SquareRootNode::CheckArgument(
    const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value = {}) {
  std::optional<Number> result;

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

std::unique_ptr<TreeNode> SquareRootNode::Clone() {
  return std::make_unique<SquareRootNode>(argument_->Clone());
}

}  // namespace math
