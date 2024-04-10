#include "ast.h"

namespace utils {

TreeBuilder AbstractSyntaxTree::builder;

std::shared_ptr<math::Expression> AbstractSyntaxTree::GetRoot() const {
  return root_;
}

std::string AbstractSyntaxTree::GetRPNExpression(const std::unordered_map<char, double>& variable_to_value) const {
  return root_->GetRPN(variable_to_value);
}

std::string AbstractSyntaxTree::GetInfixExpression() const {
  return root_->GetInfix(0);
}

AbstractSyntaxTree AbstractSyntaxTree::GetDerivative() const {
  return AbstractSyntaxTree(root_->GetDerivative());
}

double AbstractSyntaxTree::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) const {
  return root_->GetNumericResult(variable_to_value);
}

void AbstractSyntaxTree::Reset() {
  root_.reset();
}

}  // namespace utils
