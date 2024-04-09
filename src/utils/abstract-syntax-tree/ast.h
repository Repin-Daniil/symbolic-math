#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include "ast_builder.h"
#include "math/algebra/expressions/expression.h"

namespace utils {

class AbstractSyntaxTree {
 public:
  AbstractSyntaxTree() = default;
  explicit AbstractSyntaxTree(std::string_view rpn_expression) {
    root_ = builder.BuildAST(rpn_expression);
  }

  explicit AbstractSyntaxTree(std::shared_ptr<math::Expression> root) : root_(std::move(root)) {
  }

  std::shared_ptr<math::Expression> GetRoot() const;
  std::string GetRPNExpression() const;      // TODO Передавать сюда переменные
  std::string GetInfixExpression() const;    // TODO Передавать сюда переменные
  AbstractSyntaxTree GetDerivative() const;  // TODO Передавать сюда переменные
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) const;

  void Reset();

 private:
  static TreeBuilder builder;
  std::shared_ptr<math::Expression> root_;
};

}  // namespace utils
