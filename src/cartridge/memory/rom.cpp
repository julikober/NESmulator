#include "cartridge/memory/rom.hpp"

void CartridgeROM::load(const uint8_t* data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds ROM size");
  }

  for (size_t i = 0; i < size; i++) {
    mData[i] = data[i];
  }
}
