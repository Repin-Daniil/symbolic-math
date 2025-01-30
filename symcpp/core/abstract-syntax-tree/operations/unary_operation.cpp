#include "unary_operation.h"

#include <unordered_map>
#include <memory>
#include <utility>

namespace symcpp::math {

std::unique_ptr<TreeNode> UnaryOperation::ReleaseArgument() {
  return std::move(argument_);
}

bool UnaryOperation::IsContainVariable(const Symbol& variable) {
  return argument_->IsContainVariable(variable);
}
std::unique_ptr<TreeNode> UnaryOperation::Substitute(
    const std::unordered_map<Symbol, std::unique_ptr<TreeNode>, SymbolHash>& variable_to_value) {
  if (auto new_arg = argument_->Substitute(variable_to_value)) {
    argument_ = std::move(new_arg);
  }

  return nullptr;
}

std::optional<Number> UnaryOperation::GetNumber(const std::unique_ptr<TreeNode>& result) const {
  if (result->GetType() == constants::Expressions::NUMBER) {
    return dynamic_cast<NumberNode*>(result.get())->GetValue();
  }

  return std::nullopt;
}

}  // namespace symcpp::math
