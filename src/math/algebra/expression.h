#pragma once

#include <memory>
#include <string>

class Expression {
 public:
  virtual std::string GetString() = 0;
  virtual std::unique_ptr<Expression> GetDerivative() = 0;
  virtual ~Expression() = default;
  //  virtual double GetNumericResult() = 0; // optional
};
