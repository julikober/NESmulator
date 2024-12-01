#include "cartridge/mapper.hpp"

uint8_t Mapper::readPRG(uint16_t address) {
  MemoryLocation location = mMapPRG(address);
  return location.memory->read(location.address);
};

void Mapper::writePRG(uint16_t address, uint8_t value) {
  MemoryLocation location = mMapPRG(address);
  location.memory->write(location.address, value);
};

uint8_t Mapper::readCHR(uint16_t address) {
  MemoryLocation location = mMapCHR(address);
  return location.memory->read(location.address);
};

void Mapper::writeCHR(uint16_t address, uint8_t value) {
  MemoryLocation location = mMapCHR(address);
  location.memory->write(location.address, value);
};
