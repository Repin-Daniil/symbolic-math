#include <iostream>
#include "utils/abstract-syntax-tree/ast.h"

int main() {
  auto expression = utils::AbstractSyntaxTree("x 2 + ");
  std::cout << expression.GetInfixExpression({}) << std::endl;
}
