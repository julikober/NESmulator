#pragma once

#include <cstdint>

class CartridgeMemory {
 public:
  CartridgeMemory() {};
  virtual ~CartridgeMemory() {};

  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
};
