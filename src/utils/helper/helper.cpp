#include "helper.h"

#include <limits>
#include "number.h"

namespace symcpp::utils {

std::optional<double> Helper::ParseOperand(std::string_view input) noexcept {
  if (input == constants::Labels::kPi) {
    return std::numbers::pi;
  } else if (input == constants::Labels::kE) {
    return std::numbers::e;
  } else {
    try {
      return std::stod(input.data(), nullptr);
    } catch (...) {
      return std::nullopt;
    }
  }
}

bool Helper::IsOperandPart(char symbol) noexcept {
  return isdigit(symbol) || isalpha(symbol) || IsDecimalDelimiter(symbol);
}

bool Helper::IsDecimalDelimiter(char symbol) noexcept {
  return symbol == constants::Labels::kDecimalPoint || symbol == constants::Labels::kDecimalComma;
}

bool Helper::IsOperator(std::string_view input) noexcept {
  return constants::char_to_operations.contains(input);
}

std::optional<int> Helper::GetPriority(std::string_view operation) {
  if (auto priority = ParseOperation(operation)) {
    return constants::operations_to_priority.at(*priority);
  }

  return std::nullopt;
}

bool Helper::ComparePriorities(std::string_view lhs, std::string_view rhs) {
  if (lhs == constants::Labels::kExponentiation) {
    return Helper::GetPriority(lhs) > Helper::GetPriority(rhs);
  }

  return Helper::GetPriority(lhs) >= Helper::GetPriority(rhs);
}

std::optional<constants::Operations> Helper::ParseOperation(std::string_view input) noexcept {
  if (!constants::char_to_operations.contains(input)) {
    return std::nullopt;
  }

  return constants::char_to_operations.at(input);
}

bool Helper::IsSign(std::string_view operation) noexcept {
  return operation == constants::Labels::kMinus || operation == constants::Labels::kPlus ||
         operation == constants::Labels::kUnaryMinus;
}

bool Helper::IsUnaryOperation(constants::Operations operation) noexcept {
  return operation == constants::Operations::SIN || operation == constants::Operations::COS ||
         operation == constants::Operations::TANGENT || operation == constants::Operations::NATURAL_LOGARITHM ||
         operation == constants::Operations::UNARY_MINUS || operation == constants::Operations::SQRT;
}

bool Helper::IsBinaryOperation(constants::Operations operation) noexcept {
  return operation == constants::Operations::ADDITION || operation == constants::Operations::SUBTRACTION ||
         operation == constants::Operations::MULTIPLICATION || operation == constants::Operations::DIVISION ||
         operation == constants::Operations::EXPONENTIATION;
}

bool Helper::IsEqual(Number lhs, Number rhs) {
  return std::abs(rhs.GetValue() - lhs.GetValue()) < std::numeric_limits<double>::epsilon();
}

}  // namespace symcpp::utils
