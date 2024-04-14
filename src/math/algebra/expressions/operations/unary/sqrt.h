#pragma once

#include <cmath>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operations/binary/division.h"
#include "math/algebra/expressions/operations/binary/multiplication.h"
#include "math/algebra/expressions/operations/unary_operation.h"

namespace math {

class SquareRoot final : public UnaryOperation {
 public:
  explicit SquareRoot(std::shared_ptr<Expression> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::shared_ptr<Expression> GetDerivative() override;
  constants::Expressions GetType() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  std::optional<std::shared_ptr<Expression>> Simplify() override;
  bool IsContainVariable() override;

 private:
  std::optional<double> CheckArgument(const std::unordered_map<char, double>& variable_to_value);

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::SQRT);
};

}  // namespace math
