#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteTAY() {
  mCpu.mYIndex = mCpu.mAccumulator;

  mCpu.mUpdateZeroAndNegative(mCpu.mYIndex);
}

void CPU::InstructionSet::TAYImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTAY);
}
