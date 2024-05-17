#include <iostream>
#include "symcpp.h"

int main() {
  using namespace math;
  using namespace std::literals;
  //  std::string_view stv("k");
  //  std::string str("s");
  //  {
  //    Symbol x = 'x';       // это переменная
  //    Symbol pi = "pi";     // это переменная
  //    Symbol pi1 = "pi"s;   // это переменная
  //    Symbol pi2 = "pi"sv;  // это переменная
  //    Symbol k = stv;       // это переменная
  //    Symbol s = str;       // это переменная
  //    Symbol y = "y";       // это переменная
  //  }
  //  {
  //    Symbol pi("pi", 3.14);  // а это константа
  //    Symbol z("z", 3.14);    // а это константа
  //    Symbol u('u', 3.14);    // а это константа
  //    Symbol k(stv, 3.14);    // а это константа
  //    Symbol s(str, 3);       // а это константа
  //  }
  //
  //  {
  //    Number one(1);
  //    Number pi(std::numbers::pi);
  //    one = 3;
  //    auto result = one + pi;
  //    result = one - pi;
  //    result = one * pi;
  //    result = one / pi;
  //    result = Log(Pow(one * pi, Log(pi)));
  //    std::cout << result.GetValue() << std::endl;
  //    result = one / pi;
  //    result = one / pi;
  //  }
  //  auto result = SinNode(x + pi);
  //
  //  Equation eq(Pow(x, 2) - 12*x, 5);
  //  TODO Expression нужно конструировать и от строки, чтобы вызывался ast_builder
  // TODO Latex();
  // TODO Нужны predefined константы

  //  {
  //    // Демонстрация подстановки на шаредах
  //    Symbol x = 'x';
  //    const Symbol pi("pi", 3.14);  // а это константа
  //
  //    auto exp = x * 1 + Sin(pi * std::numbers::e);
  //    //      std::cout << exp << std::endl;
  //    x = 3;
  //    std::cout << exp << std::endl;
  //    x = 16;
  //    std::cout << exp << std::endl;
  //
  //    x.Reset();
  //    std::cout << exp << std::endl;
  //  }
  //
  //  {
  //    // Операторы вывода
  //        Symbol x = 'x';
  //        const Symbol pi("pi", 3.14);  // а это константа
  //        Number one = 1;
  //
  //        auto exp = x + Sin(pi * std::numbers::e) - one;
  //        std::cout << exp << std::endl;
  //        std::cout << pi << std::endl;
  //        std::cout << one << std::endl;
  //        std::cout << x << std::endl;
  //        x = 3;
  //        std::cout << "x = 3" << std::endl;
  //        std::cout << exp << std::endl;
  //        std::cout << one << std::endl;
  //        std::cout << x << std::endl;
  //  }
  //
  //  {
  //    const Symbol pi("pi", 3.14);
  //    Symbol x('x');
  //    Expression a = x + pi;
  //    std::cout << Infix(pi, {}) << std::endl;
  //    std::cout << Infix(a, {}) << std::endl;
  //
  //    x = 12;
  //    Expression b = x + pi;
  //    Expression c = Log(b + pi/b);
  //    std::cout << Infix(c, {}) << std::endl;
  //    // Get Root!
  //    // x + 3.14
  //    // Get Root!
  //    // 12 + 3.14
  //  }

  //  {
  //    Symbol x('x');
  //    Expression result = Expression(1)/2;
  //  }

  //  {
  //        const Symbol pi("pi", 3.14);
  //        Symbol x('x');
  //        Symbol y('y', 12);
  //
  //        std::cout << pi << " " << x << " " << y << std::endl;
  //  }

  //  {
  //    Symbol x('x');
  //    Expression a = x + 2;
  //  }

  //  {
  //    Symbol x('x');
  //    Symbol y('y');
  //
  //    Expression result = Log(y) * y + Sin(Cos(x * 2));
  //
  //    Expression diff_x = Diff(result, x);
  //    Expression diff_y = Diff(result, y);
  //
  //    std::cout << result << std::endl;
  //    std::cout << diff_x << std::endl;
  //    std::cout << diff_y << std::endl;
  //  }
  //
  //  {
  //    Symbol x('x');
  //    Symbol y('y');
  //
  //    Expression result = Log(y) * y + Sin(Cos(x * 2));
  //    std::cout << result << std::endl;
  //    result = Substitute(result, {{x, Pow(y, Sin(x))}});
  //    std::cout << result << std::endl;
  //  }
  //
  //  {
  //    Symbol x('x');
  //    Symbol y('y');
  //
  //    Expression result = x;
  //    std::cout << result << std::endl;
  //    result = Substitute(result, {{x, Pow(y, Sin(x))}});
  //    std::cout << result << std::endl;
  //  }
  //  {
  //    Symbol x('x');
  //
  //    Expression result = x;
  //    std::cout << result << std::endl;
  //    result = Substitute(result, {{x, 2}});
  //    std::cout << result << std::endl;
  //  }
  //
  //  {
  //    Symbol x('x');
  //    Symbol pi("pi", 3.14);  // а это константа
  //
  //    Expression result = 2*Sin(pi) + Sqrt(x * x);
  //    std::cout << result << std::endl;
  //    x = 4;
  //    std::cout << result << std::endl;
  //    result = Evaluate(result);
  //    std::cout << result << std::endl;
  //  }

  //  {
  //    Symbol a('a');
  //    Expression exp = a + 2;
  //
  //    auto result = std::move(exp);
  //
  //    exp += 2;
  //    Sin(exp);
  ////    И прочие тесты на вылет исключения
  //    exp.Release();
  //  }

  //  {
  //    //Алиасинг
  //    Symbol x('x');
  //
  //    Symbol &y = x;
  //
  //    auto exp = x + y;
  //    std::cout << exp << std::endl;
  //  }

  //  {
  //    // TODO Перегрузить оператор ввода для Symbol
  //    // TODO Сделать конструирование Number от Expression, чтобы сам Evaluate вызывал
  //    Symbol x('x');
  //
  //    auto func = 12 * Sin(Log(x) * x) - Pow(x, Tan(x));
  //    std::cout << "f(x) = " << func << std::endl;
  //
  //    auto derivative = Diff(func, x);
  //    std::cout << "f`(x) = " << derivative << std::endl;
  //
  //    while (true) {
  //      int input;
  //      std::cin >> input;
  //
  //      x = input;
  //
  //      auto y = Evaluate(func);
  //      std::cout << "f(" << x << ") = " << y << std::endl;
  //
  //      auto k = derivative.Evaluate();
  //      auto b = (y - k * x).Evaluate();
  //      auto tangent = k * x + b;
  //
  //      x.Reset();
  //
  //      std::cout << "g(x) = " << tangent << std::endl;
  //    }
  //  }

  {
    Symbol x('x');
    Number a = -2;

    std::cout << x + a << std::endl;
  }
}
