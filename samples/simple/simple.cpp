#include <iostream>
#include "symcpp.h"

/**
 * @brief Example from README.md
 */
int main() {
  using namespace symcpp;

  Symbol x('x'), y('y');
  Number num = 17;

  Expression exp("x + ln(y^2)", {x, y});
  std::cout << "exp = " << exp << std::endl;

  exp = Pow(x, 2) * 13 + Sin(pi * y);
  std::cout << "exp = " << exp << std::endl;
  x = 3;
  std::cout << "exp = " << exp << std::endl;
  y = num / 2;
  std::cout << "exp = " << exp << std::endl;

  Number result = exp;
  std::cout << "result = " << result << std::endl;

  x.Reset();
  std::cout << "exp = " << exp << std::endl;
  std::cout << "exp = " << Infix(exp) << std::endl;
  y.Reset();
  std::cout << "exp = " << exp << std::endl;

  auto derivative_of_func_x = Diff(exp, x);
  std::cout << "f`x(x,y) = " << derivative_of_func_x << std::endl;

  auto derivative_of_func_y = Diff(exp, y);
  std::cout << "f`y(x,y) = " << derivative_of_func_y << std::endl;

  Number result_2 = Evaluate(Log(exp), {{x, 14}, {y, 17}});
  std::cout << "result_2 = " << result_2 << std::endl;

  std::cout << "RPN = " << RPN(exp + Log(Pow(x, y))) << std::endl;
}
