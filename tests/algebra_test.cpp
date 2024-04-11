#include "math/algebra/algebra.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "utils/converter/converter.h"

TEST_CASE("x^2", "Algebra") {
  math::Algebra algebra;
  algebra.AddFunction(utils::Converter::ConvertInfixToRPN("x^2"));

  //  algebra.GetDerivative();
  //  algebra.GetTangent();
  //  algebra.GetFunction();
  //  algebra.GetFunctionGraph();
  //  algebra.GetTangentGraph();
  //  algebra.GetDerivativeGraph();
}

// Это интеграционный тест, здесь уже не нужно рассматривать все случаи. Просто чекни все функции
// Еще касательную в отрицательном x
// Проверить что AddFunc ресетит