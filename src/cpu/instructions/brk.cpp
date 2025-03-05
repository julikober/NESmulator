#include "cpu/cpu.hpp"

void CPU::InstructionSet::BRKImplied() { mCpu.mDoInterrupt(BRK); }
