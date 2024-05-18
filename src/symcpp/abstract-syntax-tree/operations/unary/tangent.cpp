#include "tangent.h"

namespace symcpp::math {

std::string TangentNode::GetInfix(int previous_priority) {
  std::stringstream stream;
  stream << constants::Labels::kTan << constants::Labels::kOpenParen << argument_->GetInfix(0)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string TangentNode::GetRPN() {
  std::stringstream stream;
  stream << argument_->GetRPN() << " " << constants::Labels::kTan;
  return stream.str();
}

std::unique_ptr<TreeNode> TangentNode::GetDerivative(const Symbol& d) {
  return std::make_unique<Division>(
      argument_->GetDerivative(d),
      std::make_unique<Exponentiation>(std::make_unique<CosNode>(argument_->Clone()), std::make_unique<NumberNode>(2)));
}

constants::Expressions TangentNode::GetType() {
  return constants::Expressions::TANGENT;
}

std::unique_ptr<TreeNode> TangentNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(simplified);
  }

  return nullptr;
}

std::unique_ptr<TreeNode> TangentNode::Clone() {
  return std::make_unique<TangentNode>(argument_->Clone());
}

std::unique_ptr<TreeNode> TangentNode::Evaluate() {
  auto arg_result = argument_->Evaluate();

  if (auto result = GetNumber(arg_result)) {
    // TODO Заменить std::abs на свой Abs
    if (std::abs(std::numbers::pi / 2.0 - std::fmod(result->GetValue(), std::numbers::pi)) <
        std::numeric_limits<double>::epsilon()) {
      throw std::runtime_error(constants::ExceptionMessage::kWrongTangent.data());
    }

    return std::make_unique<NumberNode>(Tan(*result));
  }

  return std::make_unique<TangentNode>(std::move(arg_result));
}

}  // namespace symcpp::math
