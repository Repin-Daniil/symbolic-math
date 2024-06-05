#include "expression.h"
#include "symcpp/utils/parser/ast_builder.h"

namespace symcpp {

Expression::Expression(std::unique_ptr<math::TreeNode> tree) : root_(std::move(tree)) {
  //  std::cout << "Get Root! " << std::endl;
  Simplify();
}

Expression::Expression(std::string infix_expression, const std::vector<Symbol>& symbols) {
  root_ = utils::TreeBuilder::BuildAST(utils::Converter::ConvertInfixToRPN(std::move(infix_expression)), symbols);
  Simplify();
}

Expression::Expression(const Number& number) : root_(std::make_unique<math::NumberNode>(number)) {
}

Expression::Expression(double number) : root_(std::make_unique<math::NumberNode>(number)) {
}

Expression::Expression(const Symbol& symbol) : root_(std::make_unique<math::Constant>(symbol)) {
}

Expression::Expression(Symbol& symbol) : root_(std::make_unique<math::Variable>(symbol)) {
}

Expression::Expression(Expression&& other) noexcept : root_(std::move(other.root_)) {
  //  std::cout << "Move Expression!" << std::endl;
  Simplify();
}

Expression::Expression(const Expression& other) : root_((other.root_ ? other.root_->Clone() : nullptr)) {
  //  std::cout << "Clone Expression!" << std::endl;
  Simplify();
}

std::unique_ptr<math::TreeNode> Expression::Release() {
  return std::move(root_);
}

std::string Expression::GetInfix() const {
  if (root_) {
    return root_->GetInfix(0);
  }

  return {};
}

std::string Expression::GetLatex() const {
  if (root_) {
    return root_->GetLatex(0);
  }

  return {};
}

std::string Expression::GetRPN() const {
  if (root_) {
    return root_->GetRPN();
  }

  return {};
}

Expression& Expression::operator=(Expression other) {
  auto other_ptr = other.Release();

  if (!other_ptr) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  root_ = std::move(other_ptr);
  return *this;
}

Expression& Expression::operator+=(Expression other) {
  auto other_ptr = other.Release();

  if (!root_ || !other_ptr) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  root_ = std::make_unique<math::Addition>(std::move(root_), std::move(other_ptr));
  Simplify();

  return *this;
}

Expression& Expression::operator/=(Expression other) {
  auto other_ptr = other.Release();

  if (!root_ || !other_ptr) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  root_ = std::make_unique<math::Division>(std::move(root_), std::move(other_ptr));
  Simplify();

  return *this;
}

Expression& Expression::operator*=(Expression other) {
  auto other_ptr = other.Release();

  if (!root_ || !other_ptr) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  root_ = std::make_unique<math::Multiplication>(std::move(root_), std::move(other_ptr));
  Simplify();

  return *this;
}

Expression& Expression::operator-=(Expression other) {
  auto other_ptr = other.Release();

  if (!root_ || !other_ptr) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  root_ = std::make_unique<math::Subtraction>(std::move(root_), std::move(other_ptr));
  Simplify();

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Expression& expression) {
  os << expression.GetInfix();
  return os;
}

void Expression::Simplify() {
  if (root_) {
    if (auto simplified = root_->Simplify()) {
      root_ = std::move(simplified);
    }
  }
}

Expression Expression::GetDerivative(const Symbol& d) const {
  if (!root_) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  return root_->GetDerivative(d);
}

std::unique_ptr<math::TreeNode> Expression::GetCopy() const {
  if (!root_) {
    return nullptr;
  }

  return root_->Clone();
}

Expression Expression::Substitute(std::unordered_map<Symbol, Expression, SymbolHash> variable_to_value) const {
  if (!root_) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unordered_map<Symbol, std::unique_ptr<math::TreeNode>, SymbolHash> map;
  auto copy = GetCopy();

  for (auto pair : variable_to_value) {
    map.emplace(pair.first, pair.second.Release());
  }

  if (auto new_root = copy->Substitute(map)) {
    copy = std::move(new_root);
  }

  return copy;
}

Expression Expression::Evaluate() const {
  if (!root_) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  return root_->Evaluate();
}

Expression operator+(Expression lhs, Expression rhs) {
  lhs += std::move(rhs);

  return lhs;
}

Expression operator-(Expression lhs, Expression rhs) {
  lhs -= std::move(rhs);

  return lhs;
}

Expression operator*(Expression lhs, Expression rhs) {
  lhs *= std::move(rhs);

  return lhs;
}

Expression operator/(Expression lhs, Expression rhs) {
  lhs /= std::move(rhs);

  return lhs;
}

Expression operator-(Expression argument) {
  auto root = argument.Release();

  if (!root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unique_ptr<math::TreeNode> new_root = std::make_unique<math::UnaryMinus>(std::move(root));

  return new_root;
}

Expression operator+(Expression argument) {
  auto root = argument.Release();

  if (!root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  return root;
}

Expression Log(Expression argument) {
  auto root = argument.Release();

  if (!root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unique_ptr<math::TreeNode> new_root = std::make_unique<math::LogarithmNode>(std::move(root));

  return new_root;
}

Expression Sin(Expression argument) {
  auto root = argument.Release();

  if (!root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unique_ptr<math::TreeNode> new_root = std::make_unique<math::SinNode>(std::move(root));

  return new_root;
}

Expression Cos(Expression argument) {
  auto root = argument.Release();

  if (!root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unique_ptr<math::TreeNode> new_root = std::make_unique<math::CosNode>(std::move(root));

  return new_root;
}

Expression Tan(Expression argument) {
  auto root = argument.Release();

  if (!root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unique_ptr<math::TreeNode> new_root = std::make_unique<math::TangentNode>(std::move(root));

  return new_root;
}

Expression Sqrt(Expression argument) {
  auto root = argument.Release();

  if (!root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unique_ptr<math::TreeNode> new_root = std::make_unique<math::SquareRootNode>(std::move(root));

  return new_root;
}

Expression Pow(Expression base, Expression power) {
  auto base_root = base.Release();
  auto power_root = power.Release();

  if (!base_root || !power_root) {
    throw std::runtime_error(constants::ExceptionMessage::kEmptyExpression.data());
  }

  std::unique_ptr<math::TreeNode> new_root =
      std::make_unique<math::Exponentiation>(std::move(base_root), std::move(power_root));
  return new_root;
}

std::string RPN(const Expression& expression) {
  return expression.GetRPN();
}

std::string Infix(const Expression& expression) {
  return expression.GetInfix();
}

std::string Latex(const Expression& expression) {
  return expression.GetLatex();
}

Expression Diff(const Expression& expression, Symbol d) {
  return expression.GetDerivative(d);
}

Expression Evaluate(const Expression& expression) {
  return expression.Evaluate();
}
Expression Evaluate(const Expression& expression,
                    std::unordered_map<Symbol, Expression, SymbolHash> variable_to_value) {
  if (!variable_to_value.empty()) {
    return expression.Substitute(std::move(variable_to_value)).Evaluate();
  }

  return expression.Evaluate();
}

Expression Substitute(const Expression& expression,
                      std::unordered_map<Symbol, Expression, SymbolHash> variable_to_value) {
  return expression.Substitute(std::move(variable_to_value));
}

}  // namespace symcpp
