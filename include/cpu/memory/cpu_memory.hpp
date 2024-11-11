#pragma once

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
    // PPU reference
    PPU& mPPU;

   public:
    IO(PPU& ppu)
        : Section(IO_START, IO_END, IO_MIRROR_SRC_START, IO_MIRROR_SRC_END,
                  IO_MIRROR_DST_START, IO_MIRROR_DST_END),
          mPPU(ppu) {};

    ~IO() {};

    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t value) override;
  };

  RAM mRAM;
  IO mIO;

 public:
  CPUMemory(PPU& ppu) : mRAM(), mIO(ppu) {};

  ~CPUMemory() {};

  uint8_t read(uint16_t address) override;
  void write(uint16_t address, uint8_t value) override;
};
