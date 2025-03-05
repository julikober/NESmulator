#include <cstdint>
#include <iostream>

#include "cartridge/mapper/mappers/000.hpp"
#include "cpu/cpu.hpp"
#include "cpu/memory/memorymap.hpp"
#include "logger/logger.hpp"
#include "ppu/memory/memorymap.hpp"

int main(void) {
  Logger& Logger = Logger::getInstance();

  NameTablesMemory nameTablesMemory = NameTablesMemory();

  Mapper* mapper =
      new Mapper000(nameTablesMemory, 1, 1, VERTICAL, false, false, false);

  PPU* ppu;
  CPU* cpu;

  cpu = new CPU(&mapper, ppu);
  ppu = new PPU(&mapper, cpu);

  uint8_t data[] = {0b10000100, 0b01000000, 0b00100000, 0b00010000,
                    0b00001000, 0b00000100, 0b00000010, 0b00000001,

                    0b00001100, 0b00000000, 0b00000000, 0b00000000,
                    0b00000000, 0b00000000, 0b00000000, 0b00000000};

  mapper->loadCHRROM(data, 16);

  for (int i = 0; i < 24; i++) {
    ppu->doCycle();
  }

  return 0;
}