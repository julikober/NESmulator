#pragma once

#include <array>

#include "memory/memory.hpp"

#define NAMETABLE_MEMORY_SIZE 0x0800  // 2 KB

class NametableMemory : public Memory {
 private:
  std::array<uint8_t, NAMETABLE_MEMORY_SIZE> mMemory;

 public:
  NametableMemory() : Memory() {}
  ~NametableMemory() {}

  virtual inline uint8_t read(uint32_t address) override {
    return mMemory[address];
  }
  virtual inline void write(uint32_t address, uint8_t value) override {
    mMemory[address] = value;
  }
};