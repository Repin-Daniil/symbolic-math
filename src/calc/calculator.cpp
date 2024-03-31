#include "calculator.h"

namespace utils {

double Calculator::Calculate(std::string_view expression) {
  if (expression.empty()) {
    throw std::invalid_argument(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::istringstream istream{expression.data()};
  std::string input;

  while (istream >> input) {
    if (Helper::IsOperator(input)) {
      if (operands_.empty()) {
        throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
      }

      if (auto operation = Helper::ParseOperation(input)) {
        ExecuteOperation(*operation);
      } else {
        throw std::invalid_argument(constants::ExceptionMessage::kWrongFormat.data());
      }
    } else {
      if (auto operand = Helper::ParseOperand(input)) {
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

  if (Helper::IsUnaryOperation(operation)) {
    auto arg = GetOperand();

    if (operation == constants::Operations::UNARY_MINUS) {
      ans = -1 * arg;
    } else if (operation == constants::Operations::SQRT) {
      if (arg < 0) {
        throw std::runtime_error(constants::ExceptionMessage::kNegativeRoot.data());
      }

      ans = std::sqrt(arg);
    } else if (operation == constants::Operations::SIN) {
      ans = std::sin(arg);
    } else if (operation == constants::Operations::COS) {
      ans = std::cos(arg);
    } else if (operation == constants::Operations::TANGENT) {
      if (IsEqual(std::fmod(arg, std::numbers::pi), std::numbers::pi / 2.0)) {
        throw std::runtime_error(constants::ExceptionMessage::kWrongTangent.data());
      }

      ans = std::tan(arg);
    } else if (operation == constants::Operations::NATURAL_LOGARITHM) {
      if (IsEqual(arg, 0)) {
        throw std::runtime_error(constants::ExceptionMessage::kZeroLogarithm.data());
      }

      ans = std::log(arg);
    }
  } else {
    if (operands_.size() < 2) {
      // Check unary minus/plus
      if (operation == constants::Operations::SUBTRACTION) {
        ans = -1 * GetOperand();
      } else if (operation == constants::Operations::ADDITION) {
        ans = GetOperand();
      } else {
        throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
      }
    } else {
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
        ans = std::pow(lhs, rhs);
      }
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

bool Calculator::IsEqual(double lhs, double rhs) {
  return std::abs(rhs - lhs) < std::numeric_limits<double>::epsilon();
}

}  // namespace utils
