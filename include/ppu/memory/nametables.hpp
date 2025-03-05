#pragma once

#include <array>

#include "memory/memory.hpp"

#define NAMETABLES_SIZE 0x0800  // 2 KB

class NameTablesMemory : public Memory {
 private:
  std::array<uint8_t, NAMETABLES_SIZE> mMemory;

 public:
  NameTablesMemory();

  virtual uint8_t read(uint32_t address) override;
  virtual void write(uint32_t address, uint8_t value) override;

  virtual void load(const uint8_t *data, size_t size) override;

  virtual inline size_t size() override { return NAMETABLES_SIZE; }
};