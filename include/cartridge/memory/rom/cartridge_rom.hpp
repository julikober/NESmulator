#pragma once

#include "cartridge/memory/cartridge_memory.hpp"
#include "logger/logger.hpp"
#include <exception>

class CartridgeROM : CartridgeMemory {
 public:
  CartridgeROM(uint16_t size) : CartridgeMemory(size) {}

  void write(uint16_t address, uint8_t value) override {
    throw std::runtime_error("Cannot write to ROM");
  }
};
