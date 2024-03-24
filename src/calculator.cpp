#include "calculator.h"

namespace calc {

double RPN::Calculate(std::string_view expression) {
  std::stringstream buffer;
  bool operand_in_buff = false;

  for (auto& symbol : expression) {
    if (IsOperator(symbol)) {
      operand_in_buff = false;

      if (operands_.size() < 2) {
        throw std::invalid_argument("No operands entered");
      }

      auto rhs = operands_.top();
      operands_.pop();
      auto lhs = operands_.top();
      operands_.pop();

      operands_.push(CalculateOperation(lhs, rhs, symbol));
    } else if (IsDelimeter(symbol)) {
      if (operand_in_buff) {
        auto operand = ParseOperand(buffer.view());

        if (operand) {
          operands_.push(*operand);
        } else {
          throw std::invalid_argument("Wrong operand or operator format");
        }
      }

      buffer.str(std::string());
    } else {
      operand_in_buff = true;
      buffer << symbol;
    }
  }

  return operands_.top();
}

void RPN::Reset() {
  std::stack<double> empty;
  std::swap(operands_, empty);
}

double RPN::CalculateOperation(double lhs, double rhs, char op) {
  if (!constants::char_to_operations.contains(op)) {
    throw std::invalid_argument("Unknown operation");
  }

  auto operation = constants::char_to_operations.at(op);
  double ans = 0;

  if (operation == constants::Operations::ADDITION) {
    ans = lhs + rhs;
  } else if (operation == constants::Operations::SUBTRACTION) {
    ans = lhs - rhs;
  } else if (operation == constants::Operations::MULTIPLICATION) {
    ans = lhs * rhs;
  } else if (operation == constants::Operations::DIVISION) {
    if (std::abs(rhs) < std::numeric_limits<double>::epsilon()) {
      throw std::runtime_error("Zero division");
    }

    ans = lhs / rhs;
  }

  return ans;
}

bool RPN::IsDelimeter(char symbol) noexcept {
  return symbol == constants::kDelimeter;
}

bool RPN::IsOperator(char input) noexcept {
  return constants::char_to_operations.contains(input);
}

std::optional<double> RPN::ParseOperand(std::string_view input) {
  double operand = 0.0;

  try {
    operand = std::stod(input.begin(), nullptr);
  } catch (...) {
    return std::nullopt;
  }

  return operand;
}

}  // namespace calc
