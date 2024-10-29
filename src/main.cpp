#include <cstdint>
#include <iostream>

#include "cpu/cpu.hpp"
#include "cpu/memory/cpu_memory.hpp"

int main(void) {
  uint8_t ppuCtrl1 = 0x00;
  uint8_t ppuCtrl2 = 0x00;
  uint8_t ppuStatus = 0x00;
  uint8_t sprRamAddr = 0x00;
  uint8_t sprRamIO = 0x00;
  uint8_t vramAddr1 = 0x00;
  uint8_t vramAddr2 = 0x00;
  uint8_t vramIO = 0x00;

  struct PPURegisters ppuRegisters = {ppuCtrl1,   ppuCtrl2, ppuStatus,
                                      sprRamAddr, sprRamIO, vramAddr1,
                                      vramAddr2,  vramIO};

  CPUMemory memory = CPUMemory(ppuRegisters);
  memory.write(0x2000, 0x02);
  memory.write(0x3509, 0x03);
  std::cout << "Memory at 0x0000: " << std::hex << (int)memory.read(0x2000)
            << std::endl;
  std::cout << "Memory at 0x0800: " << std::hex << (int)memory.read(0x2001)
            << std::endl;
  std::cout << "Memory at 0x1000: " << std::hex << (int)memory.read(0x2010)
            << std::endl;
  std::cout << "Memory at 0x1800: " << std::hex << (int)memory.read(0x3f11)
            << std::endl;
}