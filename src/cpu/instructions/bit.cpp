#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadBIT() {
  OperationOutput output = mCpu.mAnd(mCpu.mAccumulator, mCpu.mReadMemory());

  if (mCpu.mReadMemory() & (1 << 7)) {
    mCpu.mSetFlag(NEGATIVE);
  } else {
    mCpu.mClearFlag(NEGATIVE);
  }

  if (mCpu.mReadMemory() & (1 << 6)) {
    mCpu.mSetFlag(OVERFLOW);
  } else {
    mCpu.mClearFlag(OVERFLOW);
  }

  if (output.value == 0) {
    mCpu.mSetFlag(ZERO);
  } else {
    mCpu.mClearFlag(ZERO);
  }
}

void CPU::InstructionSet::BITZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadBIT, nullptr, nullptr);
}

void CPU::InstructionSet::BITAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadBIT, nullptr, nullptr);
}
