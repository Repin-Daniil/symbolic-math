#include "ast_builder.h"

#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <utility>

namespace symcpp::utils {

std::unique_ptr<math::TreeNode> TreeBuilder::BuildAST(std::string_view rpn_expression,
                                                      const std::vector<Symbol>& symbols) {
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
      AddOperand(input, symbols);
    }
  }

  return GetOperand();
}

void TreeBuilder::AddOperand(std::string_view token, const std::vector<Symbol>& symbols) {
  if (auto operand = utils::Helper::ParseOperand(token)) {
    nodes_.push(std::make_unique<math::NumberNode>(*operand));
  } else if (token.size() == 1) {
    for (auto& symbol : symbols) {
      if (symbol == Symbol{token[0]}) {
        nodes_.push(std::make_unique<math::Variable>(symbol));
        return;
      }
    }
  } else {
    throw std::invalid_argument(constants::ExceptionMessage::kWrongFormat.data() + std::string(token.data()));
  }
}

void TreeBuilder::AddOperation(constants::Operations operation) {
  std::unique_ptr<math::TreeNode> operation_node;

  if (utils::Helper::IsUnaryOperation(operation)) {
    if (operation == constants::Operations::UNARY_MINUS) {
      operation_node = std::make_unique<math::UnaryMinus>(GetOperand());
    } else if (operation == constants::Operations::SQRT) {
      operation_node = std::make_unique<math::SquareRootNode>(GetOperand());
    } else if (operation == constants::Operations::SIN) {
      operation_node = std::make_unique<math::SinNode>(GetOperand());
    } else if (operation == constants::Operations::COS) {
      operation_node = std::make_unique<math::CosNode>(GetOperand());
    } else if (operation == constants::Operations::TANGENT) {
      operation_node = std::make_unique<math::TangentNode>(GetOperand());
    } else if (operation == constants::Operations::NATURAL_LOGARITHM) {
      operation_node = std::make_unique<math::LogarithmNode>(GetOperand());
    }
  } else if (utils::Helper::IsBinaryOperation(operation)) {
    if (nodes_.size() < 2) {
      // Check unary minus/plus
      if (operation == constants::Operations::SUBTRACTION) {
        operation_node = std::make_unique<math::UnaryMinus>(GetOperand());
      } else if (operation == constants::Operations::ADDITION) {
        operation_node = GetOperand();
      } else {
        throw std::invalid_argument(constants::ExceptionMessage::kNoOperands.data());
      }
    } else {
      auto rhs = GetOperand();
      auto lhs = GetOperand();

      if (operation == constants::Operations::ADDITION) {
        operation_node = std::make_unique<math::Addition>(std::move(lhs), std::move(rhs));
      } else if (operation == constants::Operations::SUBTRACTION) {
        operation_node = std::make_unique<math::Subtraction>(std::move(lhs), std::move(rhs));
      } else if (operation == constants::Operations::MULTIPLICATION) {
        operation_node = std::make_unique<math::Multiplication>(std::move(lhs), std::move(rhs));
      } else if (operation == constants::Operations::DIVISION) {
        operation_node = std::make_unique<math::Division>(std::move(lhs), std::move(rhs));
      } else if (operation == constants::Operations::EXPONENTIATION) {
        operation_node = std::make_unique<math::Exponentiation>(std::move(lhs), std::move(rhs));
      }
    }
  }

  nodes_.push(std::move(operation_node));
}

void TreeBuilder::Reset() {
  std::stack<std::unique_ptr<math::TreeNode>> empty;
  std::swap(nodes_, empty);
}

std::unique_ptr<math::TreeNode> TreeBuilder::GetOperand() {
  if (nodes_.empty()) {
    throw std::runtime_error(constants::ExceptionMessage::kNoOperands.data());
  }

  auto operand = std::move(nodes_.top());
  nodes_.pop();

  return operand;
}

}  // namespace symcpp::utils
