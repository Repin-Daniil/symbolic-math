#include "app/application.h"

namespace app {

double Application::Calculate(std::string infix_expression) {
  // std::string rpn_expression = infrastructure::Converter::ConvertInfixToRPN(infix_expression);
  std::string rpn_expression = infix_expression;

  // std::cout << "INFIX: " << infix_expression << std::endl;
  // std::cout << "RPN: " << rpn_expression << std::endl;

  return calculator_.Calculate(rpn_expression);
}

}  // namespace app
