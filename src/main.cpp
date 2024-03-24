#include <iostream>

#include "calculator.h"

int main() {
  calc::RPN calc;

  std::string input;
  std::vector<double> results;

  // for (int i = 0; i < 5; ++i) {
    std::getline(std::cin, input);
    results.push_back(calc.Calculate(input));
    calc.Reset();
  // }

  for (auto& result : results) {
    std::cout << result << std::endl;
  }

  return EXIT_SUCCESS;
}
