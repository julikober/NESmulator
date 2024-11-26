#pragma once
#include "cartridge/mapper.hpp"

class Mapper000 : public Mapper {
 private:
  virtual uint32_t mMapPRG(uint16_t) override;

 public:
  Mapper000(uint8_t prgRomBanks, uint8_t chrRomBanks,
            MirroringMode mirroringMode, std::array<uint8_t, NAMETABLE_MEMORY_SIZE> &nametableMemory)
      : Mapper(prgRomBanks, chrRomBanks, mirroringMode, nametableMemory) {}

  
};
