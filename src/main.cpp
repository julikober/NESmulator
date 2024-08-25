#include <cstdint>
#include <iostream>

#include "cpu.hpp"
#include "memory.hpp"

int main(void) {
  Memory memory = Memory();
  CPU cpu = CPU(memory);
  memory.loadFile("testing/6502_functional_test.bin");

  while (1) {

    cpu.doCycle();
    cpu.dumpRegisters();
  }
}