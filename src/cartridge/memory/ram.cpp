#include "cartridge/memory/ram.hpp"

CartridgeRAM::CartridgeRAM(uint32_t size) : Memory(), mSize(size) {
  mData = new uint8_t[size];
}

CartridgeRAM::~CartridgeRAM() { delete[] mData; }

uint8_t CartridgeRAM::read(uint32_t address) {
  return mData[address % mSize];
}

void CartridgeRAM::write(uint32_t address, uint8_t value) {
  mData[address % mSize] = value;
}

void CartridgeRAM::load(const uint8_t* data, size_t size) {
  if (size > this->size()) {
    throw std::invalid_argument("Data size exceeds RAM size");
  }

  for (size_t i = 0; i < size; i++) {
    mData[i] = data[i];
  }
}
