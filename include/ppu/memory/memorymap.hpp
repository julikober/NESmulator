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
    PatternTablesSection(Mapper** mapper)
        : Section(mapper, PATTERNTABLES_START, PATTERNTABLES_END) {};

    ~PatternTablesSection() {};

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  class NameTablesSection : public Section {
   public:
    NameTablesSection(Mapper** mapper)
        : Section(mapper, NAMETABLES_START, NAMETABLES_END,
                  NAMETABLES_MIRROR_SRC_START, NAMETABLES_MIRROR_SRC_END,
                  NAMETABLES_MIRROR_DST_START, NAMETABLES_MIRROR_DST_END) {};

    ~NameTablesSection() {};

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  class PalettesSection : public Section {
   private:
    PalettesMemory mMemory;

   public:
    PalettesSection(Mapper** mapper)
        : Section(mapper, PALETTES_START, PALETTES_END,
                  PALETTES_MIRROR_SRC_START, PALETTES_MIRROR_SRC_END,
                  PALETTES_MIRROR_DST_START, PALETTES_MIRROR_DST_END) {};

    ~PalettesSection() {};

    virtual uint8_t read(uint16_t address) override;
    virtual void write(uint16_t address, uint8_t value) override;
  };

  PatternTablesSection mPatternTablesSection;
  NameTablesSection mNameTablesSection;
  PalettesSection mPalettesSection;

 public:
  PPUMemoryMap(Mapper** mapper)
      : MemoryMap(mapper),
        mPatternTablesSection(mapper),
        mNameTablesSection(mapper),
        mPalettesSection(mapper) {}
  ~PPUMemoryMap() {}

  virtual uint8_t read(uint16_t address) override;
  virtual void write(uint16_t address, uint8_t value) override;
};
