#include "cpu.hpp"

void CPU::InstructionSet::mReadCMP() {
  OperationOutput output = mCpu.mSum(mCpu.mAccumulator, ~mCpu.mReadMemory(), 1);

  mCpu.mSetZeroAndNegative(output.value);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::CMPImmediate() {
  mExecuteImmediate(&InstructionSet::mReadCMP);
}