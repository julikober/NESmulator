#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteTSX() {
  mCpu.mXIndex = mCpu.mStackPointer;

  mCpu.mSetZeroAndNegative(mCpu.mXIndex);
}

void CPU::InstructionSet::TSXImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTSX);
}
