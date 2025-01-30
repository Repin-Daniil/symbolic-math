#include "logarithm.h"

#include <algorithm>
#include <limits>
#include <memory>
#include <string>
#include <utility>

namespace symcpp::math {

std::string LogarithmNode::GetLatex(int previous_priority) {
  std::stringstream stream;
  stream << constants::Labels::kLatexSlash << constants::Labels::kLogarithm << constants::Labels::kLatexOpenParen
         << argument_->GetLatex(0) << constants::Labels::kLatexEndParen;
  return stream.str();
}

std::string LogarithmNode::GetInfix(int previous_priority) {
  std::stringstream stream;
  stream << constants::Labels::kLogarithm << constants::Labels::kOpenParen << argument_->GetInfix(0)
         << constants::Labels::kEndParen;
  return stream.str();
}

std::string LogarithmNode::GetRPN() {
  std::stringstream stream;
  stream << argument_->GetRPN() << " " << constants::Labels::kLogarithm;
  return stream.str();
}

std::unique_ptr<TreeNode> LogarithmNode::GetDerivative(const Symbol& d) {
  return std::make_unique<Division>(argument_->GetDerivative(d), argument_->Clone());
}

constants::Expressions LogarithmNode::GetType() {
  return constants::Expressions::LOGARITHM;
}

std::unique_ptr<TreeNode> LogarithmNode::Simplify() {
  if (auto simplified = argument_->Simplify()) {
    argument_ = std::move(simplified);
  }

  if ((argument_->GetType() == constants::Expressions::NUMBER &&
       utils::Helper::IsEqual(*GetNumber(argument_), std::numbers::e)) ||
      (argument_->GetType() == constants::Expressions::CONSTANT && argument_->IsContainVariable('e'))) {
    return std::make_unique<NumberNode>(1);
  }

  return nullptr;
}

std::unique_ptr<TreeNode> LogarithmNode::Clone() {
  return std::make_unique<LogarithmNode>(argument_->Clone());
}

std::unique_ptr<TreeNode> LogarithmNode::Evaluate() {
  auto arg_result = argument_->Evaluate();

  if (auto result = GetNumber(arg_result)) {
    // TODO Заменить std::abs на свой Abs
    if (*result < 0 || std::abs(result->GetValue() - 0) < std::numeric_limits<double>::epsilon()) {
      throw std::runtime_error(constants::ExceptionMessage::kWrongLogarithm.data());
    }

    return std::make_unique<NumberNode>(std::log(result->GetValue()));
  }

  return std::make_unique<LogarithmNode>(std::move(arg_result));
}

}  // namespace symcpp::math
