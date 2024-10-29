#include "cpu/memory/cpu_memory.hpp"

uint8_t CPUMemory::RAM::read(uint16_t address) {
  return mMemory[mResolveMirrors(address) - mStart];
}

void CPUMemory::RAM::write(uint16_t address, uint8_t value) {
  mMemory[mResolveMirrors(address) - mStart] = value;
}
