#include <iostream>
#include <cstdint>
#include "memory.hpp"
#include "cpu.hpp"

int main(void) {
  Memory memory = Memory();
  CPU cpu = CPU(memory);
  memory.loadFile("test.bin");

  cpu.doCycle();
  cpu.doCycle();
  cpu.doCycle();
  cpu.doCycle();
  memory.dumpMemory();
  cpu.dumpRegisters();  
}