#include "ppu/memory/memorymap.hpp"

uint8_t PPUMemoryMap::PatternTablesSection::read(uint16_t address) {
  return (*mMapper)->readCHR(address);
}

void PPUMemoryMap::PatternTablesSection::write(uint16_t address, uint8_t value) {
  (*mMapper)->writeCHR(address, value);
}
