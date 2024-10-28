#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadAXS() {
  OperationOutput output =
      mCpu.mSum(mCpu.mAccumulator & mCpu.mXIndex, ~mCpu.mReadMemory(), 1);
  mCpu.mXIndex = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mXIndex);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::AXSImmediate() {
  mExecuteImmediate(&InstructionSet::mReadAXS);
}
