#include "cpu.hpp"

void CPU::InstructionSet::mExecuteSEI() { mCpu.mSetFlag(INTERRUPT_DISABLE); }

void CPU::InstructionSet::SEIImplied() {
  mExecuteImplied(&InstructionSet::mExecuteSEI);
}
