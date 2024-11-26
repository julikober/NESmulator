#pragma once

#include "memory/memory.hpp"

class CartridgeRAM : public Memory {
 private:
  uint8_t* mData;
  uint32_t mSize;

 public:
  CartridgeRAM(uint32_t size) : Memory(), mSize(size) {
    mData = new uint8_t[size];
  }

  ~CartridgeRAM() { delete[] mData; }

  virtual inline uint8_t read(uint32_t address) override {
    return mData[address];
  }

  virtual inline void write(uint32_t address, uint8_t value) override {
    mData[address] = value;
  }
};
