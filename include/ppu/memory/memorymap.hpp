#pragma once

#include <array>

#include "./nametables.hpp"
#include "./palettes.hpp"
#include "cartridge/mapper/mapper.hpp"
#include "memory/memorymap.hpp"

class PPUMemoryMap : public MemoryMap {
 private:
  class PatternTablesSection : public Section {
   public:
    PatternTablesSection(Mapper** mapper);

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  class NameTablesSection : public Section {
   public:
    NameTablesSection(Mapper** mapper);

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  class PalettesSection : public Section {
   private:
    PalettesMemory mMemory;

   public:
    PalettesSection(Mapper** mapper);

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;

    void load(const uint8_t* data, size_t size);
  };

  PatternTablesSection mPatternTablesSection;
  NameTablesSection mNameTablesSection;
  PalettesSection mPalettesSection;

 public:
  PPUMemoryMap(Mapper** mapper);

  virtual uint8_t read(uint16_t address) override;
  virtual void write(uint16_t address, uint8_t value) override;
};
