#pragma once

#include "memory/memory.hpp"

class CartridgeROM : public ReadOnlyMemory {
 private:
  uint8_t* mData;
  size_t mSize;

 public:
  CartridgeROM(uint32_t size);
  ~CartridgeROM();

  virtual uint8_t read(uint32_t address) override;

  virtual inline size_t size() override { return mSize; }
  virtual void load(const uint8_t* data, size_t size) override;
};
