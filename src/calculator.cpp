#include "calculator.h"

namespace calc {

double Calculator::Calculate(std::string_view expression) {
  if (expression.empty()) {
    throw std::invalid_argument(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::istringstream istream{expression.data()};
  std::string input;

  while (istream >> input) {
    if (IsOperator(input)) {
      if (operands_.size() < 2) {
        throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
      }

      if (auto operation = ParseOperation(input)) {
        auto rhs = operands_.top();
        operands_.pop();
        auto lhs = operands_.top();
        operands_.pop();

        operands_.push(CalculateOperation(lhs, rhs, *operation));
      } else {
        throw std::invalid_argument(constants::ExceptionMessage::kWrongFormat.data());
      }
    } else {
      if (auto operand = ParseOperand(input)) {
        operands_.push(*operand);
      } else {
        throw std::invalid_argument(constants::ExceptionMessage::kWrongFormat.data());
      }
    }
  }

  return operands_.top();
}

void Calculator::Reset() {
  std::stack<double> empty;
  std::swap(operands_, empty);
}

double Calculator::CalculateOperation(double lhs, double rhs, constants::Operations operation) {
  double ans = 0;

  if (operation == constants::Operations::ADDITION) {
    ans = lhs + rhs;
  } else if (operation == constants::Operations::SUBTRACTION) {
    ans = lhs - rhs;
  } else if (operation == constants::Operations::MULTIPLICATION) {
    ans = lhs * rhs;
  } else if (operation == constants::Operations::DIVISION) {
    if (std::abs(rhs) < std::numeric_limits<double>::epsilon()) {
      throw std::runtime_error(constants::ExceptionMessage::kZeroDivision.data());
    }

    ans = lhs / rhs;
  }

  return ans;
}

bool Calculator::IsOperator(std::string_view input) noexcept {
  return constants::char_to_operations.contains(input);
}

std::optional<constants::Operations> Calculator::ParseOperation(std::string_view input) noexcept {
  if (!constants::char_to_operations.contains(input)) {
    return std::nullopt;
  }

  return constants::char_to_operations.at(input);
}

std::optional<double> Calculator::ParseOperand(std::string_view input) noexcept {
  try {
    return std::stod(input.begin(), nullptr);
  } catch (...) {
    return std::nullopt;
  }
}

}  // namespace calc
