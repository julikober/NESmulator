#pragma once

#include <array>

#include "memory/memory.hpp"

#define NAMETABLES_SIZE 0x0800  // 2 KB

class NameTablesMemory : public Memory {
 private:
  std::array<uint8_t, NAMETABLES_SIZE> mMemory;

 public:
  NameTablesMemory() : Memory() {}
  ~NameTablesMemory() {}

  virtual inline uint8_t read(uint32_t address) override {
    return mMemory[address];
  }
  virtual inline void write(uint32_t address, uint8_t value) override {
    mMemory[address] = value;
  }

  virtual inline size_t size() override { return NAMETABLES_SIZE; }
};