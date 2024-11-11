#pragma once

#include "cartridge/memory/cartridge_memory.hpp"

class CartridgeRAM : public CartridgeMemory {
 public:
  CartridgeRAM(uint16_t size) : CartridgeMemory(size) {}

  inline void write(uint16_t address, uint8_t value) override {
    mMemory[address] = value;
  }
};
