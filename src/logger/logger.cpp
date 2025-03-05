#include "logger/logger.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>

Logger& Logger::getInstance() {
  static Logger instance;

  return instance;
}

void Logger::log(const std::string& message, const LogLevel level = INFO) {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::string color;
  switch (level) {
    case DEBUG:
      color = "\033[36m";
      break;  // Cyan
    case INFO:
      color = "\033[32m";
      break;  // Green
    case WARNING:
      color = "\033[33m";
      break;  // Yellow
    case ERROR:
      color = "\033[31m";
      break;  // Red
    default:
      color = "\033[0m";
      break;  // Reset
  }

  std::cout << color << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] "
            << "[" << level << "] " << message << "\033[0m" << std::endl;
}
