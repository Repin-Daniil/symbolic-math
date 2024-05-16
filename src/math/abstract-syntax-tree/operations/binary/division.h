#pragma once

#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "exponentiation.h"
#include "math/abstract-syntax-tree/operands/number_node.h"
#include "math/abstract-syntax-tree/operations/binary_operation.h"
#include "math/utils/helper/helper.h"
#include "multiplication.h"
#include "subtraction.h"

namespace math {

class Division final : public BinaryOperation {
 public:
  Division(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  constants::Expressions GetType() override;
  std::string GetInfix(int previous_priority,
                       const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  Number GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  std::unique_ptr<TreeNode> Clone() override;
  bool IsContainVariable() override;

  std::optional<std::unique_ptr<TreeNode>> Simplify() override;

 private:
  std::optional<Number> CheckDivider(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value);

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::DIVISION);
};

}  // namespace math
