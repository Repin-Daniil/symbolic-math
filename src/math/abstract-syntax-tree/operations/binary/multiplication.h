#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "addition.h"
#include "math/abstract-syntax-tree/operands/number.h"
#include "math/abstract-syntax-tree/operations/binary_operation.h"
#include "math/utils/helper/helper.h"

namespace math {

class Multiplication final : public BinaryOperation {
 public:
  Multiplication(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  constants::Expressions GetType() override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::MULTIPLICATION);
};

}  // namespace math
