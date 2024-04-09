#include "algebra.h"

namespace math {

void Algebra::AddFunction(std::string rpn_expression) {
  function_ = BuildFunctionTree(rpn_expression);
  derivative_ = BuildDerivativeTree(function_);
}

std::vector<Coordinate> Algebra::GetFunctionGraph() {
  return BuildGraph(function_, {});
}

std::vector<Coordinate> Algebra::GetDerivativeGraph() {
  return BuildGraph(derivative_, {});
}

std::vector<Coordinate> Algebra::GetTangentGraph(double x) {
  auto y = Calculate(function_, {{'x', x}});
  auto k = Calculate(derivative_, {{'x', x}});
  auto b = y - k * x;

  return BuildGraph(tangent_, {{'k', k}, {'x', x}, {'b', b}});
}

std::string Algebra::GetFunction() {
  return function_.GetInfixExpression();
}

std::string Algebra::GetDerivative() {
  return derivative_.GetInfixExpression();
}

std::string Algebra::GetTangent(double x) {
  return tangent_.GetInfixExpression();
}

utils::AbstractSyntaxTree Algebra::BuildFunctionTree(std::string_view rpn_expression) {
  return utils::AbstractSyntaxTree(rpn_expression);
}

utils::AbstractSyntaxTree Algebra::BuildDerivativeTree(const utils::AbstractSyntaxTree& function) {
  return function.GetDerivative();
}

utils::AbstractSyntaxTree Algebra::BuildTangentTree() {
  return utils::AbstractSyntaxTree("k x * b +");
}

void Algebra::Reset() {
  function_.Reset();
  derivative_.Reset();
}

double Algebra::Calculate(const utils::AbstractSyntaxTree& function,
                          const std::unordered_map<char, double>& variable_to_value) {
  return function.GetNumericResult(variable_to_value);
}

std::vector<Coordinate> Algebra::BuildGraph(const utils::AbstractSyntaxTree& function,
                                            std::unordered_map<char, double> variable_to_value) {
  std::vector<Coordinate> coords;

  for (int x = -5000; x <= 5000; x += 1) {
    variable_to_value['x'] = x / 100;
    coords.emplace_back(x / 100, Calculate(function, variable_to_value));  // FIXME поиграть с координатами
  }

  return coords;
}

}  // namespace math
