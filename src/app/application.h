#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "math/algebra/algebra.h"
#include "math/calc/calculator.h"
#include "utils/converter/converter.h"

namespace app {

struct CalculationResult {
  std::optional<std::string> error;
  double answer;
};

struct FunctionAnalysis {
  std::optional<std::string> error;
  std::string derivative;
  std::vector<math::Coordinate> graph_;
};

class Application {
 public:
  CalculationResult Calculate(std::string infix_expression);

  FunctionAnalysis AnalyzeFunction(std::string infix_expression);
  std::vector<math::Coordinate> BuildTangent(double x);

  void Reset();

 private:
  math::Calculator calculator_;
  math::Algebra algebra_;
};

}  // namespace app
