#pragma once

#include <memory>
#include <string>

namespace math {

class Expression {
 public:
  virtual std::string GetInfix(int previous_priority) = 0;
  virtual std::string GetRPN() = 0;
  virtual std::shared_ptr<Expression> GetDerivative() = 0;
  //  virtual double GetNumericResult() = 0;

  virtual ~Expression() = default;
};

}  // namespace math
