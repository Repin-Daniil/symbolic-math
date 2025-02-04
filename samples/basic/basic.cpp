#include <iostream>
#include "symcpp.h"

using namespace symcpp;
using namespace std::literals;

Symbol x("x");

int main() {
  Symbol x("x"), y('y'), z("z"s);

  auto cosine = Cos(x);

  auto dx = Diff(cosine, ::x);
  std::cout << dx << '\n';

  //
  // std::array<Expression,8> in;
  // std::unordered_map<std::string, Expression> expressions;
  //
  // in[0] = y*Sin(x) + x*Pow(y,2);
  // std::cout << in[0] << std::endl;
  // in[1] = in[0].Substitute({{x, z}});
  // std::cout << in[0] << std::endl;
  // std::cout << in[1] << std::endl;

  return EXIT_SUCCESS;
}