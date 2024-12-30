#pragma once

#include <array>

#include "memory/memory.hpp"

#define RAM_SIZE 0x0800  // 2 KB

class RAM : public Memory {
 private:
  std::array<uint8_t, RAM_SIZE> mMemory;

 public:
  RAM() : Memory() {};
  ~RAM() {};

  virtual inline uint8_t read(uint32_t address) override {
    return mMemory[address];
  }
  virtual inline void write(uint32_t address, uint8_t value) override {
    mMemory[address] = value;
  }
};
