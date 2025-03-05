#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteTSX() {
  mCpu.mXIndex = mCpu.mStackPointer;

  mCpu.mUpdateZeroAndNegative(mCpu.mXIndex);
}

void CPU::InstructionSet::TSXImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTSX);
}
