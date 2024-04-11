#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace math {

enum class Expressions {
  NUMBER,
  VARIABLE,
  ADDITION,
  DIVISION,
  EXPONENTIATION,
  MULTIPLICATION,
  SUBTRACTION,
  LOGARITHM,
  COS,
  SIN,
  SQRT,
  TANGENT,
  UNARY_MINUS
};

class Expression {
 public:
  virtual Expressions GetType() = 0;
  virtual std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) = 0;
  virtual std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) = 0;
  virtual std::shared_ptr<Expression> GetDerivative() = 0;
  virtual double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) = 0;
  virtual std::optional<std::shared_ptr<Expression>> Simplify() = 0;
  virtual bool IsContainVariable() = 0;

  virtual ~Expression() = default;
};

}  // namespace math
