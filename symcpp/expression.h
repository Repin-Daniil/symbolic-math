#pragma once

#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "core/abstract-syntax-tree/ast.h"
#include "core/abstract-syntax-tree/operands/constant_node.h"
#include "utils/converter/converter.h"

namespace symcpp {

/**
 * @brief Держит указатель на AST, конструируется от Number, Symbol, unique_ptr<TreeNode>
 * @todo Copy-on-write, держать указатель shared_ptr на корень
 */
class Expression {
 public:
  Expression() = default;
  Expression(std::unique_ptr<math::TreeNode> tree);  // NOLINT
  Expression(double number);                         // NOLINT
  Expression(const Number& number);                  // NOLINT
  Expression(Symbol& number);                        // NOLINT
  Expression(const Symbol& number);                  // NOLINT
  Expression(std::string infix_expression, const std::vector<Symbol>& symbols);

  Expression(const Expression& other);
  Expression(Expression&& other) noexcept;

  std::string GetLatex() const;
  std::string GetInfix() const;
  std::string GetRPN() const;

  Expression& operator=(Expression other);

  Expression& operator+=(Expression other);
  Expression& operator-=(Expression other);
  Expression& operator*=(Expression other);
  Expression& operator/=(Expression other);

  friend std::ostream& operator<<(std::ostream& os, const Expression& expression);

  Expression GetDerivative(const Symbol& d) const;
  Expression Evaluate() const;
  Expression Substitute(std::unordered_map<Symbol, Expression, SymbolHash> variable_to_value) const;
  void Simplify();

  std::unique_ptr<math::TreeNode> Release();
  std::unique_ptr<math::TreeNode> GetCopy() const;

 private:
  std::unique_ptr<math::TreeNode> root_;
};

Expression operator+(Expression lhs, Expression rhs);
Expression operator-(Expression lhs, Expression rhs);
Expression operator*(Expression lhs, Expression rhs);
Expression operator/(Expression lhs, Expression rhs);

Expression operator-(Expression number);
Expression operator+(Expression number);

Expression Log(Expression argument);
Expression Sin(Expression argument);
Expression Cos(Expression argument);
Expression Tan(Expression argument);
Expression Sqrt(Expression argument);
Expression Pow(Expression base, Expression power);

std::string Infix(const Expression& expression);
std::string RPN(const Expression& expression);
std::string Latex(const Expression& expression);

Expression Diff(const Expression& expression, Symbol d);
Expression Evaluate(const Expression& expression);
Expression Evaluate(const Expression& expression, std::unordered_map<Symbol, Expression, SymbolHash> variable_to_value);
Expression Substitute(const Expression& expression,
                      std::unordered_map<Symbol, Expression, SymbolHash> variable_to_value);

}  // namespace symcpp
