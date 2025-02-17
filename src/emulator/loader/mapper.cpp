#include "emulator/loader/mapper.hpp"

Mapper* createMapper(uint8_t mapperID, NameTablesMemory& nametableMemory,
                     uint8_t prgRomBanks, uint8_t chrRomBanks,
                     MirroringMode mirroringMode, bool hasBatteryBackedRam,
                     bool hasTrainer, bool hasAlternativeMirroring) {
  switch (mapperID) {
    case 0:
      return new Mapper000(nametableMemory, prgRomBanks, chrRomBanks,
                           mirroringMode, hasBatteryBackedRam, hasTrainer,
                           hasAlternativeMirroring);
    default:
      throw std::invalid_argument("Invalid mapper ID");
  }
}
