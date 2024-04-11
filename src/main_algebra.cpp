#include <iostream>

#include "app/application.h"

int main() {
  try {
    app::Application app;

    std::cout << "Enter expression" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    auto result = app.AnalyzeFunction(input);

    std::cout << result.derivative << std::endl;

    std::cout << "Function left border is " << result.graph[0].first << " Function right border is "
              << result.graph[result.graph.size() - 1].first << std::endl;

    double x;
    std::cout << "Enter x" << std::endl;
    std::cin >> x;
    auto result2 = app.BuildTangent(x);
    std::cout << result2.tangent << std::endl;
    std::cout << "Tangent left border is " << result2.graph[0].first << " Tangent right border is "
              << result2.graph[result2.graph.size() - 1].first << std::endl;

    std::cout << "Complete" << std::endl;

    return EXIT_SUCCESS;
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}
