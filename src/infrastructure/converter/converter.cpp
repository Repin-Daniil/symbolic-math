#include "converter.h"

#include <iostream>

namespace infrastructure {

using namespace std::literals;

/* for (size_t i = 0; i < infix_expression.size(); ++i) {
    char ch = infix_expression[i];
    std::string_view ch_sv(&ch);

    if (isdigit(ch) || isalpha(ch)) {
      postfix << ch;

      // Check for the end of a number or variable name to insert a space
      if (i + 1 < infix_expression.size() && !isdigit(infix_expression[i + 1]) && !isalpha(infix_expression[i + 1])) {
        postfix << ' ';
      }
    } else if (ch == '(') {
      operators.push(ch);
    } else if (ch == ')') {
      while (!operators.empty() && operators.top() != '(') {
        postfix << operators.top();
        operators.pop();
      }

      operators.pop();
    } else if (calc::Parser::IsOperator(ch_sv)) {
      std::cout << "Find operator" << std::endl;
      while (!operators.empty() && GetPriority(operators.top()) >= GetPriority(ch)) {
        postfix << operators.top();
        operators.pop();
      }
      operators.push(ch);
    } else if (calc::Parser::IsUnaryOperation(*calc::Parser::ParseOperation(ch_sv))) { //FIXME нормальную обработку nlpt
      while (!operators.empty() && GetPriority(operators.top()) >= 1) {
        postfix << operators.top();
        operators.pop();
      }
      operators.push(ch);
    }
  }

  while (!operators.empty()) {
    postfix << operators.top();
    operators.pop();
  }
 */

std::string Converter::ConvertInfixToRPN(std::string_view infix_expression) {
  std::stack<std::string_view> operators;
  std::stringstream postfix;

  // TODO Унарный минус

  for (size_t i = 0; i < infix_expression.size(); ++i) {
    const char& symbol = infix_expression[i];

    if (isdigit(symbol)) {  // TODO потом или x
      postfix << symbol;

      if (IsEndOfOperand(i, infix_expression)) {
        postfix << ' ';
      }
    } else if (IsPrefixFunction(i, infix_expression)) {
      operators.push(*ParseFunction(i, infix_expression));
    } else if (symbol == '(') {
      operators.push(infix_expression.substr(i, 1));
    } else if (symbol == ')') {
      while (!operators.empty() && operators.top() != "("sv) {
        postfix << operators.top() << " ";
        operators.pop();
      }

      operators.pop();
    } else if (IsOperator(i, infix_expression)) {
      while (!operators.empty() && operators.top() != "("sv && (GetPriority(operators.top()) >= GetPriority(infix_expression.substr(i, 1)) ||
             IsPrefixFunction(i, infix_expression))) {
        postfix << operators.top() << " ";
        operators.pop();
      }

      operators.emplace(infix_expression.substr(i, 1));
    }
  }

  while (!operators.empty()) {
    if (operators.top() == "("sv || operators.top() == ")"sv) {
      // TODO throw несогласованная скобочная последовательность
    }

    postfix << operators.top();
    operators.pop();
  }

  return postfix.str();
}

int Converter::GetPriority(std::string_view operation) {
  if (auto priority = calc::Parser::ParseOperation(operation)) {
    return constants::operations_to_priority.at(*priority);
  }

  throw std::runtime_error(constants::ExceptionMessage::kWrongFormat.data());
}

bool Converter::IsPrefixFunction(size_t i, std::string_view infix_expression) {
  return ParseFunction(i, infix_expression).has_value();
}

std::optional<std::string_view> Converter::ParseFunction(size_t i, std::string_view infix_expression) {
  if (infix_expression[i] == 's') {
    if (i + 2 < infix_expression.size() && infix_expression.substr(i, 3) == "sin"sv) {
      return infix_expression.substr(i, 3);
    }
    if (i + 3 < infix_expression.size() && infix_expression.substr(i, 4) == "sqrt"sv) {
      return infix_expression.substr(i, 4);
    }
  } else if (infix_expression[i] == 'c') {
    if (i + 2 < infix_expression.size() && infix_expression.substr(i, 3) == "cos"sv) {
      return infix_expression.substr(i, 3);
    }
  } else if (infix_expression[i] == 'l') {
    if (i + 1 < infix_expression.size() && infix_expression.substr(i, 2) == "ln"sv) {
      return infix_expression.substr(i, 2);
    }
  } else if (infix_expression[i] == 't') {
    if (i + 1 < infix_expression.size() && infix_expression.substr(i, 2) == "tg"sv) {
      return infix_expression.substr(i, 2);
    }
    if (i + 2 < infix_expression.size() && infix_expression.substr(i, 3) == "tan"sv) {
      return infix_expression.substr(i, 3);
    }
  }
  else if (infix_expression.substr(i, 1) == "√"sv) {
    return infix_expression.substr(i, 1);
  }

  return std::nullopt;
}

bool Converter::IsOperator(size_t i, std::string_view infix_expression) {
  return calc::Parser::IsOperator(infix_expression.substr(i, 1));
}

bool Converter::IsEndOfOperand(size_t i, std::string_view infix_expression) {
  return (i + 1 == infix_expression.size()) || (i + 1 < infix_expression.size() && !isdigit(infix_expression[i + 1]));
}

// TODO Вынести многое из конвертера в парсер

}  // namespace infrastructure
