#include <cstdint>
#include <iostream>

#include "cpu/cpu.hpp"
#include "cpu/memory/cpu_memory.hpp"
#include "logger/logger.hpp"

int main(void) {
  Logger& Logger = Logger::getInstance();
  
  uint8_t ppuCtrl1 = 0x00;
  uint8_t ppuCtrl2 = 0x00;
  uint8_t ppuStatus = 0x00;
  uint8_t sprRamAddr = 0x00;
  uint8_t sprRamIO = 0x00;
  uint8_t vramAddr1 = 0x00;
  uint8_t vramAddr2 = 0x00;
  uint8_t vramIO = 0x00;
  uint8_t oamDMA = 0x00;

  struct PPURegisters ppuRegisters = {ppuCtrl1,   ppuCtrl2, ppuStatus,
                                      sprRamAddr, sprRamIO, vramAddr1,
                                      vramAddr2,  vramIO,   oamDMA};

  CPUMemory memory = CPUMemory(ppuRegisters);
  memory.write(0x1000, 0x02);
  memory.write(0x3509, 0x03);

  Logger.log("Memory written", INFO);

  return 0;
}