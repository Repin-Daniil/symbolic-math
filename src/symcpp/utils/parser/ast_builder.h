#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <optional>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "symcpp/abstract-syntax-tree/ast.h"
#include "symcpp/constants_storage.h"
#include "symcpp/utils/helper/helper.h"

namespace symcpp::utils {

class TreeBuilder {
 public:
  std::unique_ptr<math::TreeNode> BuildAST(std::string_view rpn_expression);

 private:
  void AddOperation(constants::Operations operation);
  void AddOperand(std::string_view token);
  std::unique_ptr<math::TreeNode> GetOperand();
  void Reset();

 private:
  std::stack<std::unique_ptr<math::TreeNode>> nodes_;
};

}  // namespace symcpp::utils
