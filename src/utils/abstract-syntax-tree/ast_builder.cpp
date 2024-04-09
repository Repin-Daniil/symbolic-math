#include "ast_builder.h"
#include "math/algebra/expressions/operands/number.h"
#include "math/algebra/expressions/operands/variable.h"
#include "math/algebra/expressions/operations/unary/sin.h"
#include "math/algebra/expressions/operations/unary/sqrt.h"
#include "math/algebra/expressions/operations/unary/tangent.h"
#include "math/algebra/expressions/operations/unary/unary_minus.h"

namespace utils {

std::shared_ptr<math::Expression> TreeBuilder::BuildAST(std::string_view rpn_expression) {
  Reset();

  if (rpn_expression.empty()) {
    throw std::invalid_argument(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::istringstream istream{rpn_expression.data()};
  std::string input;

  while (istream >> input) {
    if (utils::Helper::IsOperator(input)) {
      if (nodes_.empty()) {
        throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
      }

      if (auto operation = utils::Helper::ParseOperation(input)) {
        AddOperation(*operation);
      } else {
        throw std::invalid_argument(constants::ExceptionMessage::kWrongFormat.data() + input);
      }
    } else {
      AddOperand(input);
    }
  }

  if (nodes_.size() > 1) {
    throw std::runtime_error("Smth went wrong in ast_builder, stack.size() > 1");
  }

  return nodes_.top();
}

void TreeBuilder::AddOperand(std::string_view token) {
  if (auto operand = utils::Helper::ParseOperand(token)) {
    nodes_.push(std::make_shared<math::Number>(*operand));
  } else if (token.size() == 1) {
    nodes_.push(std::make_shared<math::Variable>(token[0]));
  } else {
    throw std::invalid_argument(constants::ExceptionMessage::kWrongFormat.data());
  }
}

void TreeBuilder::AddOperation(constants::Operations operation) {
  std::shared_ptr<math::Expression> operation_node;

  if (utils::Helper::IsUnaryOperation(operation)) {
    auto arg = GetOperand();

    if (operation == constants::Operations::UNARY_MINUS) {
      operation_node = std::make_shared<math::UnaryMinus>(arg);
    } else if (operation == constants::Operations::SQRT) {
      operation_node = std::make_shared<math::SquareRoot>(arg);
    } else if (operation == constants::Operations::SIN) {
      operation_node = std::make_shared<math::Sin>(arg);
    } else if (operation == constants::Operations::COS) {
      operation_node = std::make_shared<math::Cos>(arg);
    } else if (operation == constants::Operations::TANGENT) {
      operation_node = std::make_shared<math::Tangent>(arg);
    } else if (operation == constants::Operations::NATURAL_LOGARITHM) {
      operation_node = std::make_shared<math::Logarithm>(arg);
    }
  } else if (utils::Helper::IsBinaryOperation(operation)) {
    if (nodes_.size() < 2) {
      // Check unary minus/plus
      if (operation == constants::Operations::SUBTRACTION) {
        operation_node = std::make_shared<math::UnaryMinus>(GetOperand());
      } else if (operation == constants::Operations::ADDITION) {
        operation_node = GetOperand();
      } else {
        throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
      }
    } else {
      auto rhs = GetOperand();
      auto lhs = GetOperand();

      if (operation == constants::Operations::ADDITION) {
        operation_node = std::make_shared<math::Addition>(lhs, rhs);
      } else if (operation == constants::Operations::SUBTRACTION) {
        operation_node = std::make_shared<math::Substraction>(lhs, rhs);
      } else if (operation == constants::Operations::MULTIPLICATION) {
        operation_node = std::make_shared<math::Multiplication>(lhs, rhs);
      } else if (operation == constants::Operations::DIVISION) {
        operation_node = std::make_shared<math::Division>(lhs, rhs);
      } else if (operation == constants::Operations::EXPONENTIATION) {
        operation_node = std::make_shared<math::Exponentiation>(lhs, rhs);
      }
    }
  }

  nodes_.push(operation_node);
}

void TreeBuilder::Reset() {
  std::stack<std::shared_ptr<math::Expression>> empty;
  std::swap(nodes_, empty);
}

std::shared_ptr<math::Expression> TreeBuilder::GetOperand() {
  if (nodes_.empty()) {
    throw std::runtime_error(constants::ExceptionMessage::kNoOperands.data());
  }

  auto operand = nodes_.top();
  nodes_.pop();

  return operand;
}

}  // namespace utils
