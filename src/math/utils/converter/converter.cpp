#include "converter.h"

namespace utils {

std::string Converter::ConvertInfixToRPN(std::string_view infix_expression) {
  std::stack<std::string_view> operators;
  std::stringstream postfix;

  for (std::size_t i = 0; i < infix_expression.size(); ++i) {
    const char& symbol = infix_expression[i];

    if (IsPrefixFunction(i, infix_expression)) {
      auto operation = *ParseFunction(i, infix_expression);
      operators.push(operation);
      i += operation.size() - 1;
    } else if (Helper::IsOperandPart(symbol)) {
      postfix << (symbol == constants::Labels::kDecimalComma ? constants::Labels::kDecimalPoint : symbol);

      if (IsEndOfOperand(i, infix_expression)) {
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
               (Helper::ComparePriorities(operators.top(), infix_expression.substr(i, 1)) ||
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

bool Converter::IsPrefixFunction(std::size_t i, std::string_view infix_expression) {
  return ParseFunction(i, infix_expression).has_value();
}

std::optional<std::string_view> Converter::ParseFunction(std::size_t i, std::string_view infix_expression) {
  if (IsEqual(i, infix_expression, constants::Labels::kSin)) {
    return infix_expression.substr(i, constants::Labels::kSin.size());
  }

  if (IsEqual(i, infix_expression, constants::Labels::kSquareRoot)) {
    return infix_expression.substr(i, constants::Labels::kSquareRoot.size());
  }

  if (IsEqual(i, infix_expression, constants::Labels::kCos)) {
    return infix_expression.substr(i, constants::Labels::kCos.size());
  }

  if (IsEqual(i, infix_expression, constants::Labels::kLogarithm)) {
    return infix_expression.substr(i, constants::Labels::kLogarithm.size());
  }

  if (IsEqual(i, infix_expression, constants::Labels::kTg)) {
    return infix_expression.substr(i, constants::Labels::kTg.size());
  }

  if (IsEqual(i, infix_expression, constants::Labels::kTan)) {
    return infix_expression.substr(i, constants::Labels::kTan.size());
  }

  return std::nullopt;
}

bool Converter::IsEndOfOperand(std::size_t i, std::string_view infix_expression) {
  return Helper::IsOperandPart(infix_expression[i]) &&
         (i + 1 == infix_expression.size() ||
          (i + 1 < infix_expression.size() && !Helper::IsOperandPart(infix_expression[i + 1])));
}

bool Converter::IsUnary(std::size_t i, std::string_view infix_expression) {
  int j = i - 1;

  while (j >= 0 && infix_expression[j] == ' ') {
    --j;
  }

  return Helper::IsSign(infix_expression.substr(i, 1)) &&
         (j >= 0 && (infix_expression[j] == constants::Labels::kOpenParenChar ||
                     Helper::IsOperator(infix_expression.substr(j, 1))));
}

bool Converter::IsEqual(std::size_t i, std::string_view infix_expression, std::string_view candidate) {
  return (i + candidate.size() - 1) < infix_expression.size() &&
         infix_expression.substr(i, candidate.size()) == candidate;
}

}  // namespace utils
