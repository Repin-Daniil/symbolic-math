#include "unary_minus.h"

namespace symcpp::math {

std::string UnaryMinus::GetLatex(int previous_priority) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kLatexOpenParen : "") << constants::Labels::kMinus
         << argument_->GetLatex(constants::operations_to_priority.at(constants::Operations::SUBTRACTION))
         << std::string(brackets_required ? constants::Labels::kLatexEndParen : "");

  return stream.str();
}

std::string UnaryMinus::GetInfix(int previous_priority) {
  bool brackets_required =
      previous_priority == constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
  std::stringstream stream;
  stream << (brackets_required ? constants::Labels::kOpenParen : "") << constants::Labels::kMinus
         << argument_->GetInfix(constants::operations_to_priority.at(constants::Operations::SUBTRACTION))
         << std::string(brackets_required ? constants::Labels::kEndParen : "");

  return stream.str();
}

std::string UnaryMinus::GetRPN() {
  return argument_->GetRPN() + " ~";
}

std::unique_ptr<TreeNode> UnaryMinus::GetDerivative(const Symbol& d) {
  return std::make_unique<UnaryMinus>(argument_->GetDerivative(d));
}

constants::Expressions UnaryMinus::GetType() {
  return constants::Expressions::UNARY_MINUS;
}

std::unique_ptr<TreeNode> UnaryMinus::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(simplified);
  }

  if (argument_->GetType() == constants::Expressions::UNARY_MINUS) {
    return dynamic_cast<UnaryOperation*>(argument_.get())->ReleaseArgument();
  }

  if (argument_->GetType() == constants::Expressions::NUMBER) {
    return std::make_unique<NumberNode>(-(*GetNumber(argument_)));
  }

  return nullptr;
}

std::unique_ptr<TreeNode> UnaryMinus::Clone() {
  return std::make_unique<UnaryMinus>(argument_->Clone());
}

std::unique_ptr<TreeNode> UnaryMinus::Evaluate() {
  auto arg_result = argument_->Evaluate();

  if (auto result = GetNumber(arg_result)) {
    return std::make_unique<NumberNode>(-(*result));
  }

  return std::make_unique<UnaryMinus>(std::move(arg_result));
}

}  // namespace symcpp::math
