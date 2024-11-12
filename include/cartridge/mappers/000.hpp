#pragma once
#include "cartridge/mapper.hpp"

class Mapper000 : public Mapper {
 private:
 public:
  Mapper000(uint8_t prgRomBanks, uint8_t chrRomBanks,
            MirroringMode mirroringMode)
      : Mapper(prgRomBanks, uint8_t chrRomBanks, mirroringMode) {}
};
