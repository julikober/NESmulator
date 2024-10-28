#include "cpu/cpu_memory.hpp"

uint8_t CPUMemory::read(uint16_t address) {
    if (address >= RAM_START && address <= RAM_END) {
      return mRAM.read(address);
    } else if (address >= IO_START && address <= IO_END) {
      return mIO.read(address);
    } else if (address >= EXPANSION_ROM_START && address <= EXPANSION_ROM_END) {
      return mExpansionROM.read(address);
    } else if (address >= SRAM_START && address <= SRAM_END) {
      return mSRAM.read(address);
    } else if (address >= PRGROM_START && address <= PRGROM_END) {
      return mPRGROM.read(address);
    } else {
      return 0;
    }
  }

  void CPUMemory::write(uint16_t address, uint8_t value) {
    if (address >= RAM_START && address <= RAM_END) {
      mRAM.write(address, value);
    } else if (address >= IO_START && address <= IO_END) {
      mIO.write(address, value);
    } else if (address >= EXPANSION_ROM_START && address <= EXPANSION_ROM_END) {
      mExpansionROM.write(address, value);
    } else if (address >= SRAM_START && address <= SRAM_END) {
      mSRAM.write(address, value);
    } else if (address >= PRGROM_START && address <= PRGROM_END) {
      mPRGROM.write(address, value);
    }
  }

  void CPUMemory::clear() {
    mRAM.clear();
    mIO.clear();
    mExpansionROM.clear();
    mSRAM.clear();
    mPRGROM.clear();
  }
