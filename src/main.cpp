#include <cstdint>
#include <iostream>

#include "cpu/cpu.hpp"
#include "cpu/memory/cpu_memory.hpp"
#include "logger/logger.hpp"

int main(void) {
  Logger& Logger = Logger::getInstance();

  PPU ppu = PPU();

  CPUMemoryMap memory = CPUMemoryMap(ppu);
  memory.write(0x2002, 0x02);
  memory.write(0x200a, 0x03);

  Logger.log("Memory written", INFO);

  return 0;
}