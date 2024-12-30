#pragma once

#include <array>

#include "./ram.hpp"
#include "memory/memory.hpp"
#include "ppu/ppu.hpp"

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

class CPUMemoryMap : public MemoryMap {
 private:
  // RAM
  class RAMSection : public Section {
   private:
    RAM mRAM;

   public:
    RAMSection()
        : Section(RAM_START, RAM_END, RAM_MIRROR_SRC_START, RAM_MIRROR_SRC_END,
                  RAM_MIRROR_DST_START, RAM_MIRROR_DST_END) {};

    ~RAMSection() {};

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  // IO registers
  class IOSection : public Section {
   private:
    // PPU reference
    PPU& mPPU;

   public:
    IOSection(PPU& ppu)
        : Section(IO_START, IO_END, IO_MIRROR_SRC_START, IO_MIRROR_SRC_END,
                  IO_MIRROR_DST_START, IO_MIRROR_DST_END),
          mPPU(ppu) {};

    ~IOSection() {};

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  RAMSection mRAM;
  IOSection mIO;

 public:
  CPUMemoryMap(PPU& ppu) : mRAM(), mIO(ppu) {};

  ~CPUMemoryMap() {};

  virtual uint8_t read(uint16_t address) override;
  virtual void write(uint16_t address, uint8_t value) override;
};
