#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "addition.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operations/binary_operation.h"
#include "utils/helper/helper.h"

namespace math {

class Multiplication final : public BinaryOperation {
 public:
  Multiplication(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
      : BinaryOperation(std::move(left), std::move(right)) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::shared_ptr<Expression> GetDerivative() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  Expressions GetType() override;
  std::optional<std::shared_ptr<Expression>> Simplify() override;
  bool IsContainVariable() override;

 private:
  int priority_ = constants::operations_to_priority.at(constants::Operations::MULTIPLICATION);
};

}  // namespace math
