# SymCpp

С++ библиотека для символьных вычислений

## Пример использования

```c++
Symbol x('x'), y('y');
Symbol& z(x);  // alias for x
Number num = 17;

auto exp = x * 13 + Sin(pi * e);  // exp = x * 13 + sin(pi * y)

x = 3;        // exp = 3 * 13 + sin(pi * y)
y = num / 2;  // exp = 3 * 13 + sin(pi * 8.5)

Number result = exp;  // result = 40

auto derivative_of_num = Diff(result, x);  // = 0
auto derivative_of_func_x = Diff(exp, x);  // = 13
auto derivative_of_func_y = Diff(exp, y);  // = cos(pi * 8.5) * pi

Number result_2 = Evaluate(exp, {{x, 14}, {y, 17}});  // = 182

x.Reset();  // exp = x * 13 + sin(pi * 8.5)
y.Reset();  // exp = x * 13 + sin(pi * y)

RPN(Log(exp))  // x 13 * pi y * sin + ln (reverse polish notation)
```

## Сборка библиотеки

```shell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target SYMCPP
```

## Сборка примеров

```shell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target simple
cmake --build . --target tangent_builder
```

## Запуск примеров

```shell
./build/simple
./build/tangent_builder
```