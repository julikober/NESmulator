#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadCPX() {
  OperationOutput output = mCpu.mSum(mCpu.mXIndex, ~mCpu.mReadMemory(), 1);

  mCpu.mUpdateZeroAndNegative(output.value);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::CPXImmediate() {
  mExecuteImmediate(&InstructionSet::mReadCPX);
}

void CPU::InstructionSet::CPXZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadCPX);
}

void CPU::InstructionSet::CPXAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadCPX);
}
