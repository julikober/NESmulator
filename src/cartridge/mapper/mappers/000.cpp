#include "cartridge/mapper/mappers/000.hpp"

// This mapper is hard wired and does not have any bank switching

MemoryLocation Mapper000::mMapPRG(uint16_t address) {
  if (address >= MAP000_PRG_RAM_START && address <= MAP000_PRG_RAM_END) {
    // RAM
    return {&mPrgRam, address - MAP000_PRG_RAM_START};
  } else if (address >= MAP000_PRG_ROM_START && address <= MAP000_PRG_ROM_END) {
    // ROM
    return {&mPrgRom, address - MAP000_PRG_ROM_START};
  }
}

MemoryLocation Mapper000::mMapCHR(uint16_t address) {
  if (address >= PATTERNTABLES_START && address <= PATTERNTABLES_END) {
    return {mChrMemory, address - PATTERNTABLES_START};
  } else if (address >= NAMETABLES_START && address <= NAMETABLES_END) {
    return mMapNametableMirrors(address);
  } 
}
