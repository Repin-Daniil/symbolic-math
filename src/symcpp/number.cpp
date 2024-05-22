#include "number.h"
#include "expression.h"

namespace symcpp {

Number::Number() : value_(0) {
}

Number::Number(double value) : value_(value) {
}

Number::Number(const Number& other) {
  value_ = other.value_;
}

Number::Number(const Expression& expression) {
  auto root = expression.Evaluate().Release();

  if (root->GetType() != constants::Expressions::NUMBER) {
    throw std::runtime_error("Can't be cast to Number");
  }

  value_ = dynamic_cast<math::NumberNode*>(root.get())->GetValue().GetValue();
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

double Number::GetValue() const noexcept {
  return value_;
}
std::ostream& operator<<(std::ostream& os, const Number& number) {
  os << number.GetString();
  return os;
}

std::istream& operator>>(std::istream& in, Number& number) {
  in >> number.value_;

  return in;
}

std::string Number::GetString() const noexcept {
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

}  // namespace symcpp
