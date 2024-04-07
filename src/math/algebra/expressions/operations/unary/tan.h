#pragma once

#include <memory>
#include <string>
#include <utility>
#include "cos.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operations/binary/division.h"
#include "math/algebra/expressions/operations/binary/exponentiation.h"
#include "math/algebra/expressions/operations/binary/multiplication.h"
#include "math/algebra/expressions/operations/unary_operation.h"

namespace math {

class Tan final : public UnaryOperation {
 public:
  explicit Tan(std::shared_ptr<Expression> argument) : UnaryOperation(std::move(argument)) {
  }

  std::string GetInfix() override;
  std::string GetRPN() override;
  std::shared_ptr<Expression> GetDerivative() override;
};

}  // namespace math