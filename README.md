# Лабораторные работы по дисциплине "Языки программирования"

**Лабораторная работа №1**: Стековый калькулятор

**Лабораторная работа №2**: Калькулятор производных

## Сборка
```
mkdir build
cd build
pip3 install conan==1.*
conan install .. --build=missing -s build_type=ReleaseRoot -s compiler.libcxx=libstdc++11
cmake .. -DCMAKE_BUILD_TYPE=ReleaseRoot
cmake --build . --target all
```

## Запуск тестов
```
ctest --extra-verbose --test-dir build
```
