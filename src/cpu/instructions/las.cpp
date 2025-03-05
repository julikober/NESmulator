#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadLAS() {
  mCpu.mAccumulator = mCpu.mStackPointer & mCpu.mReadMemory();
  mCpu.mXIndex = mCpu.mAccumulator;
  mCpu.mStackPointer = mCpu.mAccumulator;

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::LASAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadLAS);
}
