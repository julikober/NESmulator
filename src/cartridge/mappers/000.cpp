#include "cartridge/mappers/000.hpp"

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
  if (address >= NAMETABLE_1_START && address <= NAMETABLE_1_END) {
    if (mMirroringMode == HORIZONTAL) {
      
    } else if (mMirroringMode == VERTICAL) {

    }

  } else if (address >= NAMETABLE_2_START && address <= NAMETABLE_2_END) {

  } else if (address >= NAMETABLE_3_START && address <= NAMETABLE_3_END) {

  } else if (address >= NAMETABLE_4_START && address <= NAMETABLE_4_END) {

  }
}