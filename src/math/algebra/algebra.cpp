#include "algebra.h"

namespace math {

void Algebra::AddFunction(std::string_view rpn_expression) {
  function_ = BuildFunctionTree(rpn_expression);
  derivative_ = BuildDerivativeTree(function_);
}

std::vector<Coordinate> Algebra::GetFunctionGraph() {
  auto graph = BuildGraph(function_, {});
  left_border = graph[0].first;
  right_border = graph[graph.size() - 1].first;

  return graph;
}

std::vector<Coordinate> Algebra::GetDerivativeGraph() {
  return BuildGraph(derivative_, {});
}

std::vector<Coordinate> Algebra::GetTangentGraph(double x) {
  return BuildGraph(tangent_, CalculateTangent(x));
}

std::string Algebra::GetFunction() {
  return function_.GetInfixExpression({});
}

std::string Algebra::GetDerivative() {
  return derivative_.GetInfixExpression({});
}

std::string Algebra::GetTangent(double x) {
  return tangent_.GetInfixExpression(CalculateTangent(x));
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
  left_border = -50;
  right_border = 50;
}

double Algebra::Calculate(const utils::AbstractSyntaxTree& function,
                          const std::unordered_map<char, double>& variable_to_value) {
  return function.GetNumericResult(variable_to_value);
}

std::vector<Coordinate> Algebra::BuildGraph(const utils::AbstractSyntaxTree& function,
                                            std::unordered_map<char, double> variable_to_value) {
  std::vector<Coordinate> coords;

  for (int i = left_border * 100; i <= right_border * 100; i += 1) {
    double x = i / 100.;
    variable_to_value['x'] = x;

    try {
      double y = Calculate(function, variable_to_value);
      coords.emplace_back(x, y);
    } catch (const std::exception& ex) {
      continue;
    }
  }

  return coords;
}

std::unordered_map<char, double> Algebra::CalculateTangent(double x) {
  std::unordered_map<char, double> variable_to_value;

  auto y = Calculate(function_, {{'x', x}});
  double k;
  try {
    k = Calculate(derivative_, {{'x', x}});
  } catch (...) {
    k = Calculate(derivative_, {{'x', x + 0.01}});
  }
  auto b = y - k * x;

  variable_to_value['x'] = x;
  variable_to_value['k'] = k;
  variable_to_value['b'] = b;

  return variable_to_value;
}

}  // namespace math
