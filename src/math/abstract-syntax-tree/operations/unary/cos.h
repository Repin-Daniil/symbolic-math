#pragma once

#include <cmath>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "math/abstract-syntax-tree/operations/binary/multiplication.h"
#include "math/abstract-syntax-tree/operations/unary_operation.h"
#include "sin.h"
#include "unary_minus.h"

namespace math {

class Cos final : public UnaryOperation {
 public:
  explicit Cos(std::unique_ptr<TreeNode> argument) : UnaryOperation(std::move(argument)) {
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
  int priority_ = constants::operations_to_priority.at(constants::Operations::COS);
};

}  // namespace math
