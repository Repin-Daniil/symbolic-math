#include <iostream>
#include <thread>

#include "symcpp.h"
#include "utils/logger/log.hpp"

using namespace symcpp;
using namespace std::literals;


int main() {
  {
    utils::log::SetLogLevel(utils::log::LogLevel::OFF);
    utils::log::SetLogTimeEnabled(false);

    Symbol x("x"), y('y'), z(y);

    auto cos = Cos(x);
    auto dx = Diff(cos, x);

    std::array<Expression, 8> in;
    std::unordered_map<std::string, Expression> expressions;

    in[0] = y * Sin(x) + x * Pow(y, 2);
    LOG_INFO() << in[0];

    in[1] = in[0].Substitute({{x, z}});
    y = 2;
    LOG_INFO() << in[0];
    LOG_INFO() << in[1];
  }

  utils::log::SetLogLevel(utils::log::LogLevel::INFO);

  Symbol x("x");

  std::array<Expression, 8> in;
  in[0] = Cos(x) * Sin(x);
  in[1] = Diff(in[0], x);
  LOG_INFO() << in[0];

  auto root = in[0].Release();

  LOG_INFO() << root->IsA(constants::Expressions::OPERAND);
  LOG_INFO() << root->IsA(constants::Expressions::UNARY_OPERATION);
  LOG_INFO() << root->IsA(constants::Expressions::BINARY_OPERATION);
  LOG_INFO() << root->IsA(constants::Expressions::MULTIPLICATION);

  auto root_ptr = dynamic_cast<math::BinaryOperation*>(root.get());

  if (root_ptr) {
    auto unary_ptr = root_ptr->ReleaseLeftArgument();
    LOG_INFO() << "Cos is unary = " << unary_ptr->IsA(constants::Expressions::UNARY_OPERATION);
    LOG_INFO() << "Cos is unary = " << unary_ptr->IsA(constants::Expressions::COS);
    auto raw_unary_ptr = dynamic_cast<math::UnaryOperation*>(unary_ptr.get());
    // auto raw_unary_ptr = static_cast<math::UnaryMinus*>(unary_ptr.get());

    if (raw_unary_ptr) {
      auto var_ptr = raw_unary_ptr->ReleaseArgument();
      LOG_INFO() << "X is variable = " << var_ptr->IsA(constants::Expressions::VARIABLE);
      LOG_INFO() << "X is operand = " << var_ptr->IsA(constants::Expressions::OPERAND);
    }
  } else {
    LOG_ERROR() << "Root is not binary";
  }

  return EXIT_SUCCESS;
}