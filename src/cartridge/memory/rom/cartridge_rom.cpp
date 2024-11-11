#include "cartridge/memory/rom/cartridge_rom.hpp"

#include "memory/exceptions.hpp"

void CartridgeROM::write(uint16_t address, uint8_t value) {
  throw ReadOnlyException("ROM is read-only");
}
