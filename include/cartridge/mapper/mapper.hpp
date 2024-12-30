#pragma once

#include <array>
#include <cstdint>

#include "./exceptions.hpp"
#include "../memory/ram.hpp"
#include "../memory/rom.hpp"
#include "logger/logger.hpp"
#include "memory/exceptions.hpp"
#include "ppu/memory/memory.hpp"
#include "cpu/memory/memory.hpp"

#define PRG_ROM_BANK_SIZE 16 * 1024  // 16 KB
#define CHR_ROM_BANK_SIZE 8 * 1024   // 8 KB
#define CHR_RAM_SIZE 8 * 1024        // 8 KB

#define PATTERNTABLE_0_START 0x0000
#define PATTERNTABLE_0_END 0x0FFF
#define PATTERNTABLE_1_START 0x1000
#define PATTERNTABLE_1_END 0x1FFF

#define NAMETABLE_SIZE 0x0400  // 1 KB

#define NAMETABLE_0_START 0x2000
#define NAMETABLE_0_END 0x23FF
#define NAMETABLE_1_START 0x2400
#define NAMETABLE_1_END 0x27FF
#define NAMETABLE_2_START 0x2800
#define NAMETABLE_2_END 0x2BFF
#define NAMETABLE_3_START 0x2C00
#define NAMETABLE_3_END 0x2FFF

enum MirroringMode { HORIZONTAL, VERTICAL };

enum NameTable { NAMETABLE_1, NAMETABLE_2, NAMETABLE_3, NAMETABLE_4 };

class Mapper {
 protected:
  MirroringMode mMirroringMode;

  // PRG ROM
  CartridgeROM mPrgRom;

  // CHR ROM or CHR RAM, evaluated at runtime
  Memory *mChrMemory;

  // Reference to the nametable memory
  NametableMemory &mNametableMemory;

  bool mHasAlternativeMirroring;

  MemoryLocation mMapNametableMirrors(uint16_t address);
  virtual MemoryLocation mMapAlternativeMirrors(uint16_t address);

  virtual MemoryLocation mMapPRG(uint16_t) = 0;
  virtual MemoryLocation mMapCHR(uint16_t) = 0;

 public:
  Mapper(NametableMemory &nametableMemory, uint8_t prgRomBanks,
         uint8_t chrRomBanks, MirroringMode mirroringMode,
         bool hasBatteryBackedRam, bool hasTrainer,
         bool hasAlternativeMirroring)
      : mNametableMemory(nametableMemory),
        mPrgRom(prgRomBanks * PRG_ROM_BANK_SIZE),
        mMirroringMode(mirroringMode),
        mHasAlternativeMirroring(hasAlternativeMirroring) {
    if (chrRomBanks > 0) {
      mChrMemory = new CartridgeROM(chrRomBanks * CHR_ROM_BANK_SIZE);
    } else {
      mChrMemory = new CartridgeRAM(CHR_RAM_SIZE);
    }
  }

  virtual ~Mapper() { delete mChrMemory; }

  virtual uint8_t readPRG(uint16_t address);
  virtual void writePRG(uint16_t address, uint8_t value);

  virtual uint8_t readCHR(uint16_t address);
  virtual void writeCHR(uint16_t address, uint8_t value);
};
