#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadALR() {
  OperationOutput output =
      mCpu.mShiftRight(mCpu.mAccumulator & mCpu.mReadMemory());
  mCpu.mAccumulator = output.value;

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);
  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::ALRImmediate() {
  mExecuteImmediate(&CPU::InstructionSet::mReadALR);
}
