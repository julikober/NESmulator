#pragma once

#include "cartridge/memory/cartridge_memory.hpp"

class CartridgeROM : public CartridgeMemory {
 public:
  CartridgeROM(uint16_t size) : CartridgeMemory(size) {}

  void write(uint16_t address, uint8_t value) override;
};
