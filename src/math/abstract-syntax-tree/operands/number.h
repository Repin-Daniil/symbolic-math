#pragma once

#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "math/abstract-syntax-tree/expression.h"
#include "math/constants_storage.h"

namespace math {

class Number final : public TreeNode {
 public:
  explicit Number(double value) : value_(value) {
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
  std::string GetString() const noexcept;

 private:
  double value_;
};

}  // namespace math
