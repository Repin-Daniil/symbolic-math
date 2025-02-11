#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include <sstream>
#include <thread>
#include <vector>
#include "symcpp/utils/logger/log.hpp"
#include "symcpp/utils/logger/log.hpp"  //check include-guards

using namespace symcpp::utils::log;

struct LogTestFixture {
  std::ostringstream logStream;
  LogCallback originalLogger;

  LogTestFixture() {
    originalLogger = GetLogger();

    SetLogger([this](LogLevel, std::string_view message) { logStream << message << std::endl; });
  }

  ~LogTestFixture() {
    SetLogger(originalLogger);
  }

  std::string GetLog() const {
    return logStream.str();
  }

  void ClearLog() {
    logStream.str("");
    logStream.clear();
  }
};

TEST_CASE_METHOD(LogTestFixture, "Basic Logging", "[log]") {
  LOG_INFO() << "Test message";
  std::string log_output = GetLog();

  REQUIRE(log_output.find("Test message") != std::string::npos);
  REQUIRE(log_output.find("[INFO]") != std::string::npos);
}

TEST_CASE_METHOD(LogTestFixture, "Log Levels with filter", "[log]") {
  LOG_TRACE() << "Trace log";
  LOG_DEBUG() << "Debug log";
  LOG_INFO() << "Info log";
  LOG_WARNING() << "Warning log";
  LOG_ERROR() << "Error log";
  LOG_CRITICAL() << "Critical log";

  std::string log_output = GetLog();

  REQUIRE(log_output.find("[TRACE]") == std::string::npos);
  REQUIRE(log_output.find("[DEBUG]") == std::string::npos);
  REQUIRE(log_output.find("[INFO]") != std::string::npos);
  REQUIRE(log_output.find("[WARNING]") != std::string::npos);
  REQUIRE(log_output.find("[ERROR]") != std::string::npos);
  REQUIRE(log_output.find("[CRITICAL]") != std::string::npos);
}

TEST_CASE_METHOD(LogTestFixture, "Source Location", "[log]") {
  LOG_INFO() << "Location test";
  std::string log_output = GetLog();

  REQUIRE(log_output.find("logger_test.cpp") != std::string::npos);
  REQUIRE(log_output.find("Location test") != std::string::npos);
}

TEST_CASE_METHOD(LogTestFixture, "Thread Safety", "[log][thread]") {
  SetThreadSyncEnabled(true);
  const int num_threads = 10;
  const int logs_per_thread = 10;

  std::vector<std::thread> threads;
  threads.reserve(num_threads);

  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back([] {
      for (int j = 0; j < logs_per_thread; ++j) {
        LOG_INFO() << "Thread " << std::this_thread::get_id() << " - Message " << j;
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  std::string log_output = GetLog();
  std::size_t count = std::ranges::count(log_output, '\n');

  REQUIRE(count == num_threads * logs_per_thread);
}

TEST_CASE("Custom Logger", "[log][custom]") {
  std::ostringstream customStream;

  SetLogger([&customStream](LogLevel, std::string_view message) { customStream << message << "\n"; });

  LOG_INFO() << "Custom logger test";
  std::string log_output = customStream.str();

  REQUIRE(log_output.find("Custom logger test") != std::string::npos);

  SetLogger(nullptr);
}

TEST_CASE_METHOD(LogTestFixture, "Log Color", "[log][color]") {
  LOG_ERROR() << "Color test";
  std::string log_output = GetLog();

  REQUIRE(log_output.find("\033[31m") != std::string::npos);  // RED
}
