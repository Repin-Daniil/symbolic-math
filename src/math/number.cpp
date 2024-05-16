#include "number.h"
#include <stdexcept>
#include <valarray>
#include "constants_storage.h"

namespace math {

Number::Number() : value_(0) {
}

Number::Number(double value) : value_(value) {
}

Number::Number(const Number& other) {
  value_ = other.value_;
}

Number& Number::operator+=(const Number& other) {
  value_ += other.value_;

  return *this;
}

Number& Number::operator-=(const Number& other) {
  value_ -= other.value_;

  return *this;
}

Number& Number::operator*=(const Number& other) {
  value_ *= other.value_;

  return *this;
}

Number& Number::operator/=(const Number& other) {
  if (other.value_ == 0) {
    throw std::runtime_error(constants::ExceptionMessage::kZeroDivision.data());
  }

  value_ /= other.value_;

  return *this;
}

Number& Number::operator++() {
  ++value_;
  return *this;
}

Number Number::operator++(int) {
  Number copy(value_);
  ++value_;

  return *this;
}

Number& Number::operator--() {
  --value_;
  return *this;
}

Number Number::operator--(int) {
  Number copy(value_);
  --value_;

  return *this;
}

Number& Number::operator=(const Number& other) = default;

Number operator+(const Number& lhs, const Number& rhs) {
  Number result = lhs;
  result += rhs;

  return result;
}

Number operator-(const Number& lhs, const Number& rhs) {
  Number result = lhs;
  result -= rhs;

  return result;
}

Number operator*(const Number& lhs, const Number& rhs) {
  Number result = lhs;
  result *= rhs;

  return result;
}

Number operator/(const Number& lhs, const Number& rhs) {
  Number result = lhs;
  result /= rhs;

  return result;
}

bool operator<(const Number& lhs, const Number& rhs) {
  return lhs.GetValue() < rhs.GetValue();
}

bool operator>(const Number& lhs, const Number& rhs) {
  return lhs.GetValue() > rhs.GetValue();
}

bool operator==(const Number& lhs, const Number& rhs) {
  return lhs.GetValue() == rhs.GetValue();
}

bool operator!=(const Number& lhs, const Number& rhs) {
  return lhs.GetValue() != rhs.GetValue();
}

bool operator>=(const Number& lhs, const Number& rhs) {
  return lhs.GetValue() >= rhs.GetValue();
}

bool operator<=(const Number& lhs, const Number& rhs) {
  return lhs.GetValue() <= rhs.GetValue();
}

Number operator-(const Number& number) {
  return 0 - number;
}

Number operator+(const Number& number) {
  return number;
}

Number Log(const Number& argument) {
  if (argument < 0 || std::abs(argument.GetValue() - 0) < std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongLogarithm.data());
  }

  return std::log(argument.GetValue());
}

Number Sin(const Number& argument) {
  return std::sin(argument.GetValue());
}

Number Cos(const Number& argument) {
  return std::cos(argument.GetValue());
}

Number Tan(const Number& argument) {
  if (std::abs(std::numbers::pi / 2.0 - std::fmod(argument.GetValue(), std::numbers::pi)) <
      std::numeric_limits<double>::epsilon()) {
    throw std::runtime_error(constants::ExceptionMessage::kWrongTangent.data());
  }

  return std::tan(argument.GetValue());
}

Number Sqrt(const Number& argument) {
  if (argument < 0) {
    throw std::runtime_error(constants::ExceptionMessage::kNegativeRoot.data());
  }

  return std::sqrt(argument.GetValue());
}

Number Pow(const Number& base, const Number& power) {
  return std::pow(base.GetValue(), power.GetValue());
}

double Number::GetValue() const noexcept {
  return value_;
}
std::ostream& operator<<(std::ostream& os, const Number& number) {
  os << number.GetString();
  return os;
}

std::string Number::GetString() const noexcept {
  // FIXME Почему раньше тут стоял abs?
  auto str = std::to_string(value_);
  int64_t dot_position = str.find(constants::Labels::kDecimalPoint);

  if (dot_position == std::string::npos) {
    return str;
  }

  int64_t last_non_zero = str.size() - 1;

  while (str[last_non_zero] == constants::Labels::kZero) {
    last_non_zero--;
  }

  if (str[last_non_zero] == constants::Labels::kDecimalPoint) {
    last_non_zero--;
  }

  return str.substr(0, last_non_zero + 1);
}

}  // namespace math
