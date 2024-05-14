#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "math/stack_calc/calculator.h"
#include "math/utils/converter/converter.h"

namespace app {

struct CalculationResult {
  std::optional<std::string> error;
  double answer;
};

// struct FunctionAnalysis {
//   std::optional<std::string> error;
//   std::string function;
//   std::string derivative;
//   std::vector<math::Coordinate> graph;
// };
//
// struct TangentBuildingResult {
//   std::optional<std::string> error;
//   std::string tangent;
//   std::vector<math::Coordinate> graph;
// };

class Application {
 public:
  CalculationResult Calculate(std::string infix_expression);

  //  FunctionAnalysis AnalyzeFunction(std::string infix_expression);
  //  TangentBuildingResult BuildTangent(double x);

  void Reset();

 private:
  math::Calculator calculator_;
  //  math::Algebra algebra_;
};

}  // namespace app
