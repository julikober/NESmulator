#include "memory.hpp"

void Memory::Section::clear() {
  for (uint16_t i = 0; i < mEnd - mStart; i++) {
    data[i] = 0;
  }
}
