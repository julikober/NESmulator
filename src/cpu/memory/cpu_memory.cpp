#include "cpu/memory/cpu_memory.hpp"

uint8_t CPUMemoryMap::read(uint16_t address) {
  if (address >= RAM_START && address <= RAM_END) {
    return mRAM.read(address);
  } else if (address >= IO_START && address <= IO_END) {
    return mIO.read(address);
  } else {
    return 0;
  }
}

void CPUMemoryMap::write(uint16_t address, uint8_t value) {
  if (address >= RAM_START && address <= RAM_END) {
    mRAM.write(address, value);
  } else if (address >= IO_START && address <= IO_END) {
    mIO.write(address, value);
  }
}
