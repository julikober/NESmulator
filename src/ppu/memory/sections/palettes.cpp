#include "ppu/memory/memorymap.hpp"

PPUMemoryMap::PalettesSection::PalettesSection(Mapper** mapper)
    : Section(mapper, PALETTES_START, PALETTES_END, PALETTES_MIRROR_SRC_START,
              PALETTES_MIRROR_SRC_END, PALETTES_MIRROR_DST_START,
              PALETTES_MIRROR_DST_END) {}

uint8_t PPUMemoryMap::PalettesSection::read(uint16_t address) {
  return mMemory.read(address);
}

void PPUMemoryMap::PalettesSection::write(uint16_t address, uint8_t value) {
  mMemory.write(address, value);
}

void PPUMemoryMap::PalettesSection::load(const uint8_t* data,
                                                size_t size) {
  mMemory.load(data, size);
}
