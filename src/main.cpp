#include <iostream>

#include "app/application.h"
#include "calc/calculator.h"

int main() {
  try {
    app::Application app;

    while (true) {
      std::string input;
      std::getline(std::cin, input);
      std::cout << app.Calculate(input) << std::endl;
    }

    return EXIT_SUCCESS;
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}
