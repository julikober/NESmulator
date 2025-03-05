#include "cpu/memory/memorymap.hpp"

CPUMemoryMap::CartridgeSection::CartridgeSection(Mapper** mapper)
        : Section(mapper, CARTRIDGE_START, CARTRIDGE_END) {};

uint8_t CPUMemoryMap::CartridgeSection::read(uint16_t address) {
  return (*mMapper)->readPRG(address);
}

void CPUMemoryMap::CartridgeSection::write(uint16_t address, uint8_t value) {
  (*mMapper)->writePRG(address, value);
}
