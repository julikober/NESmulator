#pragma once

#include <cstdint>

class CartridgeMemory {
 private:
  uint8_t *memory;

 public:
  CartridgeMemory(uint16_t size) {
    memory = new uint8_t[size];
  };
  virtual ~CartridgeMemory() {};

  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
};
