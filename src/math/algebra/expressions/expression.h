#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace math {

class Expression {
 public:
  virtual std::string GetInfix(int previous_priority) = 0;
  virtual std::string GetRPN() = 0;
  virtual std::shared_ptr<Expression> GetDerivative() = 0;
  virtual double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) = 0;

  virtual ~Expression() = default;
};

}  // namespace math
