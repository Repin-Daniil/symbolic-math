#include "cos.h"

namespace symcpp::math {

std::string CosNode::GetInfix(int previous_priority) {
  std::stringstream stream;
  stream << constants::Labels::kCos << constants::Labels::kOpenParen << argument_->GetInfix(0)
         << constants::Labels::kEndParen;

  return stream.str();
}

std::string CosNode::GetRPN() {
  std::stringstream stream;
  stream << argument_->GetRPN() << " " << constants::Labels::kCos;
  return stream.str();
}

std::unique_ptr<TreeNode> CosNode::GetDerivative(const Symbol& d) {
  return std::make_unique<UnaryMinus>(
      std::make_unique<Multiplication>(std::make_unique<SinNode>(argument_->Clone()), argument_->GetDerivative(d)));
}

constants::Expressions CosNode::GetType() {
  return constants::Expressions::COS;
}

std::unique_ptr<TreeNode> CosNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(simplified);
  }

  return nullptr;
}

std::unique_ptr<TreeNode> CosNode::Clone() {
  return std::make_unique<CosNode>(argument_->Clone());
}

std::unique_ptr<TreeNode> CosNode::Evaluate() {
  auto arg_result = argument_->Evaluate();

  if (auto result = GetNumber(arg_result)) {
    return std::make_unique<NumberNode>(std::cos(result->GetValue()));
  }

  return std::make_unique<CosNode>(std::move(arg_result));
}

}  // namespace symcpp::math
