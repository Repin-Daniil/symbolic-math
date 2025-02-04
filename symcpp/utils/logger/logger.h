#pragma once

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <source_location>
#include <sstream>

#include "constants_storage.h"

namespace symcpp::utils {

enum class LogLevel { TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL };

using LogCallback = std::function<void(LogLevel, std::string_view)>;

LogCallback& GetLogger();
void SetLogger(LogCallback newLogger);

class LogStream {
  static auto GetTimestamp();

 public:
  explicit LogStream(LogLevel level, std::source_location loc = std::source_location::current());

  template <typename T>
  LogStream& operator<<(const T& value) {
    buffer_ << value;
    return *this;
  }

  ~LogStream();

 private:
  static const char* GetLogLevelName(LogLevel level);
  static const char* GetLogLevelColor(LogLevel level);

  LogLevel level_;
  std::ostringstream buffer_;
  std::source_location location_;
};

#define LOG(level) symcpp::utils::LogStream(symcpp::utils::LogLevel::level, std::source_location::current())
#define LOG_TRACE() LOG(TRACE)
#define LOG_DEBUG() LOG(DEBUG)
#define LOG_INFO() LOG(INFO)
#define LOG_WARNING() LOG(WARNING)
#define LOG_ERROR() LOG(ERROR)
#define LOG_CRITICAL() LOG(CRITICAL)
}  // namespace symcpp::utils