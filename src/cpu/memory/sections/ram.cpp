#include "cpu/memory/memorymap.hpp"

uint8_t CPUMemoryMap::RAMSection::read(uint16_t address) {
  return mMemory.read(mResolveMirrors(address) - mStart);
}

void CPUMemoryMap::RAMSection::write(uint16_t address, uint8_t value) {
  mMemory.write(mResolveMirrors(address) - mStart, value);
}
