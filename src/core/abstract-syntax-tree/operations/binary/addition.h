#pragma once

#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "constants_storage.h"
#include "core/abstract-syntax-tree/operands/number_node.h"
#include "core/abstract-syntax-tree/operations/binary_operation.h"
#include "core/abstract-syntax-tree/operations/unary_operation.h"
#include "utils/helper/helper.h"
#include "subtraction.h"

namespace symcpp::math {

class Addition final : public BinaryOperation {
 public:
  Addition(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
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
  int priority_ = constants::operations_to_priority.at(constants::Operations::ADDITION);
};

}  // namespace symcpp::math
