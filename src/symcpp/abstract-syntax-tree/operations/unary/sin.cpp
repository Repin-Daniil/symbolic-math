#include "sin.h"

namespace symcpp::math {

std::string SinNode::GetInfix(int previous_priority) {
  std::stringstream stream;
  stream << constants::Labels::kSin << constants::Labels::kOpenParen << argument_->GetInfix(0)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string SinNode::GetRPN() {
  std::stringstream stream;
  stream << argument_->GetRPN() << " " << constants::Labels::kSin;
  return stream.str();
}

std::unique_ptr<TreeNode> SinNode::GetDerivative(const Symbol& d) {
  return std::make_unique<Multiplication>(std::make_unique<CosNode>(argument_->Clone()), argument_->GetDerivative(d));
}

constants::Expressions SinNode::GetType() {
  return constants::Expressions::SIN;
}

std::unique_ptr<TreeNode> SinNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(simplified);
  }

  return nullptr;
}

std::unique_ptr<TreeNode> SinNode::Clone() {
  return std::make_unique<SinNode>(argument_->Clone());
}

std::unique_ptr<TreeNode> SinNode::Evaluate() {
  auto arg_result = argument_->Evaluate();

  if (auto result = GetNumber(arg_result)) {
    return std::make_unique<NumberNode>(Sin(*result));
  }

  return std::make_unique<SinNode>(std::move(arg_result));
}

}  // namespace symcpp::math
