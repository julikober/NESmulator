#include "cpu.hpp"

void CPU::InstructionSet::mReadBIT() {
  mCpu.mAnd(mCpu.mAccumulator, mCpu.mReadMemory());

  if (mCpu.mReadMemory() & (1 << 6)) {
    mCpu.mSetFlag(OVERFLOW);
  } else {
    mCpu.mClearFlag(OVERFLOW);
  }

  if (mCpu.mReadMemory() & (1 << 7)) {
    mCpu.mSetFlag(NEGATIVE);
  } else {
    mCpu.mClearFlag(NEGATIVE);
  }
}

void CPU::InstructionSet::BITZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadBIT, nullptr, nullptr);
}

void CPU::InstructionSet::BITAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadBIT, nullptr, nullptr);
}