#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "math/constants_storage.h"

namespace math {

class TreeNode {
 public:
  virtual constants::Expressions GetType() = 0;
  virtual std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) = 0;
  virtual std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) = 0;
  virtual std::unique_ptr<TreeNode> GetDerivative() = 0;
  virtual double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) = 0;
  virtual std::optional<std::unique_ptr<TreeNode>> Simplify() = 0;
  virtual bool IsContainVariable() = 0;
  virtual std::unique_ptr<TreeNode> Clone() = 0;

  virtual ~TreeNode() = default;
};

}  // namespace math
