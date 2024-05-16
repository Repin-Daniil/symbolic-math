#include "symbol.h"

#include <utility>

namespace math {

Symbol::Symbol(std::string_view symbol) : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
}

Symbol::Symbol(char symbol) : symbol_({symbol}), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
}

Symbol::Symbol(const char* symbol) : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
}

Symbol::Symbol(std::string symbol)
    : symbol_(std::move(symbol)), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
}

Symbol::Symbol(char symbol, double value)
    : symbol_({symbol}), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
}

Symbol::Symbol(std::string_view symbol, const Number& value)
    : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
}

Symbol::Symbol(char symbol, const Number& value)
    : symbol_({symbol}), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
}

Symbol::Symbol(std::string_view symbol, double value)
    : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
}

std::string Symbol::GetSymbol() const noexcept {
  return symbol_;
}

bool Symbol::operator==(const Symbol& rhs) const {
  return symbol_ == rhs.symbol_;
}

bool Symbol::operator!=(const Symbol& rhs) const {
  return !(rhs == *this);
}

std::shared_ptr<std::pair<bool, Number>> Symbol::GetValue() const noexcept {
  return value_;
}

std::string Symbol::GetString() noexcept {
  if (value_->first) {
    return value_->second.GetString();
  }

  return symbol_;
}

std::string Symbol::GetString() const noexcept {
  return symbol_;
}

Symbol& Symbol::operator=(const Number& new_value) {
  value_->second = new_value;
  value_->first = true;
  return *this;
}

Symbol& Symbol::operator=(double new_value) {
  value_->second = new_value;
  value_->first = true;
  return *this;
}

Symbol& Symbol::operator=(const Symbol& other) {
  value_->first = other.value_->first;
  value_->second = other.value_->second;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  os << symbol.GetString();

  return os;
}

std::ostream& operator<<(std::ostream& os, Symbol& symbol) {
  os << symbol.GetString();

  return os;
}

void Symbol::Reset() {
  value_->first = false;
}

}  // namespace math