#pragma once

#include <memory>
#include <numbers>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "addition.h"

#include "core/abstract-syntax-tree/operations/binary_operation.h"

namespace symcpp::math {

class Exponentiation final : public BinaryOperation {
 public:
  Exponentiation(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
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
  int priority_ = constants::operations_to_priority.at(constants::Operations::EXPONENTIATION);
};

}  // namespace symcpp::math
