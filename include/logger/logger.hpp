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
  Logger() {}

 public:
  static Logger& getInstance() {
    static Logger instance;

    return instance;
  }

  Logger(Logger const&) = delete;
  void operator=(Logger const&) = delete;

  void log(const std::string& message, const LogLevel level);
};
