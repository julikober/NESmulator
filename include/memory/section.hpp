#pragma once

#include <cstdint>

#include "cartridge/mapper/mapper.hpp"

class Section {
 protected:
  Mapper** mMapper;

  uint16_t mStart;
  uint16_t mEnd;

  struct Mirror {
    uint16_t srcStart;
    uint16_t srcEnd;
    uint16_t dstStart;
    uint16_t dstEnd;
  } mirror;

  // Resolve mirror addresses
  uint16_t mResolveMirrors(uint16_t address);

 public:
  Section(Mapper** mapper, uint16_t start, uint16_t end);
  Section(Mapper** mapper, uint16_t start, uint16_t end,
          uint16_t mirrorSrcStart, uint16_t mirrorSrcEnd,
          uint16_t mirrorDstStart, uint16_t mirrorDstEnd);

  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
};