#include "binary_operation.h"

#include <unordered_map>
#include <memory>
#include <utility>

namespace symcpp::math {

std::unique_ptr<TreeNode> BinaryOperation::ReleaseLeftArgument() {
  return std::move(left_argument_);
}

std::unique_ptr<TreeNode> BinaryOperation::ReleaseRightArgument() {
  return std::move(right_argument_);
}

bool BinaryOperation::IsContainVariable(const Symbol& variable) {
  return left_argument_->IsContainVariable(variable) || right_argument_->IsContainVariable(variable);
}

bool BinaryOperation::IsA(constants::Expressions node_type) {
  return node_type == constants::Expressions::BINARY_OPERATION || GetType() == node_type;
}

std::unique_ptr<TreeNode> BinaryOperation::Substitute(
    const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) {
  if (auto new_left = left_argument_->Substitute(variable_to_value)) {
    left_argument_ = std::move(new_left);
  }

  if (auto new_right = right_argument_->Substitute(variable_to_value)) {
    right_argument_ = std::move(new_right);
  }

  return nullptr;
}

std::optional<Number> BinaryOperation::GetNumber(const std::unique_ptr<TreeNode>& result) const {
  if (result->GetType() == constants::Expressions::NUMBER) {
    return dynamic_cast<NumberNode*>(result.get())->GetValue();
  }

  return std::nullopt;
}

}  // namespace symcpp::math
