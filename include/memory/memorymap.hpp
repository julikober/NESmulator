#pragma once

#include "./memory.hpp"
#include "./section.hpp"
#include "cartridge/mapper/mapper.hpp"

class MemoryMap {
 protected:
  Mapper** mMapper;

 public:
  MemoryMap(Mapper** mapper);

  virtual uint8_t read(uint16_t address) = 0;
  virtual void write(uint16_t address, uint8_t value) = 0;
};
