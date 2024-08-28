#include "cpu.hpp"

void CPU::InstructionSet::mReadALR() {
  OperationOutput output =
      mCpu.mShiftRight(mCpu.mReadMemory() & mCpu.mAccumulator);
  mCpu.mAccumulator = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::ALRImmediate() {
  mExecuteImmediate(&CPU::InstructionSet::mReadALR);
}
