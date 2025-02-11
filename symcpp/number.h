#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <valarray>
#include "symcpp/constants_storage.h"

namespace symcpp {

class Expression;

class Number {
 public:
  Number();
  Number(double value);                  // NOLINT
  Number(const Number& other);           // NOLINT
  Number(const Expression& expression);  // NOLINT
  double GetValue() const noexcept;
  std::string GetString() const noexcept;

  Number& operator=(const Number& other);

  Number& operator+=(const Number& other);
  Number& operator-=(const Number& other);
  Number& operator*=(const Number& other);
  Number& operator/=(const Number& other);

  Number& operator++();
  Number operator++(int);
  Number& operator--();
  Number operator--(int);
  friend std::ostream& operator<<(std::ostream& os, const Number& number);
  friend std::istream& operator>>(std::istream& in, Number& symbol);

 private:
  double value_;
  // TODO Пусть будет комплексным
};

Number operator+(const Number& lhs, const Number& rhs);
Number operator-(const Number& lhs, const Number& rhs);
Number operator*(const Number& lhs, const Number& rhs);
Number operator/(const Number& lhs, const Number& rhs);

bool operator<(const Number& lhs, const Number& rhs);
bool operator>(const Number& lhs, const Number& rhs);
bool operator==(const Number& lhs, const Number& rhs);
bool operator!=(const Number& lhs, const Number& rhs);
bool operator>=(const Number& lhs, const Number& rhs);
bool operator<=(const Number& lhs, const Number& rhs);

Number operator-(const Number& number);
Number operator+(const Number& number);

}  // namespace symcpp
