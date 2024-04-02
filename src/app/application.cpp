#include "app/application.h"

namespace app {

CalculationResult Application::Handle(std::string infix_expression) {
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

}  // namespace app
