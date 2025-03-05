#include "ppu/memory/memorymap.hpp"

PPUMemoryMap::NameTablesSection::NameTablesSection(Mapper** mapper)
    : Section(mapper, NAMETABLES_START, NAMETABLES_END,
              NAMETABLES_MIRROR_SRC_START, NAMETABLES_MIRROR_SRC_END,
              NAMETABLES_MIRROR_DST_START, NAMETABLES_MIRROR_DST_END) {}

uint8_t PPUMemoryMap::NameTablesSection::read(uint16_t address) {
  return (*mMapper)->readCHR(address);
}

void PPUMemoryMap::NameTablesSection::write(uint16_t address, uint8_t value) {
  (*mMapper)->writeCHR(address, value);
}
