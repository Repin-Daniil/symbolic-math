#include "log.hpp"

#include <atomic>
#include <iostream>
#include <mutex>
#include <utility>

namespace symcpp::utils::log {

namespace {
std::mutex log_mutex_;
std::atomic current_log_level = LogLevel::INFO;
std::atomic log_time_enabled = true;
std::atomic log_location_enabled = true;
std::atomic log_thread_safe = false;
}  // namespace

void SetLogLevel(LogLevel level) {
  current_log_level.store(level, std::memory_order_relaxed);
}

void SetLogTimeEnabled(bool enabled) {
  log_time_enabled.store(enabled, std::memory_order_relaxed);
}

void SetLogLocationEnabled(bool enabled) {
  log_location_enabled.store(enabled, std::memory_order_relaxed);
}

void SetThreadSyncEnabled(bool enabled) {
  log_thread_safe.store(enabled, std::memory_order_relaxed);
}

LogLevel GetLogLevel() {
  return current_log_level.load();
}

bool GetLogTimeEnabled() {
  return log_time_enabled.load();
}

bool GetLogLocationEnabled() {
  return log_location_enabled.load();
}

bool GetThreadSyncEnabled() {
  return log_thread_safe.load();
}

LogCallback& GetLogger() {
  static LogCallback callback = nullptr;
  return callback;
}

void SetLogger(LogCallback newLogger) {
  GetLogger() = std::move(newLogger);
}

auto LogStream::GetTimestamp() {
  const auto now = std::chrono::system_clock::now();
  const auto t_c = std::chrono::system_clock::to_time_t(now);
  return std::put_time(std::localtime(&t_c), "%F %T");
}

LogStream::LogStream(LogLevel level, std::source_location loc) : level_(level), location_(loc) {
}

LogStream::~LogStream() {
  if (level_ < GetLogLevel()) return;

  std::ostringstream output;

  if (GetLogTimeEnabled()) {
    output << GetTimestamp() << " ";
  }

  output << GetLogLevelColor(level_) << "[" << GetLogLevelName(level_) << "]" << constants::BashColors::RESET;

  if (GetLogLocationEnabled()) {
    output << " (" << location_.file_name() << ":" << location_.line() << " " << location_.function_name() << ")";
  }

  output << ": " << buffer_.str();

  if (GetThreadSyncEnabled()) {
    log_mutex_.lock();
  }

  try {
    if (GetLogger()) {
      GetLogger()(level_, output.str());
    } else {
      std::cout << output.str() << std::endl;
    }
  } catch (...) {
    log_mutex_.unlock();
    std::cout << "Exception occured while logging" << std::endl;
  }

  if (GetThreadSyncEnabled()) {
    log_mutex_.unlock();
  }
}

const char* LogStream::GetLogLevelName(LogLevel level) {
  switch (level) {
    case LogLevel::TRACE:
      return "TRACE";
    case LogLevel::DEBUG:
      return "DEBUG";
    case LogLevel::INFO:
      return "INFO";
    case LogLevel::WARNING:
      return "WARNING";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::CRITICAL:
      return "CRITICAL";
    default:
      return "UNKNOWN";
  }
}

const char* LogStream::GetLogLevelColor(LogLevel level) {
  switch (level) {
    case LogLevel::TRACE:
      return constants::BashColors::CYAN;
    case LogLevel::DEBUG:
      return constants::BashColors::BLUE;
    case LogLevel::INFO:
      return constants::BashColors::GREEN;
    case LogLevel::WARNING:
      return constants::BashColors::YELLOW;
    case LogLevel::ERROR:
      return constants::BashColors::RED;
    case LogLevel::CRITICAL:
      return constants::BashColors::MAGENTA;
    default:
      return constants::BashColors::RESET;
  }
}

}  // namespace symcpp::utils::log
