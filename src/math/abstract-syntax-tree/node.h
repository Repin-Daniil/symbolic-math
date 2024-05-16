#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "math/constants_storage.h"
#include "math/number.h"
#include "math/symbol.h"

namespace math {

// TODO GetNumericResult вызывает себя у детей, затем IsContainVariable. Если false, то Evaluate. Возвращает
// unique_ptr<TreeNode>
class TreeNode {
 public:
  virtual constants::Expressions GetType() = 0;
  virtual std::string GetInfix(int previous_priority,
                               const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) = 0;
  virtual std::string GetRPN(const std::unordered_map<Symbol, Number, SymbolHash>& variable_to_value) = 0;
  virtual std::unique_ptr<TreeNode> GetDerivative() = 0;
  virtual Number GetNumericResult(
      const std::unordered_map<Symbol, Number, SymbolHash>&
          variable_to_value) = 0;  // TODO Заменить бы Number на Expression, это будет более гибким
  virtual std::optional<std::unique_ptr<TreeNode>> Simplify() = 0;
  virtual bool IsContainVariable() = 0;
  virtual std::unique_ptr<TreeNode> Clone() = 0;

  virtual ~TreeNode() = default;
};

}  // namespace math
