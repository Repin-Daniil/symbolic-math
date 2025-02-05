#pragma once

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <source_location>
#include <sstream>

#include "constants_storage.h"

namespace symcpp::utils::log {

enum class LogLevel : int{
  TRACE = 0,
  DEBUG = 1,
  INFO = 2,
  WARNING = 3,
  ERROR = 4,
  CRITICAL = 5,
  OFF = 10,
};

using LogCallback = std::function<void(LogLevel, std::string_view)>;

LogCallback& GetLogger();
void SetLogger(LogCallback newLogger);

LogLevel GetLogLevel();
bool GetLogTimeEnabled();
bool GetLogLocationEnabled();
bool GetThreadSyncEnabled();

void SetLogLevel(LogLevel level);
void SetLogTimeEnabled(bool enabled);
void SetLogLocationEnabled(bool enabled);
void SetThreadSyncEnabled(bool enabled);

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

#define LOG(level)                                                              \
  if (symcpp::utils::log::LogLevel::level >= symcpp::utils::log::GetLogLevel()) \
  symcpp::utils::log::LogStream(symcpp::utils::log::LogLevel::level, std::source_location::current())

#define LOG_TRACE() LOG(TRACE)
#define LOG_DEBUG() LOG(DEBUG)
#define LOG_INFO() LOG(INFO)
#define LOG_WARNING() LOG(WARNING)
#define LOG_ERROR() LOG(ERROR)
#define LOG_CRITICAL() LOG(CRITICAL)

}  // namespace symcpp::utils::log
