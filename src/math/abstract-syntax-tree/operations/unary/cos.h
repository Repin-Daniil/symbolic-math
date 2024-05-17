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

class CosNode final : public UnaryOperation {
 public:
  explicit CosNode(std::unique_ptr<TreeNode> argument) : UnaryOperation(std::move(argument)) {
  }

  constants::Expressions GetType() override;

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;

  std::unique_ptr<TreeNode> Evaluate() override;
  std::unique_ptr<TreeNode> GetDerivative(const Symbol& d) override;

  std::unique_ptr<TreeNode> Simplify() override;
  std::unique_ptr<TreeNode> Clone() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::COS);
};

}  // namespace math
