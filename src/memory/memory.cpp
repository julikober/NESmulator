#include "memory/memory.hpp"

void ReadOnlyMemory::write(uint32_t address, uint8_t value) {
  throw InvalidAccessTypeException("ROM is read-only");
}
