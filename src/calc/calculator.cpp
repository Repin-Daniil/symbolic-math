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
      if (operands_.empty()) {
        throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
      }

      if (auto operation = ParseOperation(input)) {
        ExecuteOperation(*operation);
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

void Calculator::ExecuteOperation(constants::Operations operation) {
  double ans = 0;

  if (IsUnaryOperation(operation)) {
    auto arg = GetOperand();

    if (operation == constants::Operations::SINE) {
      ans = std::sin(arg);
    } else if (operation == constants::Operations::COSINE) {
      ans = std::cos(arg);
    } else if (operation == constants::Operations::NATURAL_LOGARITHM) {
      if (IsEqual(arg, 0)) {
        throw std::runtime_error(constants::ExceptionMessage::kZeroLogarithm.data());
      }

      ans = std::log(arg);
    }
  } else {
    if (operands_.size() < 2) {
      throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
    }

    auto rhs = GetOperand();
    auto lhs = GetOperand();

    if (operation == constants::Operations::ADDITION) {
      ans = lhs + rhs;
    } else if (operation == constants::Operations::SUBTRACTION) {
      ans = lhs - rhs;
    } else if (operation == constants::Operations::MULTIPLICATION) {
      ans = lhs * rhs;
    } else if (operation == constants::Operations::DIVISION) {
      if (IsEqual(rhs, 0)) {
        throw std::runtime_error(constants::ExceptionMessage::kZeroDivision.data());
      }

      ans = lhs / rhs;
    } else if (operation == constants::Operations::EXPONENTIATION) {
      ans = std::pow(lhs, rhs);  // FIXME Тщательно протестировать, в степени может быть тоже выражение
    }
  }

  operands_.push(ans);
}

double Calculator::GetOperand() {
  if (operands_.empty()) {
    throw std::runtime_error(constants::ExceptionMessage::kNoOperands.data());
  }

  double operand = operands_.top();
  operands_.pop();

  return operand;
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

bool Calculator::IsUnaryOperation(constants::Operations operation) noexcept {
  return operation == constants::Operations::SINE || operation == constants::Operations::COSINE ||
         operation == constants::Operations::NATURAL_LOGARITHM;
}

bool Calculator::IsEqual(double lhs, double rhs) {
  return std::abs(rhs - lhs) < std::numeric_limits<double>::epsilon();
}

std::optional<double> Calculator::ParseOperand(std::string_view input) noexcept {
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

}  // namespace calc
