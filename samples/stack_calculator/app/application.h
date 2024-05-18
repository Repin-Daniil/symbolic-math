#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "symcpp/stack_calc/calculator.h"
#include "symcpp/utils/converter/converter.h"

namespace symcpp::app {

struct CalculationResult {
  std::optional<std::string> error;
  double answer;
};

// struct FunctionAnalysis {
//   std::optional<std::string> error;
//   std::string function;
//   std::string derivative;
//   std::vector<symcpp::Coordinate> graph;
// };
//
// struct TangentBuildingResult {
//   std::optional<std::string> error;
//   std::string tangent;
//   std::vector<symcpp::Coordinate> graph;
// };

class Application {
 public:
  CalculationResult Calculate(std::string infix_expression);

  //  FunctionAnalysis AnalyzeFunction(std::string infix_expression);
  //  TangentBuildingResult BuildTangent(double x);

  void Reset();

 private:
  math::Calculator calculator_;
  //  symcpp::Algebra algebra_;
};

}  // namespace symcpp::app
