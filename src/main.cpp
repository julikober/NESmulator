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
      new Mapper000(nameTablesMemory, 1, 1, HORIZONTAL, false, false, false);

  PPU ppu = PPU(&mapper);

  CPUMemoryMap cpuMemory = CPUMemoryMap(&mapper, ppu);
  CPU cpu = CPU(cpuMemory);

  // Test simple background sprite
  cpuMemory.write(0x0000, 0b10000000);
  cpuMemory.write(0x0001, 0b01000000);
  cpuMemory.write(0x0002, 0b00100000);
  cpuMemory.write(0x0003, 0b00010000);
  cpuMemory.write(0x0004, 0b00001000);
  cpuMemory.write(0x0005, 0b00000100);
  cpuMemory.write(0x0006, 0b00000010);
  cpuMemory.write(0x0007, 0b00000001);

  cpuMemory.write(0x0008, 0b00000000);
  cpuMemory.write(0x0009, 0b00000000);
  cpuMemory.write(0x000A, 0b00000000);
  cpuMemory.write(0x000B, 0b00000000);
  cpuMemory.write(0x000C, 0b00000000);
  cpuMemory.write(0x000D, 0b00000000);
  cpuMemory.write(0x000E, 0b00000000);
  cpuMemory.write(0x000F, 0b00000000);

  for (int i = 0; i < 16; i++) {
    ppu.doCycle();
  }

  return 0;
}