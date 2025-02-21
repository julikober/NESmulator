#include "ppu/memory/nametables.hpp"

void NameTablesMemory::load(const uint8_t* data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds nametables size");
  }

  for (size_t i = 0; i < size; i++) {
    mMemory[i] = data[i];
  }
}
