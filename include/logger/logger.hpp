#pragma once

#include <iostream>

enum LogLevel {
  DEBUG,
  INFO,
  WARNING,
  ERROR
};

class Logger {
 private:
  Logger() = default;

 public:
  static Logger& getInstance();

  Logger(Logger const&) = delete;
  void operator=(Logger const&) = delete;
  ~Logger() = default;

  void log(const std::string& message, const LogLevel level);
};
