#include "logger.h"

namespace {
using namespace std::literals;
}

namespace symcpp::utils {

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
  std::ostringstream full_message;

  full_message << GetTimestamp() << " " << GetLogLevelColor(level_) << "["sv << GetLogLevelName(level_) << "]"sv
               << constants::BashColors::RESET << " "
               << "("sv << location_.file_name() << ":"sv << location_.line() << " " << location_.function_name()
               << "): "sv << buffer_.str();

  if (GetLogger()) {
    GetLogger()(level_, full_message.str());
  } else {
    std::cout << full_message.str() << std::endl;  // FIXME osyncstream or mutex
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
}  // namespace symcpp::utils