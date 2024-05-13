#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "constants_storage.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operations/binary_operation.h"
#include "math/algebra/expressions/operations/unary/unary_minus.h"
#include "utils/helper/helper.h"

namespace math {

class Subtraction final : public BinaryOperation {
 public:
  Subtraction(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::unique_ptr<Expression> GetDerivative() override;
  constants::Expressions GetType() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  std::optional<std::unique_ptr<Expression>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<Expression> Clone() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::SUBTRACTION);
};

}  // namespace math
