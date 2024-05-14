#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "addition.h"
#include "division.h"
#include "math/abstract-syntax-tree/operations/binary_operation.h"
#include "math/abstract-syntax-tree/operations/unary/logarithm.h"
#include "math/utils/helper/helper.h"
#include "multiplication.h"

namespace math {

class Exponentiation final : public BinaryOperation {
 public:
  Exponentiation(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  constants::Expressions GetType() override;
  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::EXPONENTIATION);
};

}  // namespace math
