#pragma once

#include <array>

#include "memory/memory.hpp"

#define PATTERN_TABLES_START 0x0000
#define PATTERN_TABLES_END 0x1FFF

#define NAME_TABLES_START 0x2000
#define NAME_TABLES_END 0x3EFF
#define NAME_TABLES_MIRROR_SRC_START 0x2000
#define NAME_TABLES_MIRROR_SRC_END 0x2EFF
#define NAME_TABLES_MIRROR_DST_START 0x3000
#define NAME_TABLES_MIRROR_DST_END 0x3EFF

#define PALETTES_START 0x3F00
#define PALETTES_END 0x3FFF
#define PALETTES_MIRROR_SRC_START 0x3F00
#define PALETTES_MIRROR_SRC_END 0x3F1F
#define PALETTES_MIRROR_DST_START 0x3F20
#define PALETTES_MIRROR_DST_END 0x3FFF

#define NAMETABLE_MEMORY_SIZE 0x0800  // 2 KB

class NametableMemory : public Memory {
 private:
  std::array<uint8_t, NAMETABLE_MEMORY_SIZE> mMemory;

 public:
  NametableMemory() : Memory() {}
  ~NametableMemory() {}

  virtual inline uint8_t read(uint32_t address) override {
    return mMemory[address];
  }
  virtual inline void write(uint32_t address, uint8_t value) override {
    mMemory[address] = value;
  }
};

class PPUMemoryMap : public MemoryMap {
 private:
  NametableMemory mNametableMemory;

 public:
  class PatternTables : public Section {};

  class NameTables : public Section {};

  class Palettes : public Section {};

  Memory *getNametableMemory() { return &mNametableMemory; }
};
