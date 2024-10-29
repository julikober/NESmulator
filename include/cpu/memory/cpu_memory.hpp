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
  uint8_t& ppuCtrl1;
  uint8_t& ppuCtrl2;
  uint8_t& ppuStatus;
  uint8_t& sprRamAddr;
  uint8_t& sprRamIO;
  uint8_t& vramAddr1;
  uint8_t& vramAddr2;
  uint8_t& vramIO;
};

class CPUMemory : public Memory {
 private:
  class RAM : public Section {
   private:
    uint8_t mMemory[RAM_MIRROR_SRC_END - RAM_MIRROR_SRC_START + 1];

   public:
    RAM(uint16_t start, uint16_t end)
        : Section(start, end, RAM_MIRROR_SRC_START, RAM_MIRROR_SRC_END,
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
    IO(uint16_t start, uint16_t end, uint16_t mirrorSrcStart,
       uint16_t mirrorSrcEnd, uint16_t mirrorDstStart, uint16_t mirrorDstEnd,
       const struct PPURegisters ppuRegisters)
        : Section(start, end, mirrorSrcStart, mirrorSrcEnd, mirrorDstStart,
                  mirrorDstEnd),
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
      : mRAM(RAM_START, RAM_END),
        mIO(IO_START, IO_END, IO_MIRROR_SRC_START, IO_MIRROR_SRC_END,
            IO_MIRROR_DST_START, IO_MIRROR_DST_END, ppuRegisters)
  // mExpansionROM(EXPANSION_ROM_START, EXPANSION_ROM_END),
  // mSRAM(SRAM_START, SRAM_END),
  // mPRGROM(PRGROM_START, PRGROM_END)
  {};

  ~CPUMemory() {};

  uint8_t read(uint16_t address) override;
  void write(uint16_t address, uint8_t value) override;
};
