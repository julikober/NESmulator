#pragma once

#include <cstdint>

#include "exceptions.hpp"

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
  Memory *memory;
  uint32_t address;
};

class MemoryMap {
 public:
  MemoryMap() {};
  virtual ~MemoryMap() {};

  class Section {
   protected:
    uint16_t mStart;
    uint16_t mEnd;

    struct Mirror {
      uint16_t srcStart;
      uint16_t srcEnd;
      uint16_t dstStart;
      uint16_t dstEnd;
    } mirror;

    // Resolve mirror addresses
    uint16_t mResolveMirrors(uint16_t address) {
      if (address >= mirror.dstStart && address <= mirror.dstEnd) {
        return mirror.srcStart + (address - mirror.dstStart) %
                                     (mirror.srcEnd - mirror.srcStart + 1);
      } else if (address >= mStart && address <= mEnd) {
        return address;
      } else {
        return 0;
      }
    }

   public:
    Section(uint16_t start, uint16_t end) : mStart(start), mEnd(end) {
      mirror.srcStart = 0;
      mirror.srcEnd = 0;
      mirror.dstStart = 0;
      mirror.dstEnd = 0;
    };

    Section(uint16_t start, uint16_t end, uint16_t mirrorSrcStart,
            uint16_t mirrorSrcEnd, uint16_t mirrorDstStart,
            uint16_t mirrorDstEnd)
        : mStart(start), mEnd(end) {
      mirror.srcStart = mirrorSrcStart;
      mirror.srcEnd = mirrorSrcEnd;
      mirror.dstStart = mirrorDstStart;
      mirror.dstEnd = mirrorDstEnd;
    };

    virtual ~Section() {};

    // void clear();

    virtual uint8_t read(uint16_t address) = 0;
    virtual void write(uint16_t address, uint8_t value) = 0;
  };

  // virtual void clear() = 0;

  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
};
