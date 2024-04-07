#pragma once

#include <memory>
#include <string>

class Expression {
 public:
  virtual std::string GetInfix() = 0;
  virtual std::string GetRPN() = 0;
  virtual std::shared_ptr<Expression> GetDerivative() = 0;
  //  virtual double GetNumericResult() = 0; // optional

  virtual ~Expression() = default;
};
