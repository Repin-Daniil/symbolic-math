#include "converter.h"

#include <iostream>

namespace infrastructure {

using namespace std::literals;

std::string Converter::ConvertInfixToRPN(std::string_view infix_expression) {
  std::stack<std::string_view> operators;
  std::stringstream postfix;

  for (size_t i = 0; i < infix_expression.size(); ++i) {
    const char &symbol = infix_expression[i];

    if (IsPrefixFunction(i, infix_expression)) {
      auto operation = *ParseFunction(i, infix_expression);
      operators.push(operation);
      i += operation.size() - 1;
    } else if (isdigit(symbol) || symbol == '.' || symbol == ',' || isalpha(symbol)) {
      postfix << (symbol == ',' ? '.' : symbol);

      if (IsEndOfOperand(i, infix_expression) || IsEndOfConstant(i, infix_expression)) {
        postfix << ' ';
      }
    } else if (symbol == '(') {
      operators.push(infix_expression.substr(i, 1));
    } else if (symbol == ')') {
      while (!operators.empty() && operators.top() != "("sv) {
        postfix << operators.top() << " ";
        operators.pop();
      }

      if (operators.empty()) {
        throw std::runtime_error(constants::ExceptionMessage::kUnbalancedBracket.data());
      }

      operators.pop();
    } else if (IsOperator(i, infix_expression)) {
      if (IsUnary(i, infix_expression)) {
        if (infix_expression[i] == '-') operators.emplace("~"sv);
      } else {
        while (!operators.empty() && operators.top() != "("sv &&
            (GetPriority(operators.top()) >= GetPriority(infix_expression.substr(i, 1)) ||
                IsPrefixFunction(i, infix_expression))) {
          postfix << operators.top() << " ";
          operators.pop();
        }

        operators.emplace(infix_expression.substr(i, 1));
      }
    }
  }

  while (!operators.empty()) {
    if (operators.top() == "("sv || operators.top() == ")"sv) {
      throw std::runtime_error(constants::ExceptionMessage::kUnbalancedBracket.data());
    }

    postfix << operators.top() << " ";
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

  return std::nullopt;
}

bool Converter::IsOperator(size_t i, std::string_view infix_expression) {
  return calc::Parser::IsOperator(infix_expression.substr(i, 1));
}

bool Converter::IsEndOfOperand(size_t i, std::string_view infix_expression) {
  return (isdigit(infix_expression[i]) || infix_expression[i] == ',' || infix_expression[i] == '.') &&
      ((i + 1 == infix_expression.size()) || (i + 1 < infix_expression.size() && !isdigit(infix_expression[i + 1]) &&
          infix_expression[i + 1] != '.' && infix_expression[i + 1] != ','));
}

bool Converter::IsUnary(size_t i, std::string_view infix_expression) {
  size_t j = i - 1;

  while (j >= 0 && infix_expression[j] == ' ') {
    --j;
  }

  return (infix_expression[i] == '-' || infix_expression[i] == '+') &&
      (i == 0 || infix_expression[i - 1] == '(' || IsOperator(j, infix_expression));
}

bool Converter::IsEndOfConstant(size_t i, std::string_view infix_expression) {
  return isalpha(infix_expression[i]) &&
      ((i + 1 == infix_expression.size()) || (i + 1 < infix_expression.size() && !isalpha(infix_expression[i + 1])));
}

// TODO Вынести многое из конвертера в парсер

}  // namespace infrastructure
