#include <iostream>
#include "symcpp/symcpp.h"

/**
 * @brief Example of interactive calculations
 */
int main() {
  using namespace symcpp;
  std::string symbol;
  std::cout << "Enter variable symbol: ";
  std::cin >> symbol;

  Symbol var(symbol);

  std::cout << "Enter expression: ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string expr_str;
  std::getline(std::cin, expr_str);
  Expression exp(expr_str, {var});

  std::cout << "Simplified: " << exp << std::endl;
  std::cout << "RPN: " << RPN(exp) << std::endl;
  std::cout << "f`(x) = " << Diff(exp, var) << std::endl;

  std::cout << "Enter x: " << std::endl;
  std::cin >> var;

  std::cout << "f(" << var << ") = " << Evaluate(exp) << std::endl;

  return EXIT_SUCCESS;
}
