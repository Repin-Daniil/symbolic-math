#pragma once

#include <cmath>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "math/abstract-syntax-tree/operands/number.h"
#include "math/abstract-syntax-tree/operations/binary/division.h"
#include "math/abstract-syntax-tree/operations/binary/multiplication.h"
#include "math/abstract-syntax-tree/operations/unary_operation.h"

namespace math {

class SquareRoot final : public UnaryOperation {
 public:
  explicit SquareRoot(std::unique_ptr<TreeNode> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  constants::Expressions GetType() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  std::optional<double> CheckArgument(const std::unordered_map<char, double>& variable_to_value);

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::SQRT);
};

}  // namespace math
