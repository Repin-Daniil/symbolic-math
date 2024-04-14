#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "ast_builder.h"
#include "math/algebra/expressions/expression.h"
#include "utils/helper/helper.h"

namespace utils {

class AbstractSyntaxTree {
 public:
  AbstractSyntaxTree() = default;
  explicit AbstractSyntaxTree(std::string_view rpn_expression);
  explicit AbstractSyntaxTree(std::shared_ptr<math::Expression> root);

  std::shared_ptr<math::Expression> GetRoot() const;
  std::string GetRPNExpression(const std::unordered_map<char, double>& variable_to_value) const;
  std::string GetInfixExpression(const std::unordered_map<char, double>& variable_to_value) const;
  AbstractSyntaxTree GetDerivative() const;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) const;

  void Simplify();
  void Reset();

 private:
  static TreeBuilder builder;
  std::shared_ptr<math::Expression> root_;
};

}  // namespace utils
