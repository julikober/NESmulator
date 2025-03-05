#include "memory/section.hpp"

Section::Section(Mapper** mapper, uint16_t start, uint16_t end)
    : mMapper(mapper), mStart(start), mEnd(end) {
  mirror.srcStart = 0;
  mirror.srcEnd = 0;
  mirror.dstStart = 0;
  mirror.dstEnd = 0;
}

Section::Section(Mapper** mapper, uint16_t start, uint16_t end,
                 uint16_t mirrorSrcStart, uint16_t mirrorSrcEnd,
                 uint16_t mirrorDstStart, uint16_t mirrorDstEnd)
    : mMapper(mapper), mStart(start), mEnd(end) {
  mirror.srcStart = mirrorSrcStart;
  mirror.srcEnd = mirrorSrcEnd;
  mirror.dstStart = mirrorDstStart;
  mirror.dstEnd = mirrorDstEnd;
}

uint16_t Section::mResolveMirrors(uint16_t address) {
  if (address >= mirror.dstStart && address <= mirror.dstEnd) {
    return mirror.srcStart +
           (address - mirror.dstStart) % (mirror.srcEnd - mirror.srcStart + 1);
  } else if (address >= mStart && address <= mEnd) {
    return address;
  } else {
    return 0;
  }
}
