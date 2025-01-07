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

  cpuMemory.write(0x0000, 0xA9);
  cpuMemory.write(0x0001, 0x01);
  cpuMemory.write(0x0002, 0x69);
  cpuMemory.write(0x0003, 0x02);

  cpuMemory.write(0x0004, 0x85);
  cpuMemory.write(0x0005, 0x00);

  for (int i = 0; i < 20; i++) {
    cpu.doCycle();
  }

  // Print hex value of 0x0000
  std::cout << std::hex << (int)cpuMemory.read(0x0000) << std::endl;


  // PPU ppu = PPU();

  // CPUMemoryMap memory = CPUMemoryMap(ppu);
  // memory.write(0x2002, 0x02);
  // memory.write(0x200a, 0x03);

  // Logger.log("Memory written", INFO);

  return 0;
}