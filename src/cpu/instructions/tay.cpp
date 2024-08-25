#include "cpu.hpp"

void CPU::InstructionSet::mExecuteTAY() {
  mCpu.mYIndex = mCpu.mAccumulator;

  mCpu.mSetZeroAndNegative(mCpu.mYIndex);
}

void CPU::InstructionSet::TAYImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTAY);
}
