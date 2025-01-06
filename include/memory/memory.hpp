#pragma once

#include <cstdint>

#include "exceptions.hpp"

// CPU memory map
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

// PPU memory map
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

// Specific PPU memory sections
#define PATTERNTABLE_0_START 0x0000
#define PATTERNTABLE_0_END 0x0FFF
#define PATTERNTABLE_1_START 0x1000
#define PATTERNTABLE_1_END 0x1FFF

#define NAMETABLE_SIZE 0x0400  // 1 KB

#define NAMETABLE_0_START 0x2000
#define NAMETABLE_0_END 0x23FF
#define NAMETABLE_1_START 0x2400
#define NAMETABLE_1_END 0x27FF
#define NAMETABLE_2_START 0x2800
#define NAMETABLE_2_END 0x2BFF
#define NAMETABLE_3_START 0x2C00
#define NAMETABLE_3_END 0x2FFF

enum AccessType { READ, WRITE, READ_WRITE, NONE };

class Memory {
 public:
  Memory() {};
  virtual ~Memory() {};

  virtual uint8_t read(uint32_t address) = 0;
  virtual void write(uint32_t address, uint8_t value) = 0;
};

class ReadOnlyMemory : public Memory {
 public:
  ReadOnlyMemory() : Memory() {}

  void write(uint32_t address, uint8_t value) override;
};

struct MemoryLocation {
  Memory* memory;
  uint32_t address;
};
