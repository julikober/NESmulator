#include "cpu/memory/memorymap.hpp"

uint8_t CPUMemoryMap::CartridgeSection::read(uint16_t address) {
  return (*mMapper)->readPRG(address);
}

void CPUMemoryMap::CartridgeSection::write(uint16_t address, uint8_t value) {
  (*mMapper)->writePRG(address, value);
}
