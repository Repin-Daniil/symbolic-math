#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include "number.h"

namespace symcpp {

/**
 * @brief Никак не работает с деревом, это просто обертка над строкой и опциональное значение, если это константа
 * Если был квалификатор const, то это константа и выбираются перегрузки с const
 * Все операторы присваивания делают глубокое копирование. Поверхностное и алиасинг делай через ссылки
 *@todo Нужна функцию Symbols, возвращающая tuple, вот так: x, y, z = Symbols("x y z")
 *
 */
class Symbol {
 public:
  Symbol(char symbol);              // NOLINT
  explicit Symbol(const char* symbol);       // NOLINT
  explicit Symbol(std::string symbol);       // NOLINT
  explicit Symbol(std::string_view symbol);  // NOLINT

  Symbol(char symbol, double value);
  Symbol(char symbol, const Number& value);
  Symbol(std::string_view symbol, double value);
  Symbol(std::string_view symbol, const Number& value);

  std::string GetSymbol() const noexcept;
  std::shared_ptr<std::pair<bool, Number>> GetValue() const noexcept;
  void Reset();

  std::string GetString() noexcept;        // Переменные должны печатать значение
  std::string GetString() const noexcept;  // Константы должны печатать символ

  Symbol& operator=(const Symbol& other);
  Symbol& operator=(const Number& new_value);
  Symbol& operator=(double new_value);

  bool operator==(const Symbol& rhs) const;
  bool operator!=(const Symbol& rhs) const;
  friend std::ostream& operator<<(std::ostream& os, Symbol& symbol);
  friend std::ostream& operator<<(std::ostream& os, const Symbol& symbol);
  friend std::istream& operator>>(std::istream& in, Symbol& symbol);

 private:
  std::string symbol_;
  std::shared_ptr<std::pair<bool, Number>> value_;
};

struct SymbolHash {
  std::size_t operator()(const Symbol& symbol) const {
    return std::hash<std::string>{}(symbol.GetSymbol());
  }
};

}  // namespace symcpp
