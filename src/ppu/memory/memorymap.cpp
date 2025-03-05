#include "ppu/memory/memorymap.hpp"

PPUMemoryMap::PPUMemoryMap(Mapper** mapper)
    : MemoryMap(mapper),
      mPatternTablesSection(mapper),
      mNameTablesSection(mapper),
      mPalettesSection(mapper) {}

uint8_t PPUMemoryMap::read(uint16_t address) {
  if (address >= PATTERNTABLES_START && address <= PATTERNTABLES_END) {
    return mPatternTablesSection.read(address);
  } else if (address >= NAMETABLES_START && address <= NAMETABLES_END) {
    return mNameTablesSection.read(address);
  } else if (address >= PALETTES_START && address <= PALETTES_END) {
    return mPalettesSection.read(address);
  } else {
    throw std::out_of_range(
        "PPUMemoryMap::read - Address does not match any section");
  }
}

void PPUMemoryMap::write(uint16_t address, uint8_t value) {
  if (address >= PATTERNTABLES_START && address <= PATTERNTABLES_END) {
    mPatternTablesSection.write(address, value);
  } else if (address >= NAMETABLES_START && address <= NAMETABLES_END) {
    mNameTablesSection.write(address, value);
  } else if (address >= PALETTES_START && address <= PALETTES_END) {
    mPalettesSection.write(address, value);
  } else {
    throw std::out_of_range(
        "PPUMemoryMap::write - Address does not match any section");
  }
}
