#include "app/application.h"

namespace app {

CalculationResult Application::Calculate(std::string infix_expression) {
  if (infix_expression == "Reset") {
    calculator_.Reset();

    return {};
  }

  CalculationResult result;

  try {
    std::string rpn_expression = utils::Converter::ConvertInfixToRPN(infix_expression);

    std::cout << "INFIX: " << infix_expression << std::endl;
    std::cout << "RPN:   " << rpn_expression << std::endl;

    result.answer = calculator_.Calculate(rpn_expression);
  } catch (std::exception& ex) {
    result.error = ex.what();
    calculator_.Reset();
  }

  return result;
}

FunctionAnalysis Application::AnalyzeFunction(std::string infix_expression) {
  FunctionAnalysis result;

  try {
    std::string rpn_expression = utils::Converter::ConvertInfixToRPN(infix_expression);

    algebra_.AddFunction(std::move(rpn_expression));
    result.derivative = algebra_.GetDerivative();
    result.graph = algebra_.GetFunctionGraph();
  } catch (std::exception& ex) {
    result.error = ex.what();
    algebra_.Reset();
  }

  return result;
}

TangentBuildingResult Application::BuildTangent(double x) {
  TangentBuildingResult result;
  result.tangent = algebra_.GetTangent(x);
  result.graph = algebra_.GetTangentGraph(x);

  return result;
}

void Application::Reset() {
  algebra_.Reset();
}

}  // namespace app
