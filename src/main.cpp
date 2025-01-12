#include <cstdint>
#include <iostream>

#include "cpu/cpu.hpp"
#include "cpu/memory/memorymap.hpp"
#include "ppu/memory/memorymap.hpp"
#include "logger/logger.hpp"
#include "cartridge/mapper/mappers/000.hpp"

int main(void) {
  Logger& Logger = Logger::getInstance();

  NameTablesMemory nameTablesMemory = NameTablesMemory();

  Mapper* mapper = new Mapper000(nameTablesMemory, 1, 1, HORIZONTAL, false, false, false);

  PPU ppu = PPU(&mapper);

  CPUMemoryMap cpuMemory = CPUMemoryMap(&mapper, ppu);
  CPU cpu = CPU(cpuMemory);

  cpuMemory.write(0x0400, 0xA9);
  cpuMemory.write(0x0401, 0x01);
  cpuMemory.write(0x0402, 0x69);
  cpuMemory.write(0x0403, 0x02);

  cpuMemory.write(0x0404, 0x8D);
  cpuMemory.write(0x0405, 0x00);
  cpuMemory.write(0x0406, 0x04);

  for (int i = 0; i < 10; i++) {
    cpu.doCycle();
  }

  // Print hex value of 0x0000
  std::cout << std::hex << (int)cpuMemory.read(0x0400) << std::endl;


  // PPU ppu = PPU();

  // CPUMemoryMap memory = CPUMemoryMap(ppu);
  // memory.write(0x2002, 0x02);
  // memory.write(0x200a, 0x03);

  // Logger.log("Memory written", INFO);

  return 0;
}