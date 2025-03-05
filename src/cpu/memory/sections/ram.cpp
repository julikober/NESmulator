#include "cpu/memory/memorymap.hpp"

CPUMemoryMap::RAMSection::RAMSection(Mapper** mapper)
    : Section(mapper, RAM_START, RAM_END, RAM_MIRROR_SRC_START,
              RAM_MIRROR_SRC_END, RAM_MIRROR_DST_START, RAM_MIRROR_DST_END) {};

uint8_t CPUMemoryMap::RAMSection::read(uint16_t address) {
  return mMemory.read(mResolveMirrors(address) - mStart);
}

void CPUMemoryMap::RAMSection::write(uint16_t address, uint8_t value) {
  mMemory.write(mResolveMirrors(address) - mStart, value);
}

void CPUMemoryMap::RAMSection::load(const uint8_t* data, size_t size) {
  mMemory.load(data, size);
}
