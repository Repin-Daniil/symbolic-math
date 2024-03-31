#include "converter.h"

namespace utils {

using namespace std::literals;

std::string Converter::ConvertInfixToRPN(std::string_view infix_expression) {
  std::stack<std::string_view> operators;
  std::stringstream postfix;

  for (size_t i = 0; i < infix_expression.size(); ++i) {
    const char& symbol = infix_expression[i];

    if (IsPrefixFunction(i, infix_expression)) {
      auto operation = *ParseFunction(i, infix_expression);
      operators.push(operation);
      i += operation.size() - 1;
    } else if (isdigit(symbol) || symbol == constants::Labels::kDecimalPoint ||
               symbol == constants::Labels::kDecimalComma || isalpha(symbol)) {
      postfix << (symbol == constants::Labels::kDecimalComma ? constants::Labels::kDecimalPoint : symbol);

      if (IsEndOfOperand(i, infix_expression) || IsEndOfConstant(i, infix_expression)) {
        postfix << ' ';
      }
    } else if (symbol == constants::Labels::kOpenParenChar) {
      operators.push(infix_expression.substr(i, 1));
    } else if (symbol == constants::Labels::kEndParenChar) {
      while (!operators.empty() && operators.top() != constants::Labels::kOpenParen) {
        postfix << operators.top() << " ";
        operators.pop();
      }

      if (operators.empty()) {
        throw std::runtime_error(constants::ExceptionMessage::kUnbalancedBracket.data());
      }

      operators.pop();
    } else if (Helper::IsOperator(infix_expression.substr(i, 1))) {
      if (IsUnary(i, infix_expression)) {
        if (infix_expression.substr(i, 1) == constants::Labels::kMinus) {
          operators.emplace(constants::Labels::kUnaryMinus);
        }
      } else {
        while (!operators.empty() && operators.top() != constants::Labels::kOpenParen &&
               (Helper::GetPriority(operators.top()) >= Helper::GetPriority(infix_expression.substr(i, 1)) ||
                IsPrefixFunction(i, infix_expression))) {
          postfix << operators.top() << " ";
          operators.pop();
        }

        operators.emplace(infix_expression.substr(i, 1));
      }
    }
  }

  while (!operators.empty()) {
    if (operators.top() == constants::Labels::kOpenParen || operators.top() == constants::Labels::kEndParen) {
      throw std::runtime_error(constants::ExceptionMessage::kUnbalancedBracket.data());
    }

    postfix << operators.top() << " ";
    operators.pop();
  }

  return postfix.str();
}

bool Converter::IsPrefixFunction(size_t i, std::string_view infix_expression) {
  return ParseFunction(i, infix_expression).has_value();
}

std::optional<std::string_view> Converter::ParseFunction(size_t i, std::string_view infix_expression) {
  if (infix_expression[i] == 's') {
    if (i + 2 < infix_expression.size() && infix_expression.substr(i, 3) == constants::Labels::kSin) {
      return infix_expression.substr(i, 3);
    }
    if (i + 3 < infix_expression.size() && infix_expression.substr(i, 4) == constants::Labels::kSquareRoot) {
      return infix_expression.substr(i, 4);
    }
  } else if (infix_expression[i] == 'c') {
    if (i + 2 < infix_expression.size() && infix_expression.substr(i, 3) == constants::Labels::kCos) {
      return infix_expression.substr(i, 3);
    }
  } else if (infix_expression[i] == 'l') {
    if (i + 1 < infix_expression.size() && infix_expression.substr(i, 2) == constants::Labels::kLogarithm) {
      return infix_expression.substr(i, 2);
    }
  } else if (infix_expression[i] == 't') {
    if (i + 1 < infix_expression.size() && infix_expression.substr(i, 2) == constants::Labels::kTg) {
      return infix_expression.substr(i, 2);
    }
    if (i + 2 < infix_expression.size() && infix_expression.substr(i, 3) == constants::Labels::kTan) {
      return infix_expression.substr(i, 3);
    }
  }

  return std::nullopt;
}

bool Converter::IsEndOfOperand(size_t i, std::string_view infix_expression) {
  return (isdigit(infix_expression[i]) || infix_expression[i] == constants::Labels::kDecimalComma ||
          infix_expression[i] == constants::Labels::kDecimalPoint) &&
         ((i + 1 == infix_expression.size()) || (i + 1 < infix_expression.size() && !isdigit(infix_expression[i + 1]) &&
                                                 infix_expression[i + 1] != constants::Labels::kDecimalPoint &&
                                                 infix_expression[i + 1] != constants::Labels::kDecimalComma));
}

bool Converter::IsUnary(size_t i, std::string_view infix_expression) {
  int j = i - 1;

  while (j >= 0 && infix_expression[j] == ' ') {
    --j;
  }

  return (infix_expression.substr(i, 1) == constants::Labels::kMinus ||
          infix_expression.substr(i, 1) == constants::Labels::kPlus ||
          infix_expression.substr(i, 1) == constants::Labels::kUnaryMinus) &&
         (infix_expression[i - 1] == constants::Labels::kOpenParenChar ||
          (j >= 0 && Helper::IsOperator(infix_expression.substr(j, 1))));
}

bool Converter::IsEndOfConstant(size_t i, std::string_view infix_expression) {
  return isalpha(infix_expression[i]) &&
         ((i + 1 == infix_expression.size()) || (i + 1 < infix_expression.size() && !isalpha(infix_expression[i + 1])));
}

}  // namespace utils
