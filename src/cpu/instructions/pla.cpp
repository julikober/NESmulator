#include "cpu.hpp"

void CPU::InstructionSet::mExecutePLA() {
  mCpu.mAccumulator = mCpu.mPopStack();

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::PLAImplied() {
  mExecuteImplied(&InstructionSet::mExecutePLA);
}
