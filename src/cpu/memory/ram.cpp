#include "cpu/memory/ram.hpp"

RAM::RAM() : mMemory() {}

uint8_t RAM::read(uint32_t address) { return mMemory[address]; }

void RAM::write(uint32_t address, uint8_t value) { mMemory[address] = value; }

void RAM::load(const uint8_t* data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds RAM size");
  }

  for (size_t i = 0; i < size; i++) {
    mMemory[i] = data[i];
  }
}
