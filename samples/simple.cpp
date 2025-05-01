#include <symcpp/symcpp.h>

#include <complex>
#include <iostream>

/**
 * @brief Example from README.md
 */
int main() {
  using namespace symcpp;

  utils::log::SetLogTimeEnabled(false);
  utils::log::SetLogLocationEnabled(false);
  utils::log::SetThreadSyncEnabled(false);

  Symbol x('x'), y('y');
  Number num = 17;

  Notebook in;
  in[0] = Expression("x + ln(y^2)", {x, y});

  LOG_INFO() << "in[0] = " << in[0];

  in[1] = Pow(x, 2) * 13 + Sin(pi * y);
  LOG_INFO() << "in[1] = " << in[1];

  x = 3;

  LOG_INFO() << "in[1] = " << in[1];

  y = num / 2;

  LOG_INFO() << "in[1] = " << in[1];

  Number result = in[1];
  LOG_INFO() << "result = " << result;

  x.Reset();
  LOG_INFO() << 'x reset';
  LOG_INFO() << "in[1] = " << in[1];
  LOG_INFO() << "in[1] = " << Infix(in[1]);
  y.Reset();
  LOG_INFO() << 'y reset';
  LOG_INFO() << "in[1] = " << in[1];

  auto d_x = Diff(in[1], x);
  LOG_INFO() << "f`x(x,y) = " << d_x;

  auto d_y = Diff(in[1], y);
  LOG_INFO() << "f`y(x,y) = " << d_y;

  Number result_2 = Evaluate(Log(in[1]), {{x, 14}, {y, 17}});
  LOG_INFO() << "result_2 = " << result_2;

  LOG_INFO() << "RPN = " << RPN(in[1] + Log(Pow(x, y)));
  LOG_INFO() << "LaTeX = " << Latex(in[1] + Log(Pow(x, y)));
}
