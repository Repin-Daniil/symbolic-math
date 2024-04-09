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

#include "constants_storage.h"
#include "math/algebra/expressions/math.h"
#include "utils/helper/helper.h"

namespace utils {

class TreeBuilder {
 public:
  std::shared_ptr<math::Expression> BuildAST(std::string_view rpn_expression);

 private:
  void AddOperation(constants::Operations operation);
  void AddOperand(std::string_view token);
  std::shared_ptr<math::Expression> GetOperand();
  void Reset();

 private:
  std::stack<std::shared_ptr<math::Expression>> nodes_;  // TODO Rename
};

}  // namespace utils
