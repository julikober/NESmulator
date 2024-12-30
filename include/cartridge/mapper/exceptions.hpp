#pragma once

#include <exception>
#include <string>

class MissingNametableMirroringException : public std::exception {
 private:
  std::string mMessage;

 public:
  MissingNametableMirroringException(const std::string message)
      : mMessage(message) {}

  const char* what() const throw() { return mMessage.c_str(); }
};