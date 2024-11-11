#pragma once

#include <cstdint>

class CartridgeMemory {
 protected:
  uint8_t *mMemory;

 public:
  CartridgeMemory(uint16_t size) { mMemory = new uint8_t[size]; };
  virtual ~CartridgeMemory() {};

  inline uint8_t read(uint16_t address) { return mMemory[address]; }
  virtual void write(uint16_t address, uint8_t value) = 0;
};
