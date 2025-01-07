#include "ppu/memory/memorymap.hpp"

uint8_t PPUMemoryMap::PalettesSection::read(uint16_t address) {
  return mMemory.read(address);
}

void PPUMemoryMap::PalettesSection::write(uint16_t address, uint8_t value) {
  mMemory.write(address, value);
}
