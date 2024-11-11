#pragma once

#include <exception>
#include <string>

class InvalidAccessTypeException : public std::exception {
 private:
  std::string mMessage;

 public:
  InvalidAccessTypeException(const std::string message) : mMessage(message) {}

  const char* what() const throw() { return mMessage.c_str(); }
};

class InvalidAddressException : public std::exception {
 private:
  std::string mMessage;

 public:
  InvalidAddressException(const std::string message) : mMessage(message) {}

  const char* what() const throw() { return mMessage.c_str(); }
};
