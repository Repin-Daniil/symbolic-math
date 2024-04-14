#pragma once

#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include "constants_storage.h"
#include "math/algebra/expressions/expression.h"

namespace math {

class Number : public Expression {
 public:
  explicit Number(double value) : value_(value) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::shared_ptr<Expression> GetDerivative() override;
  constants::Expressions GetType() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  std::optional<std::shared_ptr<Expression>> Simplify() override;
  bool IsContainVariable() override;

 private:
  std::string GetString() const noexcept;

 private:
  double value_;
};

}  // namespace math
