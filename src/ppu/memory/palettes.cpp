#include "ppu/memory/palettes.hpp"

PalettesMemory::PalettesMemory() : Memory() {}

uint8_t PalettesMemory::read(uint32_t address) {
  return mMemory[address];
}

void PalettesMemory::write(uint32_t address, uint8_t value) {
  mMemory[address] = value;
}

void PalettesMemory::load(const uint8_t *data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds palettes memory size");
  }

  for (size_t i = 0; i < size; i++) {
    mMemory[i] = data[i];
  }
}
