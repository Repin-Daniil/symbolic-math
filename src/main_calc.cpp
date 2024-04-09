#include <iostream>

#include "app/application.h"

int main() {
  try {
    app::Application app;

    std::cout << "Application start" << std::endl;

    while (true) {
      std::string input;
      std::getline(std::cin, input);

      auto result = app.Calculate(input);

      std::cout << (!result.error ? std::to_string(result.answer) : *result.error) << std::endl;
    }

    return EXIT_SUCCESS;
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}
