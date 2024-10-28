#pragma once

#include <cstdint>
#include <iostream>

class Memory {
 public:
  Memory() {};
  ~Memory() {};

  class Section {
   private:
    uint16_t mStart;
    uint16_t mEnd;

    struct Mirror {
      uint16_t srcStart;
      uint16_t srcEnd;
      uint16_t dstStart;
      uint16_t dstEnd;
    } mirror;

    uint8_t* data;

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
      mirror.srcStart = start;
      mirror.srcEnd = end;
      mirror.dstStart = start;
      mirror.dstEnd = end;

      data = new uint8_t[end - start];
    };

    Section(uint16_t start, uint16_t end, uint16_t mirrorSrcStart,
            uint16_t mirrorSrcEnd, uint16_t mirrorDstStart,
            uint16_t mirrorDstEnd)
        : mStart(start), mEnd(end) {
      mirror.srcStart = mirrorSrcStart;
      mirror.srcEnd = mirrorSrcEnd;
      mirror.dstStart = mirrorDstStart;
      mirror.dstEnd = mirrorDstEnd;

      data = new uint8_t[end - start];
    };

    ~Section() { delete[] data; };

    void clear();

    inline uint8_t read(uint16_t address) {
      return data[mResolveMirrors(address) - mStart];
    };

    inline void write(uint16_t address, uint8_t value) {
      data[mResolveMirrors(address) - mStart] = value;
    };
  };

  virtual void clear() = 0;

  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
};
