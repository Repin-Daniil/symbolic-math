#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "math/abstract-syntax-tree/operations/binary/division.h"
#include "math/abstract-syntax-tree/operations/unary_operation.h"

namespace math {

class LogarithmNode final : public UnaryOperation {
 public:
  explicit LogarithmNode(std::unique_ptr<TreeNode> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetInfix(int previous_priority,
                       const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  Number GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  constants::Expressions GetType() override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  std::optional<Number> CheckArgument(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value);

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::NATURAL_LOGARITHM);
};

}  // namespace math
