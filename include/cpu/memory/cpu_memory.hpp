#pragma once

#include "memory/memory.hpp"

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

struct PPURegisters {
  uint8_t& PPUCTRL;
  uint8_t& PPUMASK;
  uint8_t& PPUSTATUS;
  uint8_t& OAMADDR;
  uint8_t& OAMDATA;
  uint8_t& PPUSCROLL;
  uint8_t& PPUADDR;
  uint8_t& PPUDATA;
  uint8_t& OAMDMA;
};

class CPUMemory : public Memory {
 private:
  class RAM : public Section {
   private:
    uint8_t mMemory[RAM_MIRROR_SRC_END - RAM_MIRROR_SRC_START + 1];

   public:
    RAM()
        : Section(RAM_START, RAM_END, RAM_MIRROR_SRC_START, RAM_MIRROR_SRC_END,
                  RAM_MIRROR_DST_START, RAM_MIRROR_DST_END) {};

    ~RAM() {};

    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t value) override;
  };

  class IO : public Section {
   private:
    // PPU registers
    const struct PPURegisters mPPURegisters;

   public:
    IO(const struct PPURegisters ppuRegisters)
        : Section(IO_START, IO_END, IO_MIRROR_SRC_START, IO_MIRROR_SRC_END,
                  IO_MIRROR_DST_START, IO_MIRROR_DST_END),
          mPPURegisters(ppuRegisters) {};

    ~IO() {};

    uint8_t& getRegister(uint16_t address);

    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t value) override;
  };

  RAM mRAM;
  IO mIO;
  //   Section mExpansionROM;
  //   Section mSRAM;
  //   Section mPRGROM;

 public:
  CPUMemory(const struct PPURegisters ppuRegisters)
      : mRAM(),
        mIO(ppuRegisters)
  // mExpansionROM(EXPANSION_ROM_START, EXPANSION_ROM_END),
  // mSRAM(SRAM_START, SRAM_END),
  // mPRGROM(PRGROM_START, PRGROM_END)
  {};

  ~CPUMemory() {};

  uint8_t read(uint16_t address) override;
  void write(uint16_t address, uint8_t value) override;
};
