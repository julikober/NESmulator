#pragma once

#include <array>

#include "memory/memory.hpp"

#define PALETTES_SIZE 0x0020  // 32 bytes

class PalettesMemory : public Memory {
 private:
  std::array<uint8_t, PALETTES_SIZE> mMemory;

 public:
  PalettesMemory() : Memory() {};
  ~PalettesMemory() {};

  virtual inline uint8_t read(uint32_t address) override {
    return mMemory[address];
  }

  virtual inline void write(uint32_t address, uint8_t value) override {
    mMemory[address] = value;
  }

  virtual void load(const uint8_t *data, size_t size) override;

  virtual inline size_t size() override { return PALETTES_SIZE; }
};
