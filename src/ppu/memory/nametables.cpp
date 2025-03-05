#include "ppu/memory/nametables.hpp"

NameTablesMemory::NameTablesMemory() : Memory() {}

uint8_t NameTablesMemory::read(uint32_t address) {
  return mMemory[address];
}

void NameTablesMemory::write(uint32_t address, uint8_t value) {
  mMemory[address] = value;
}

void NameTablesMemory::load(const uint8_t* data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds nametables size");
  }

  for (size_t i = 0; i < size; i++) {
    mMemory[i] = data[i];
  }
}
