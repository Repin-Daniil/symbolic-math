#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "math/abstract-syntax-tree/operands/number_node.h"
#include "math/abstract-syntax-tree/operations/binary_operation.h"
#include "math/abstract-syntax-tree/operations/unary/unary_minus.h"
#include "math/constants_storage.h"
#include "math/utils/helper/helper.h"

namespace math {

class Subtraction final : public BinaryOperation {
 public:
  Subtraction(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(int previous_priority,
                       const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  constants::Expressions GetType() override;
  Number GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
};

}  // namespace math
