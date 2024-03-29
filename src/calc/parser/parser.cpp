#include "parser.h"

namespace calc {

std::optional<double> Parser::ParseOperand(std::string_view input) noexcept {
  if (input == constants::ConstantsLabels::kPi) {
    return std::numbers::pi;
  } else if (input == constants::ConstantsLabels::kE) {
    return std::numbers::e;
  } else {
    try {
      return std::stod(input.begin(), nullptr);
    } catch (...) {
      return std::nullopt;
    }
  }
}

bool Parser::IsOperator(std::string_view input) noexcept {
  return constants::char_to_operations.contains(input);
}

std::optional<constants::Operations> Parser::ParseOperation(std::string_view input) noexcept {
  if (!constants::char_to_operations.contains(input)) {
    return std::nullopt;
  }

  return constants::char_to_operations.at(input);
}

bool Parser::IsUnaryOperation(constants::Operations operation) noexcept {
  return operation == constants::Operations::SINE || operation == constants::Operations::COSINE ||
         operation == constants::Operations::TANGENS || operation == constants::Operations::NATURAL_LOGARITHM ||
         operation == constants::Operations::UNARY_MINUS || operation == constants::Operations::SQRT;
}

bool Parser::IsBinaryOperation(constants::Operations operation) noexcept {
  return operation == constants::Operations::ADDITION || operation == constants::Operations::SUBTRACTION ||
         operation == constants::Operations::MULTIPLICATION || operation == constants::Operations::DIVISION ||
         operation == constants::Operations::EXPONENTIATION;
}

bool Parser::IsFunction(constants::Operations operation) noexcept {
  return operation == constants::Operations::SINE || operation == constants::Operations::COSINE ||
         operation == constants::Operations::TANGENS || operation == constants::Operations::NATURAL_LOGARITHM ||
         operation == constants::Operations::SQRT;
}
}  // namespace calc
