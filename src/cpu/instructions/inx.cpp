#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteINX() {
  mCpu.mXIndex++;

  mCpu.mSetZeroAndNegative(mCpu.mXIndex);
}

void CPU::InstructionSet::INXImplied() {
  mExecuteImplied(&InstructionSet::mExecuteINX);
}
