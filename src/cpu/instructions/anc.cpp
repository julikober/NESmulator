#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadANC() {
  mCpu.mAccumulator &= mCpu.mReadMemory();

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);

  if (mCpu.mCheckFlag(NEGATIVE)) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::ANCImmediate() {
  mExecuteImmediate(&CPU::InstructionSet::mReadANC);
}