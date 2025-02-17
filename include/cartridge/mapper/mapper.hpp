#pragma once

#include <array>
#include <cstdint>

#include "../memory/ram.hpp"
#include "../memory/rom.hpp"
#include "./exceptions.hpp"
#include "logger/logger.hpp"
#include "memory/exceptions.hpp"
#include "ppu/memory/nametables.hpp"

#define PRG_ROM_BANK_SIZE 16 * 1024  // 16 KB
#define CHR_ROM_BANK_SIZE 8 * 1024   // 8 KB
#define CHR_RAM_SIZE 8 * 1024        // 8 KB

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
  NameTablesMemory &mNametableMemory;

  bool mHasAlternativeMirroring;

  MemoryLocation mMapNametableMirrors(uint16_t address);
  virtual MemoryLocation mMapAlternativeMirrors(uint16_t address);

  virtual MemoryLocation mMapPRG(uint16_t) = 0;
  virtual MemoryLocation mMapCHR(uint16_t) = 0;

 public:
  Mapper(NameTablesMemory &nametableMemory, uint8_t prgRomBanks,
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

  void loadPRGROM(const uint8_t *data, size_t size);
  void loadCHR(const uint8_t *data, size_t size);
};
