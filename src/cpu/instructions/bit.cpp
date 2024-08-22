#include "cpu.hpp"

void CPU::InstructionSet::mReadBIT() {
  mCpu.mAnd(mCpu.mAccumulator, mCpu.mReadMemory());

  if (mCpu.mReadMemory() & (1 << 6)) {
    mCpu.mSetFlag(OVERFLOW);
  } else {
    mCpu.mClearFlag(OVERFLOW);
  }

  mCpu.mSetZeroAndNegative(mCpu.mReadMemory());
}

void CPU::InstructionSet::BITZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadBIT, nullptr, nullptr);
}

void CPU::InstructionSet::BITAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadBIT, nullptr, nullptr);
}