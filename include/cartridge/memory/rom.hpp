#pragma once

#include "memory/memory.hpp"

class CartridgeROM : public ReadOnlyMemory {
 private:
  uint8_t* mData;
  uint32_t mSize;

 public:
  CartridgeROM(uint32_t size) : ReadOnlyMemory(), mSize(size) {
    mData = new uint8_t[size];
  }

  ~CartridgeROM() { delete[] mData; }

  virtual inline uint8_t read(uint32_t address) override {
    return mData[address % mSize];
  }
};
