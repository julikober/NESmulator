#include <cstdint>
#include <iostream>

#include "cpu/cpu.hpp"
#include "memory.hpp"

int main(void) {
  CPUMemory memory = CPUMemory();
  memory.write(0x3000, 0x02);
  std::cout << "Memory at 0x0000: " << std::hex << (int)memory.read(0x2000) << std::endl;
  std::cout << "Memory at 0x0800: " << std::hex << (int)memory.read(0x2008) << std::endl;
  std::cout << "Memory at 0x1000: " << std::hex << (int)memory.read(0x2010) << std::endl;
  std::cout << "Memory at 0x1800: " << std::hex << (int)memory.read(0x4000) << std::endl;

}