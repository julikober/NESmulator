#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteTAX() {
  mCpu.mXIndex = mCpu.mAccumulator;

  mCpu.mSetZeroAndNegative(mCpu.mXIndex);
}

void CPU::InstructionSet::TAXImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTAX);
}
