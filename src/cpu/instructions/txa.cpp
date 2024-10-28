#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteTXA() {
  mCpu.mAccumulator = mCpu.mXIndex;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::TXAImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTXA);
}
