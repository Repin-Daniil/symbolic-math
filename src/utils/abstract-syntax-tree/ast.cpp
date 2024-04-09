#include "ast.h"
#include <sstream>
#include <stack>
#include "utils/helper/helper.h"

namespace utils {

TreeBuilder AbstractSyntaxTree::builder;

std::shared_ptr<math::Expression> AbstractSyntaxTree::GetRoot() const {
  return root_;
}

std::string AbstractSyntaxTree::GetRPNExpression() const {
  return root_->GetRPN();
}

std::string AbstractSyntaxTree::GetInfixExpression() const {
  return root_->GetInfix();
}

AbstractSyntaxTree AbstractSyntaxTree::GetDerivative() const {
  return AbstractSyntaxTree(root_->GetDerivative());
}

double AbstractSyntaxTree::GetNumericResult(const std::unordered_map<char, double>& variable_to_value) const {
  return 0;  // TODO
}

void AbstractSyntaxTree::Reset() {
  root_.reset();
}

}  // namespace utils
