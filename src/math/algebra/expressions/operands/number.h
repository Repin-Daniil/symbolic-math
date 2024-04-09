#pragma once

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include "math/algebra/expressions/expression.h"

namespace math {

class Number : public Expression {
 public:
  explicit Number(double value) : value_(value) {
  }

  std::string GetInfix(int previous_priority) override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;

 private:
  std::string GetString() const noexcept;

 public:
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;

 private:
  double value_;
};

}  // namespace math
