#pragma once

#include "memory.hpp"

#define RAM_START 0x0000
#define RAM_END 0x1FFF
#define RAM_MIRROR_SRC_START 0x0000
#define RAM_MIRROR_SRC_END 0x07FF
#define RAM_MIRROR_DST_START 0x0800
#define RAM_MIRROR_DST_END 0x1FFF

#define IO_START 0x2000
#define IO_END 0x401F
#define IO_MIRROR_SRC_START 0x2000
#define IO_MIRROR_SRC_END 0x2007
#define IO_MIRROR_DST_START 0x2008
#define IO_MIRROR_DST_END 0x3FFF

#define EXPANSION_ROM_START 0x4020
#define EXPANSION_ROM_END 0x5FFF

#define SRAM_START 0x6000
#define SRAM_END 0x7FFF

#define PRGROM_START 0x8000
#define PRGROM_END 0xFFFF

class CPUMemory : Memory {
 private:
  Section mRAM;
  Section mIO;
  Section mExpansionROM;
  Section mSRAM;
  Section mPRGROM;

 public:
  CPUMemory()
      : mRAM(RAM_START, RAM_END, RAM_MIRROR_SRC_START, RAM_MIRROR_SRC_END,
             RAM_MIRROR_DST_START, RAM_MIRROR_DST_END),
        mIO(IO_START, IO_END, IO_MIRROR_SRC_START, IO_MIRROR_SRC_END,
            IO_MIRROR_DST_START, IO_MIRROR_DST_END),
        mExpansionROM(EXPANSION_ROM_START, EXPANSION_ROM_END),
        mSRAM(SRAM_START, SRAM_END),
        mPRGROM(PRGROM_START, PRGROM_END) {};

  ~CPUMemory() {};

  void clear();

  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t value);
};
