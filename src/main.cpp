#include <iostream>

#include "calculator.h"

int main() {
  calc::Calculator calc;

  std::string input;

  try {
    for (int i = 0; i < 5; ++i) {
      std::getline(std::cin, input);
      std::cout << calc.Calculate(input) << std::endl;
      calc.Reset();
    }

    return EXIT_SUCCESS;
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}
