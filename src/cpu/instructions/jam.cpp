#include "cpu/cpu.hpp"

void CPU::InstructionSet::JAM() {
  mCpu.mCycle = 1;
}
