#pragma once

#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "exponentiation.h"
#include "multiplication.h"
#include "subtraction.h"
#include "symcpp/core/abstract-syntax-tree/operands/number_node.h"
#include "symcpp/core/abstract-syntax-tree/operations/binary_operation.h"
#include "symcpp/utils/helper/helper.h"

namespace symcpp::math {

class Division final : public BinaryOperation {
 public:
  Division(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  constants::Expressions GetType() override;

  std::string GetLatex(int previous_priority) override;
  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;

  std::unique_ptr<TreeNode> Evaluate() override;
  std::unique_ptr<TreeNode> GetDerivative(const Symbol& d) override;

  std::unique_ptr<TreeNode> Clone() override;
  std::unique_ptr<TreeNode> Simplify() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::DIVISION);
};

}  // namespace symcpp::math
