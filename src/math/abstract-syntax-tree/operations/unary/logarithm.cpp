#include "logarithm.h"

namespace math {

std::string LogarithmNode::GetInfix(int previous_priority,
                                    const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << constants::Labels::kLogarithm << constants::Labels::kOpenParen << argument_->GetInfix(0, variable_to_value)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string LogarithmNode::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  std::stringstream stream;
  stream << argument_->GetRPN(variable_to_value) << " " << constants::Labels::kLogarithm;
  return stream.str();
}

std::unique_ptr<TreeNode> LogarithmNode::GetDerivative() {
  CheckArgument({});

  return std::make_unique<Division>(argument_->GetDerivative(), argument_->Clone());
}

Number LogarithmNode::GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  auto arg = CheckArgument(variable_to_value);

  return std::log(arg->GetValue());
}

constants::Expressions LogarithmNode::GetType() {
  return constants::Expressions::LOGARITHM;
}

std::optional<std::unique_ptr<TreeNode>> LogarithmNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(*simplified);
  } else if (argument_->GetType() == constants::Expressions::NUMBER &&
             utils::Helper::IsEqual(argument_->GetNumericResult({}), std::numbers::e)) {
    return std::make_unique<NumberNode>(1);
  }

  return std::nullopt;
}

bool LogarithmNode::IsContainVariable() {
  return argument_->IsContainVariable();
}

std::optional<Number> LogarithmNode::CheckArgument(
    const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value = {}) {
  std::optional<Number> result;

  if (!argument_->IsContainVariable()) {
    result = argument_->GetNumericResult({});
  }

  if (!variable_to_value.empty()) {
    result = argument_->GetNumericResult(variable_to_value);
  }

  // TODO Заменить std::abs на свой Abs
  if (result && (*result < 0 || std::abs(result->GetValue() - 0) < std::numeric_limits<double>::epsilon())) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongLogarithm.data());
  }

  return result;
}

std::unique_ptr<TreeNode> LogarithmNode::Clone() {
  return std::make_unique<LogarithmNode>(argument_->Clone());
}

}  // namespace math
