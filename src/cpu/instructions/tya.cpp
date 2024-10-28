#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteTYA() {
  mCpu.mAccumulator = mCpu.mYIndex;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::TYAImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTYA);
}
