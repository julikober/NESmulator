#include "cpu/memory/memory.hpp"

uint8_t CPUMemoryMap::RAMSection::read(uint16_t address) {
  return mRAM.read(mResolveMirrors(address) - mStart);
}

void CPUMemoryMap::RAMSection::write(uint16_t address, uint8_t value) {
  mRAM.write(mResolveMirrors(address) - mStart, value);
}
