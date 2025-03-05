#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadARR() {
  OperationOutput output =
      mCpu.mShiftRight(mCpu.mReadMemory() & mCpu.mAccumulator);
  mCpu.mAccumulator = output.value | (mCpu.mCheckFlag(CARRY) << 7);

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);

  // Set carry if bit 6 is set
  if (mCpu.mAccumulator & (1 << 6)) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }

  // Set overflow flag if bit 6 is different from bit 5
  if (((mCpu.mAccumulator & (1 << 6)) >> 6) !=
      ((mCpu.mAccumulator & (1 << 5)) >> 5)) {
    mCpu.mSetFlag(OVERFLOW);
  } else {
    mCpu.mClearFlag(OVERFLOW);
  }
}

void CPU::InstructionSet::ARRImmediate() {
  mExecuteImmediate(&InstructionSet::mReadARR);
}
