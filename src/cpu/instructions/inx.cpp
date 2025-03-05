#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteINX() {
  mCpu.mXIndex++;

  mCpu.mUpdateZeroAndNegative(mCpu.mXIndex);
}

void CPU::InstructionSet::INXImplied() {
  mExecuteImplied(&InstructionSet::mExecuteINX);
}
