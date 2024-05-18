#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "addition.h"
#include "symcpp/abstract-syntax-tree/operands/number_node.h"
#include "symcpp/abstract-syntax-tree/operations/binary_operation.h"
#include "symcpp/utils/helper/helper.h"

namespace symcpp::math {

class Multiplication final : public BinaryOperation {
 public:
  Multiplication(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  constants::Expressions GetType() override;

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;

  std::unique_ptr<TreeNode> Evaluate() override;
  std::unique_ptr<TreeNode> GetDerivative(const Symbol& d) override;

  std::unique_ptr<TreeNode> Simplify() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::MULTIPLICATION);
};

}  // namespace symcpp::math
