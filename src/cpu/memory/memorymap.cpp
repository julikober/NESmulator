#include "cpu/memory/memorymap.hpp"

uint8_t CPUMemoryMap::read(uint16_t address) {
  if (address >= RAM_START && address <= RAM_END) {
    return mRAM.read(address);
  } else if (address >= IO_START && address <= IO_END) {
    return mIO.read(address);
  } else if (address >= CARTRIDGE_START && address <= CARTRIDGE_END) {
    return mCartridge.read(address);
  } else {
    throw std::out_of_range(
        "CPUMemoryMap::read - Address does not match any section");
  }
}

void CPUMemoryMap::write(uint16_t address, uint8_t value) {
  if (address >= RAM_START && address <= RAM_END) {
    mRAM.write(address, value);
  } else if (address >= IO_START && address <= IO_END) {
    mIO.write(address, value);
  } else if (address >= CARTRIDGE_START && address <= CARTRIDGE_END) {
    mCartridge.write(address, value);
  } else {
    throw std::out_of_range(
        "CPUMemoryMap::read - Address does not match any section");
  }
}
