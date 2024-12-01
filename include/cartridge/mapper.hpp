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

#define NAMETABLE_1_START 0x2000
#define NAMETABLE_1_END 0x23FF
#define NAMETABLE_2_START 0x2400
#define NAMETABLE_2_END 0x27FF
#define NAMETABLE_3_START 0x2800
#define NAMETABLE_3_END 0x2BFF
#define NAMETABLE_4_START 0x2C00
#define NAMETABLE_4_END 0x2FFF

enum MirroringMode {
  HORIZONTAL,
  VERTICAL
};

enum NameTable {
  NAMETABLE_1,
  NAMETABLE_2,
  NAMETABLE_3,
  NAMETABLE_4
};

class Mapper {
 protected:
  MirroringMode mMirroringMode;

  // PRG ROM
  CartridgeROM mPrgRom;

  // Reference to the nametable memory
  NametableMemory &mNametableMemory;

  virtual MemoryLocation mMapPRG(uint16_t) = 0;
  virtual MemoryLocation mMapCHR(uint16_t) = 0;

 public:
  Mapper(uint8_t prgRomBanks, MirroringMode mirroringMode,
         NametableMemory &nametableMemory)
      : mMirroringMode(mirroringMode),
        mPrgRom(prgRomBanks * PRG_ROM_BANK_SIZE),
        mNametableMemory(nametableMemory) {}

  virtual ~Mapper() {}

  virtual uint8_t readPRG(uint16_t address);
  virtual void writePRG(uint16_t address, uint8_t value);

  virtual uint8_t readCHR(uint16_t address);
  virtual void writeCHR(uint16_t address, uint8_t value);
};
