#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "constants_storage.h"
#include "math/algebra/expressions/expression.h"
#include "number.h"

namespace math {

class Variable final : public Expression {
 public:
  explicit Variable(char symbol) : symbol_(symbol) {
  }

  std::string GetInfix(int previous_priority, const std::unordered_map<char, double>& variable_to_value) override;
  std::string GetRPN(const std::unordered_map<char, double>& variable_to_value) override;
  std::unique_ptr<Expression> GetDerivative() override;
  double GetNumericResult(const std::unordered_map<char, double>& variable_to_value) override;
  constants::Expressions GetType() override;
  std::optional<std::unique_ptr<Expression>> Simplify() override;
  bool IsContainVariable() override;
  std::unique_ptr<Expression> Clone() override;

 private:
  std::string GetString() const noexcept;

 private:
  char symbol_;
};

}  // namespace math
