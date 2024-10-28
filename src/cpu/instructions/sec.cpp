#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteSEC() { mCpu.mSetFlag(CARRY); }

void CPU::InstructionSet::SECImplied() {
  mExecuteImplied(&InstructionSet::mExecuteSEC);
}
