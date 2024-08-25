#include "cpu.hpp"

void CPU::InstructionSet::mExecuteTXS() {
  mCpu.mStackPointer = mCpu.mXIndex;

  mCpu.mSetZeroAndNegative(mCpu.mStackPointer);
}

void CPU::InstructionSet::TXSImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTXS);
}
