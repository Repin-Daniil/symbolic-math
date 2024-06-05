#include "sqrt.h"

namespace symcpp::math {

std::string SquareRootNode::GetLatex(int previous_priority) {
  std::stringstream stream;
  stream << constants::Labels::kLatexSlash << constants::Labels::kSquareRoot << constants::Labels::kLatexOpenCurlyBrace
         << argument_->GetLatex(0) << constants::Labels::kLatexEndCurlyBrace;
  return stream.str();
}

std::string SquareRootNode::GetInfix(int previous_priority) {
  std::stringstream stream;
  stream << constants::Labels::kSquareRoot << constants::Labels::kOpenParen << argument_->GetInfix(0)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string SquareRootNode::GetRPN() {
  std::stringstream stream;
  stream << argument_->GetRPN() << " " << constants::Labels::kSquareRoot;
  return stream.str();
}

std::unique_ptr<TreeNode> SquareRootNode::GetDerivative(const Symbol& d) {
  return std::make_unique<Division>(
      argument_->GetDerivative(d),
      std::make_unique<Multiplication>(std::make_unique<NumberNode>(2),
                                       std::make_unique<SquareRootNode>(argument_->Clone())));
}

constants::Expressions SquareRootNode::GetType() {
  return constants::Expressions::SQRT;
}

std::unique_ptr<TreeNode> SquareRootNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(simplified);
  }

  if (argument_->GetType() == constants::Expressions::NUMBER) {
    if (utils::Helper::IsEqual(*GetNumber(argument_), 0)) {
      return std::make_unique<NumberNode>(0);
    }

    if (utils::Helper::IsEqual(*GetNumber(argument_), 1)) {
      return std::make_unique<NumberNode>(1);
    }
  }

  return nullptr;
}

std::unique_ptr<TreeNode> SquareRootNode::Clone() {
  return std::make_unique<SquareRootNode>(argument_->Clone());
}

std::unique_ptr<TreeNode> SquareRootNode::Evaluate() {
  auto arg_result = argument_->Evaluate();

  if (auto result = GetNumber(arg_result)) {
    if (result < 0) {
      throw std::runtime_error(constants::ExceptionMessage::kNegativeRoot.data());
    }

    return std::make_unique<NumberNode>(std::sqrt(result->GetValue()));
  }

  return std::make_unique<SquareRootNode>(std::move(arg_result));
}

}  // namespace symcpp::math
