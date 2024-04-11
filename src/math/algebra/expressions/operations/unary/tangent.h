#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "cos.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operations/binary/division.h"
#include "math/algebra/expressions/operations/binary/exponentiation.h"
#include "math/algebra/expressions/operations/binary/multiplication.h"
#include "math/algebra/expressions/operations/unary_operation.h"

namespace math {

class Tangent final : public UnaryOperation {
 public:
  explicit Tangent(std::shared_ptr<Expression> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::shared_ptr<Expression> GetDerivative() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  Expressions GetType() override;
  std::optional<std::shared_ptr<Expression>> Simplify() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::TANGENT);
};

}  // namespace math
