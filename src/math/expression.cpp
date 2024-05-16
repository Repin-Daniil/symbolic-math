#include "expression.h"
#include <iostream>

namespace math {

Expression::Expression(std::unique_ptr<TreeNode> tree) : root_(std::move(tree)) {
  std::cout << "Get Root! " << root_->GetInfix(0, {}) << std::endl;
}

Expression::Expression(const Number& number) : root_(std::make_unique<NumberNode>(number)) {
}

Expression::Expression(double number) : root_(std::make_unique<NumberNode>(number)) {
}

Expression::Expression(const Symbol& symbol) : root_(std::make_unique<Variable>(symbol)) {
}

Expression::Expression(Expression&& other) noexcept : root_(std::move(other.root_)) {
  std::cout << "Move Expression!" << root_->GetInfix(0, {}) << std::endl;
}

Expression::Expression(const Expression& other) : root_(other.root_->Clone()) {
  std::cout << "Clone Expression!" << root_->GetInfix(0, {}) << std::endl;
}

std::unique_ptr<TreeNode> Expression::Release() {
  return std::move(root_);
}

std::string Expression::GetInfix(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) const {
  if (root_) {
    return root_->GetInfix(0, variable_to_value);
  }

  return {};
}

std::string Expression::GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) const {
  if (root_) {
    return root_->GetRPN(variable_to_value);
  }

  return {};
}

Expression& Expression::operator=(Expression other) {
  root_ = other.Release();
  return *this;
}

Expression& Expression::operator+=(Expression other) {
  if (root_) {
    root_ = std::make_unique<Addition>(std::move(root_), other.Release());
  } else {
    root_ = other.Release();
  }

  return *this;
}

Expression& Expression::operator/=(Expression other) {
  if (root_) {
    root_ = std::make_unique<Division>(std::move(root_), other.Release());
  } else {
    root_ = other.Release();
  }
  return *this;
}

Expression& Expression::operator*=(Expression other) {
  if (root_) {
    root_ = std::make_unique<Multiplication>(std::move(root_), other.Release());
  } else {
    root_ = other.Release();
  }
  return *this;
}

Expression& Expression::operator-=(Expression other) {
  if (root_) {
    root_ = std::make_unique<Subtraction>(std::move(root_), other.Release());
  } else {
    root_ = other.Release();
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Expression& expression) {
  os << expression.GetInfix({});
  return os;
}

Expression operator+(Expression lhs, Expression rhs) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<Addition>(lhs.Release(), rhs.Release());
  return new_root;
}

Expression operator-(Expression lhs, Expression rhs) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<Subtraction>(lhs.Release(), rhs.Release());
  return new_root;
}

Expression operator*(Expression lhs, Expression rhs) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<Multiplication>(lhs.Release(), rhs.Release());
  return new_root;
}

Expression operator/(Expression lhs, Expression rhs) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<Division>(lhs.Release(), rhs.Release());
  return new_root;
}

Expression operator-(Expression argument) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<UnaryMinus>(argument.Release());
  return new_root;
}

Expression operator+(Expression argument) {
  return argument.Release();
}

Expression Log(Expression argument) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<LogarithmNode>(argument.Release());
  return new_root;
}

Expression Sin(Expression argument) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<SinNode>(argument.Release());
  return new_root;
}

Expression Cos(Expression argument) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<CosNode>(argument.Release());
  return new_root;
}

Expression Tan(Expression argument) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<TangentNode>(argument.Release());
  return new_root;
}

Expression Sqrt(Expression argument) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<SquareRootNode>(argument.Release());
  return new_root;
}

Expression Pow(Expression base, Expression power) {
  std::unique_ptr<TreeNode> new_root = std::make_unique<Exponentiation>(base.Release(), power.Release());
  return new_root;
}

std::string RPN(const Expression& expression, const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  return expression.GetRPN(variable_to_value);
}

std::string Infix(const Expression& expression,
                  const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) {
  return expression.GetInfix(variable_to_value);
}

// std::string Latex(const Expression& expression) {
//   return std::string();
// }

}  // namespace math
