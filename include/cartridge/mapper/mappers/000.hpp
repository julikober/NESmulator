#pragma once

#include "cartridge/mapper/mapper.hpp"

#define MAP000_PRG_RAM_SIZE 8 * 1024  // 8 KB

#define MAP000_PRG_ROM_START 0x8000
#define MAP000_PRG_ROM_END 0xFFFF

#define MAP000_PRG_RAM_START 0x6000
#define MAP000_PRG_RAM_END 0x7FFF

class Mapper000 : public Mapper {
 private:
  CartridgeRAM mPrgRam;

  virtual MemoryLocation mMapPRG(uint16_t address) override;
  virtual MemoryLocation mMapCHR(uint16_t address) override;

 public:
  Mapper000(NameTablesMemory& nametableMemory, uint8_t prgRomBanks,
            uint8_t chrRomBanks, MirroringMode mirroringMode,
            bool hasBatteryBackedRam, bool hasTrainer,
            bool hasAlternativeMirroring);
};
