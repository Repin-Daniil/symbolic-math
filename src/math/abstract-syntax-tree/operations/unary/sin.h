#pragma once

#include <cmath>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "cos.h"
#include "math/abstract-syntax-tree/operations/binary/multiplication.h"
#include "math/abstract-syntax-tree/operations/unary_operation.h"

namespace math {

class SinNode final : public UnaryOperation {
 public:
  explicit SinNode(std::unique_ptr<TreeNode> argument) : UnaryOperation(std::move(argument)) {
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
  int priority_ = constants::operations_to_priority.at(constants::Operations::SIN);
};

}  // namespace math
