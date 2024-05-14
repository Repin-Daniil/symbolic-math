#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "math/abstract-syntax-tree/expression.h"
#include "math/constants_storage.h"
#include "number.h"

namespace math {

class Variable final : public TreeNode {
 public:
  explicit Variable(char symbol) : symbol_(symbol) {
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
  std::string GetString() const noexcept;

 private:
  char symbol_;
};

}  // namespace math
