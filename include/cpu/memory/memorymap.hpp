#pragma once

#include <array>

#include "./ram.hpp"
#include "memory/memorymap.hpp"
#include "ppu/ppu.hpp"

class CPUMemoryMap : public MemoryMap {
 private:
  // RAM
  class RAMSection : public Section {
   private:
    RAM mMemory;

   public:
    RAMSection(Mapper** mapper)
        : Section(mapper, RAM_START, RAM_END, RAM_MIRROR_SRC_START,
                  RAM_MIRROR_SRC_END, RAM_MIRROR_DST_START,
                  RAM_MIRROR_DST_END) {};

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
    IOSection(Mapper** mapper, PPU& ppu)
        : Section(mapper, IO_START, IO_END, IO_MIRROR_SRC_START,
                  IO_MIRROR_SRC_END, IO_MIRROR_DST_START, IO_MIRROR_DST_END),
          mPPU(ppu) {};

    ~IOSection() {};

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  class CartridgeSection : public Section {
   public:
    CartridgeSection(Mapper** mapper)
        : Section(mapper, CARTRIDGE_START, CARTRIDGE_END) {};

    ~CartridgeSection() {};

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  RAMSection mRAM;
  IOSection mIO;
  CartridgeSection mCartridge;

 public:
  CPUMemoryMap(Mapper** mapper, PPU& ppu)
      : MemoryMap(mapper), mRAM(mapper), mIO(mapper, ppu), mCartridge(mapper) {};

  ~CPUMemoryMap() {};

  virtual uint8_t read(uint16_t address) override;
  virtual void write(uint16_t address, uint8_t value) override;
};
