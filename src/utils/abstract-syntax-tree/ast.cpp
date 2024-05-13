#include "ast.h"

namespace utils {

TreeBuilder AbstractSyntaxTree::builder;

AbstractSyntaxTree::AbstractSyntaxTree(std::string_view rpn_expression) {
  root_ = std::move(builder.BuildAST(rpn_expression));
  Simplify();
}

AbstractSyntaxTree::AbstractSyntaxTree(std::unique_ptr<math::Expression> root) : root_(std::move(root)) {
  Simplify();
}

const math::Expression& AbstractSyntaxTree::GetRoot() const {
  return *root_;
}

std::string AbstractSyntaxTree::GetRPNExpression(const std::unordered_map<char, double>& variable_to_value) const {
  return root_->GetRPN(variable_to_value);
}

std::string AbstractSyntaxTree::GetInfixExpression(const std::unordered_map<char, double>& variable_to_value) const {
  return root_->GetInfix(0, variable_to_value);
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

void AbstractSyntaxTree::Simplify() {
  if (auto simplified = root_->Simplify()) {
    root_ = std::move(*simplified);
  }
}

}  // namespace utils
