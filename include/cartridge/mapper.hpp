#pragma once
#include <cstdint>

#include "memory/ram/cartridge_ram.hpp"
#include "memory/rom/cartridge_rom.hpp"

#define PRG_ROM_BANK_SIZE 16 * 1024

enum MirroringMode {
  HORIZONTAL,
  VERTICAL,
  FOUR_SCREEN,
  SINGLE_SCREEN

  // TODO: Add more mirroring modes
};

class Mapper {
 protected:
  MirroringMode mMirroringMode;
  CartridgeROM mPrgRom;
  CartridgeMemory *mChrMemory;

 public:
  Mapper(uint8_t prgRomBanks, uint8_t chrRomBanks, MirroringMode mirroringMode)
      : mMirroringMode(mirroringMode),
        mPrgRom(prgRomBanks * PRG_ROM_BANK_SIZE) {
    if (chrRomBanks == 0) {
      mChrMemory = new CartridgeRAM(8 * 1024);
    } else {
      mChrMemory = new CartridgeROM(chrRomBanks * 8 * 1024);
    }
  }

  virtual ~Mapper() { delete mChrMemory; }

  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
};
