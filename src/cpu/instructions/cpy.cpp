#include "cpu.hpp"

void CPU::InstructionSet::mReadCPY() {
  OperationOutput output = mCpu.mSum(mCpu.mYIndex, ~mCpu.mReadMemory(), 1);

  mCpu.mSetZeroAndNegative(output.value);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::CPYImmediate() {
  mExecuteImmediate(&InstructionSet::mReadCPY);
}

void CPU::InstructionSet::CPYZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadCPY);
}

void CPU::InstructionSet::CPYAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadCPY);
}