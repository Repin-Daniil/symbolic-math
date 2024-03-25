#pragma once

#include <string>

#include "calc/calculator.h"

namespace app {

class Application {
 public:
  double Calculate(std::string infix_expression);  // TODO Возвращай структурку со статусом и ответом

 private:
  calc::Calculator calculator_;
  // TODO класс для работы с алгеброй
};

}  // namespace app
