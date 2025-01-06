#include <cstdint>
#include <iostream>

#include "cpu/cpu.hpp"
#include "cpu/memory/memorymap.hpp"
#include "ppu/memory/memorymap.hpp"
#include "logger/logger.hpp"
#include "cartridge/mapper/mappers/000.hpp"

int main(void) {
  Logger& Logger = Logger::getInstance();

  NameTablesMemory nameTables = NameTablesMemory();

  Mapper* mapper = new Mapper000(nameTables, 2, 1, HORIZONTAL, false, false, false);

  PPUMemoryMap ppuMemory = PPUMemoryMap(&mapper);

  ppuMemory.write(0x0000, 0xff);
  ppuMemory.write(0x2400, 0xff);


  // PPU ppu = PPU();

  // CPUMemoryMap memory = CPUMemoryMap(ppu);
  // memory.write(0x2002, 0x02);
  // memory.write(0x200a, 0x03);

  // Logger.log("Memory written", INFO);

  return 0;
}