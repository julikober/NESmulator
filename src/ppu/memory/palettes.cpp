#include "ppu/memory/palettes.hpp"

void PalettesMemory::load(const uint8_t *data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds palettes memory size");
  }

  for (size_t i = 0; i < size; i++) {
    mMemory[i] = data[i];
  }
}