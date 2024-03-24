#include <iostream>

#include "calculator.h"

int main() {
  calc::RPN calc;

  std::string input;
  std::vector<double> results;

  for (int i = 0; i < 5; ++i) {
    std::getline(std::cin, input);
    std::cout << calc.Calculate(input) << std::endl;
    calc.Reset();
  }

  return EXIT_SUCCESS;
}
