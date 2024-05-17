#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <valarray>
#include "constants_storage.h"

namespace math {

class Number {
 public:
  Number();
  Number(double value);         // NOLINT
  Number(const Number& other);  // NOLINT

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

Number Log(const Number& argument);
Number Sin(const Number& argument);
Number Cos(const Number& argument);
Number Tan(const Number& argument);
Number Sqrt(const Number& argument);
Number Pow(const Number& base, const Number& power);

}  // namespace math
