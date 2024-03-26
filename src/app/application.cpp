#include "app/application.h"

namespace app {

CalculationResult Application::Calculate(std::string infix_expression) {
  // std::string rpn_expression = infrastructure::Converter::ConvertInfixToRPN(infix_expression);
  std::string rpn_expression = infix_expression;

  std::cout << "INFIX: " << infix_expression << std::endl;
  std::cout << "RPN: " << rpn_expression << std::endl;

  CalculationResult result;

  try {
    result.answer = calculator_.Calculate(rpn_expression);
  } catch (std::exception& ex) {
    result.error = ex.what();
  }

  return result;
}

}  // namespace app
