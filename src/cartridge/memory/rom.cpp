#include "cartridge/memory/rom.hpp"

CartridgeROM::CartridgeROM(uint32_t size) : ReadOnlyMemory(), mSize(size) {
  mData = new uint8_t[size];
}

CartridgeROM::~CartridgeROM() { delete[] mData; }

uint8_t CartridgeROM::read(uint32_t address) {
  return mData[address % mSize];
}

void CartridgeROM::load(const uint8_t* data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds ROM size");
  }

  for (size_t i = 0; i < size; i++) {
    mData[i] = data[i];
  }
}
