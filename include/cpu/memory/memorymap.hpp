#pragma once

#include <array>

#include "./ram.hpp"
#include "memory/memorymap.hpp"
#include "ppu/ppu.hpp"

#define ADDR_PPUCTRL 0x2000
#define ADDR_PPUMASK 0x2001
#define ADDR_PPUSTATUS 0x2002
#define ADDR_OAMADDR 0x2003
#define ADDR_OAMDATA 0x2004
#define ADDR_PPUSCROLL 0x2005
#define ADDR_PPUADDR 0x2006
#define ADDR_PPUDATA 0x2007
#define ADDR_OAMDMA 0x4014

class PPU;

class CPUMemoryMap : public MemoryMap {
 private:
  // RAM
  class RAMSection : public Section {
   private:
    RAM mMemory;

   public:
    RAMSection(Mapper** mapper);

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
    void load(const uint8_t* data, size_t size);
  };

  // IO registers
  class IOSection : public Section {
   private:
    // PPU reference
    PPU* mPPU;

   public:
    IOSection(Mapper** mapper, PPU* ppu);

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  class CartridgeSection : public Section {
   public:
    CartridgeSection(Mapper** mapper);

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  RAMSection mRAM;
  IOSection mIO;
  CartridgeSection mCartridge;

 public:
  CPUMemoryMap(Mapper** mapper, PPU* ppu);

  virtual uint8_t read(uint16_t address) override;
  virtual void write(uint16_t address, uint8_t value) override;
};
