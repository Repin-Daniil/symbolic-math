#include <iostream>

#include "app/application.h"

int main() {
  try {
    app::Application app;

    std::cout << "Application start" << std::endl;

    while (true) {
      std::string input;
      std::getline(std::cin, input);

      auto result = app.AnalyzeFunction(input);

      std::cout << result.derivative << std::endl;

      double x;
      std::cin >> x;
      auto result2 = app.BuildTangent(x);

      for (auto coord : result2) {
        std::cout << coord.first << " " << coord.second << std::endl;
      }
    }

    return EXIT_SUCCESS;
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}
