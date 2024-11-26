#pragma once
#include <array>
#include <cstdint>

#include "./memory/ram.hpp"
#include "./memory/rom.hpp"
#include "memory/exceptions.hpp"
#include "ppu/memory/ppu_memory.hpp"

#define PRG_ROM_BANK_SIZE 16 * 1024  // 16 KB
#define CHR_ROM_BANK_SIZE 8 * 1024   // 8 KB
#define CHR_RAM_SIZE 8 * 1024        // 8 KB

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
  ReadOnlyMemory mPrgRom;
  Memory *mChrMemory;

  // Reference to the nametable memory
  std::array<uint8_t, NAMETABLE_MEMORY_SIZE> &mNametableMemory;

  virtual uint32_t mMapPRG(uint16_t) = 0;
  virtual uint32_t mMapCHR(uint16_t) = 0;

 public:
  Mapper(uint8_t prgRomBanks, uint8_t chrRomBanks, MirroringMode mirroringMode,
         std::array<uint8_t, NAMETABLE_MEMORY_SIZE> &nametableMemory)
      : mMirroringMode(mirroringMode),
        mPrgRom(prgRomBanks * PRG_ROM_BANK_SIZE),
        mNametableMemory(nametableMemory) {
    if (chrRomBanks == 0) {
      mChrMemory = new RAM(CHR_RAM_SIZE);
    } else {
      mChrMemory = new ReadOnlyMemory(chrRomBanks * CHR_ROM_BANK_SIZE);
    }
  }

  virtual ~Mapper() { delete mChrMemory; }

  virtual uint8_t readPRG(uint16_t address) = 0;
  virtual void writePRG(uint16_t address, uint8_t value) = 0;

  virtual uint8_t readCHR(uint16_t address) = 0;
  virtual void writeCHR(uint16_t address, uint8_t value) = 0;
};
