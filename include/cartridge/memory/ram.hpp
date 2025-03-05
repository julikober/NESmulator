#pragma once

#include "memory/memory.hpp"

class CartridgeRAM : public Memory {
 private:
  uint8_t* mData;
  size_t mSize;

 public:
  CartridgeRAM(uint32_t size);
  ~CartridgeRAM();

  virtual uint8_t read(uint32_t address) override;
  virtual void write(uint32_t address, uint8_t value);

  virtual void load(const uint8_t* data, size_t size) override;

  virtual inline size_t size() override { return mSize; }
};
