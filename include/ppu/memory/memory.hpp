#pragma once

#include <array>

#include "./nametables.hpp"
#include "memory/memory.hpp"

#define PATTERNTABLES_START 0x0000
#define PATTERNTABLES_END 0x1FFF

#define NAMETABLES_START 0x2000
#define NAMETABLES_END 0x3EFF
#define NAMETABLES_MIRROR_SRC_START 0x2000
#define NAMETABLES_MIRROR_SRC_END 0x2EFF
#define NAMETABLES_MIRROR_DST_START 0x3000
#define NAMETABLES_MIRROR_DST_END 0x3EFF

#define PALETTES_START 0x3F00
#define PALETTES_END 0x3FFF
#define PALETTES_MIRROR_SRC_START 0x3F00
#define PALETTES_MIRROR_SRC_END 0x3F1F
#define PALETTES_MIRROR_DST_START 0x3F20
#define PALETTES_MIRROR_DST_END 0x3FFF

class PPUMemoryMap : public MemoryMap {
 private:
  NametableMemory mNametableMemory;

 public:
  class PatternTables : public Section {};

  class NameTables : public Section {};

  class Palettes : public Section {};

  Memory *getNametableMemory() { return &mNametableMemory; }
};
