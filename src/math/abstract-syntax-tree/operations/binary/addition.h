#pragma once

#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "math/abstract-syntax-tree/operands/number.h"
#include "math/abstract-syntax-tree/operations/binary_operation.h"
#include "math/abstract-syntax-tree/operations/unary_operation.h"
#include "math/constants_storage.h"
#include "math/utils/helper/helper.h"
#include "subtraction.h"

namespace math {

class Addition final : public BinaryOperation {
 public:
  Addition(std::unique_ptr<TreeNode> left, std::unique_ptr<TreeNode> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  constants::Expressions GetType() override;
  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::ADDITION);
};

}  // namespace math
