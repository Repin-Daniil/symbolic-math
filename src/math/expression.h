#pragma once

#include <memory>
#include <ostream>
#include "math/abstract-syntax-tree/ast.h"

namespace math {

/**
 * @brief Держит указатель на AST, конструируется от Number, Symbol unique_ptr<TreeNode>
 * @todo Подстановка вместо переменных целых выражений. result = expr.subs({x: 2, y: pi/2})
 * @fixme Проверять везде, что дерево действительно есть. Нас ведь могли помувать и там nullptr стоит. Привет, сегфолт!
 */
class Expression {
 public:
  Expression(std::unique_ptr<TreeNode> tree);  // NOLINT
  Expression(double number);                   // NOLINT
  Expression(const Number& number);            // NOLINT
  Expression(const Symbol& number);            // NOLINT

  Expression(const Expression& other);
  Expression(Expression&& other) noexcept;

  std::string GetInfix(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) const;
  std::string GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) const;
  //  std::string GetLatex(); //TODO

  Expression& operator=(Expression other);

  Expression& operator+=(Expression other);
  Expression& operator-=(Expression other);
  Expression& operator*=(Expression other);
  Expression& operator/=(Expression other);

  friend std::ostream& operator<<(std::ostream& os, const Expression& expression);

  std::unique_ptr<TreeNode> Release();

 private:
  // TODO Метод Substitute

 private:
  std::unique_ptr<TreeNode> root_;
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

std::string Infix(const Expression& expression, const std::unordered_map<Symbol, Number, SymbolHash>&
                                                    variable_to_value);  // TODO Подставлять Expression, а не Number
std::string RPN(const Expression& expression, const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value);
// std::string Latex(const Expression& expression, const std::unordered_map<Symbol, Number, SymbolHash>&
// variable_to_value);
Expression Evaluate(const Expression& expression,
                    const std::unordered_map<Symbol, Expression, SymbolHash>& variable_to_value);

}  // namespace math
