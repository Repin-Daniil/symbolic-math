#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/abstract-syntax-tree/ast.h"

namespace math {

using Coordinate = std::pair<double, double>;

class Algebra {
 public:
  Algebra() : tangent_(BuildTangentTree()) {
  }

  void AddFunction(std::string rpn_expression);

  std::vector<Coordinate> GetFunctionGraph();
  std::vector<Coordinate> GetDerivativeGraph();
  std::vector<Coordinate> GetTangentGraph(double x);

  std::string GetFunction();
  std::string GetDerivative();
  std::string GetTangent(double x);

  void Reset();

 private:
  utils::AbstractSyntaxTree BuildFunctionTree(std::string_view rpn_expression);
  utils::AbstractSyntaxTree BuildDerivativeTree(const utils::AbstractSyntaxTree& function);
  utils::AbstractSyntaxTree BuildTangentTree();

  std::vector<Coordinate> BuildGraph(const utils::AbstractSyntaxTree& function,
                                     std::unordered_map<char, double> variable_to_value);
  double Calculate(const utils::AbstractSyntaxTree& function,
                   const std::unordered_map<char, double>& variable_to_value);

 private:
  utils::AbstractSyntaxTree function_;
  utils::AbstractSyntaxTree derivative_;
  utils::AbstractSyntaxTree tangent_;
};

}  // namespace math
