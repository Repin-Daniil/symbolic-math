#include <iostream>
#include "symcpp.h"

/**
 * @brief Example. Tangent builder
 * @input x coordinate
 */
int main() {
  using namespace symcpp;

  Symbol x('x');

  auto func = 12 * Sin(Log(x) * x) - Pow(x, Tan(x));
  std::cout << "f(x) = " << func << std::endl;

  auto derivative = Diff(func, x);
  std::cout << "f`(x) = " << derivative << std::endl;

  while (true) {
    int input;
    std::cout << "Enter x: ";
    std::cin >> input;

    x = input;

    auto y = Evaluate(func);
    std::cout << "f(" << x << ") = " << y << std::endl;

    auto k = Evaluate(derivative);
    auto b = Evaluate(y - k * x);

    auto tangent = k * x + b;
    x.Reset();

    std::cout << "Tangent: g(x) = " << tangent << std::endl;

    std::cout << std::endl;
  }
}
