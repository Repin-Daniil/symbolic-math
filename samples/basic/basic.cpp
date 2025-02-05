#include <iostream>
#include <thread>

#include "symcpp.h"
#include "utils/logger/log.hpp"

using namespace symcpp;
using namespace std::literals;

Symbol x("x");

int main() {
  Symbol x("x"), y('y'), z("z"s);

  auto cosine = Cos(x);

  auto dx = Diff(cosine, ::x);
  std::cout << dx << '\n';

  utils::log::SetLogLevel(utils::log::LogLevel::DEBUG);
  utils::log::SetLogLocationEnabled(false);
  utils::log::SetLogTimeEnabled(false);

  LOG_DEBUG() << "I dnot koe";
  LOG_INFO() << "I dnot koe";
  LOG_TRACE() << "I dnot koe";
  LOG_WARNING() << "I dnot koe";
  LOG_CRITICAL() << "I dnot koe";
  LOG_ERROR() << "error";
  //
  // std::array<Expression,8> in;
  // std::unordered_map<std::string, Expression> expressions;
  //
  // in[0] = y*Sin(x) + x*Pow(y,2);
  // std::cout << in[0] << std::endl;
  // in[1] = in[0].Substitute({{x, z}});
  // std::cout << in[0] << std::endl;
  // std::cout << in[1] << std::endl;

  const int numThreads = 10;
  const int logsPerThread = 10;
  std::vector<std::thread> threads;
  threads.reserve(numThreads);

  for (int i = 0; i < numThreads; ++i) {
    threads.emplace_back([] {
      for (int j = 0; j < logsPerThread; ++j) {
        LOG_INFO() << "Thread " << std::this_thread::get_id() << " - Message " << j;
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  return EXIT_SUCCESS;
}