#pragma once

#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "math/abstract-syntax-tree/node.h"
#include "math/constants_storage.h"
#include "math/number.h"
#include "math/symbol.h"

namespace math {

class NumberNode final : public TreeNode {
 public:
  explicit NumberNode(const Number& value) : value_(value) {
  }

  std::string GetInfix(int previous_priority,
                       const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::unique_ptr<TreeNode> GetDerivative() override;
  constants::Expressions GetType() override;
  Number GetNumericResult(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) override;
  std::optional<std::unique_ptr<TreeNode>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  Number value_;
};

}  // namespace math
