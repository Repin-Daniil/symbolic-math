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

#include "core/abstract-syntax-tree/ast.h"
#include "constants_storage.h"
#include "utils/helper/helper.h"

namespace symcpp::utils {

class TreeBuilder {
 public:
  static std::unique_ptr<math::TreeNode> BuildAST(std::string_view rpn_expression, const std::vector<Symbol>& symbols);

 private:
  static void AddOperation(constants::Operations operation);
  static void AddOperand(std::string_view token, const std::vector<Symbol>& symbols);
  static std::unique_ptr<math::TreeNode> GetOperand();
  static void Reset();

 private:
  inline static std::stack<std::unique_ptr<math::TreeNode>> nodes_;
};

}  // namespace symcpp::utils
