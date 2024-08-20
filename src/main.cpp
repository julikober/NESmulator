#include <iostream>
#include <cstdint>
#include "memory.hpp"
#include "cpu.hpp"

int main(void) {
  Memory memory = Memory();
  CPU cpu = CPU(memory);
  memory.loadFile("test.bin");

  cpu.do_cycle();
  cpu.do_cycle();
  cpu.do_cycle();
  cpu.do_cycle();
  memory.dumpMemory();
  cpu.dumpRegisters();  
}