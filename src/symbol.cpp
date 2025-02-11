#include "symbol.h"

#include <memory>
#include <string>
#include <utility>

namespace symcpp {

Symbol::Symbol(std::string_view symbol) : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from string_view";
}

Symbol::Symbol(char symbol) : symbol_({symbol}), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from char";
}

Symbol::Symbol(const char* symbol) : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from const char*";
}

Symbol::Symbol(std::string symbol)
    : symbol_(std::move(symbol)), value_(std::make_shared<std::pair<bool, Number>>(false, 0)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from string";
}

Symbol::Symbol(char symbol, double value)
    : symbol_({symbol}), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from char"
              << " with value = " << value_->second.GetValue();
}

Symbol::Symbol(char symbol, const Number& value)
    : symbol_({symbol}), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from string_view"
              << " and Number " << &value << "with value" << value_->second.GetValue();
}

Symbol::Symbol(std::string_view symbol, const Number& value)
    : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from string_view"
              << " and Number " << &value << "with value" << value_->second.GetValue();
}

Symbol::Symbol(std::string_view symbol, double value)
    : symbol_(symbol), value_(std::make_shared<std::pair<bool, Number>>(true, value)) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << symbol_ << " from string_view"
              << " with value = " << value_->second.GetValue();
}

Symbol::Symbol(const Symbol& other) : symbol_(other.symbol_), value_(other.value_) {
  LOG_TRACE() << "(" << this << ") Created Symbol " << other.symbol_ << " by copying Symbol (" << &other << ") "
              << other.GetSymbol();
}

Symbol::Symbol(std::string_view symbol, const Symbol& other) : symbol_(symbol), value_(other.value_) {
  LOG_TRACE() << "(" << this << ") Created alias " << symbol_ << " for (" << &other << ") " << other.GetSymbol();
}

Symbol::Symbol(char symbol, const Symbol& other) : symbol_({symbol}), value_(other.value_) {
  LOG_TRACE() << "(" << this << ") Created alias " << symbol_ << " for (" << &other << ") " << other.GetSymbol();
}

Symbol::Symbol(const char* symbol, const Symbol& other) : symbol_(symbol), value_(other.value_) {
  LOG_TRACE() << "(" << this << ") Created alias " << symbol_ << " for (" << &other << ") " << other.GetSymbol();
}

Symbol::Symbol(std::string symbol, const Symbol& other) : symbol_(std::move(symbol)), value_(other.value_) {
  LOG_TRACE() << "(" << this << ") Created alias " << symbol_ << " for (" << &other << ") " << other.GetSymbol();
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
  if (this != &other) {
    LOG_TRACE() << "Make alias for " << other.symbol_ << " (" << &other << ") as (" << this << ") " << symbol_
                << (other.value_->first ? " with value " + std::to_string(other.value_->second.GetValue())
                                        : " without value");

    value_ = other.value_;
  }

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  os << symbol.GetString();

  return os;
}

void Symbol::Reset() {
  LOG_TRACE() << "(" << this << ") Resetting Symbol " << symbol_;
  value_->first = false;
}

std::istream& operator>>(std::istream& in, Symbol& symbol) {
  LOG_TRACE() << "(" << &symbol << ") Reading Symbol " << symbol.GetSymbol();

  in >> symbol.value_->second;
  symbol.value_->first = true;

  return in;
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

}  // namespace symcpp
