#pragma once

#include <iostream>
#include <string>

#include "calc/calculator.h"

namespace app {

struct CalculationResult {
  std::optional<double> answer;
  std::string error;
};

class Application {
 public:
  CalculationResult Handle(std::string infix_expression);

 private:
  utils::Calculator calculator_;
  // TODO класс для работы с алгеброй
};

}  // namespace app
