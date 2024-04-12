#include <iostream>

#include "app/application.h"

int main() {
  app::Application app;

  while (true) {
    std::cout << "Enter expression" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    auto result = app.AnalyzeFunction(input);

    if (result.error) {
      std::cout << *result.error << std::endl;
      continue;
    }

    std::cout << result.derivative << std::endl;

    double x;
    std::cout << "Enter x" << std::endl;
    std::cin >> x;

    auto result2 = app.BuildTangent(x);
    if (result2.error) {
      std::cout << *result2.error << std::endl;
      continue;
    }
    std::cout << result2.tangent << std::endl;
  }

  return EXIT_SUCCESS;
}
