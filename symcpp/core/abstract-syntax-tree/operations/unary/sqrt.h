#pragma once

#include <cmath>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "symcpp/core/abstract-syntax-tree/operands/number_node.h"
#include "symcpp/core/abstract-syntax-tree/operations/binary/division.h"
#include "symcpp/core/abstract-syntax-tree/operations/binary/multiplication.h"
#include "symcpp/core/abstract-syntax-tree/operations/unary_operation.h"

namespace symcpp::math {

class SquareRootNode final : public UnaryOperation {
 public:
  explicit SquareRootNode(std::unique_ptr<TreeNode> argument) : UnaryOperation(std::move(argument)) {
  }

  constants::Expressions GetType() override;

  std::string GetLatex(int previous_priority) override;
  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;

  std::unique_ptr<TreeNode> Evaluate() override;
  std::unique_ptr<TreeNode> GetDerivative(const Symbol& d) override;

  std::unique_ptr<TreeNode> Simplify() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::SQRT);
};

}  // namespace symcpp::math
