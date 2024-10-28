#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteINY() {
  mCpu.mYIndex++;

  mCpu.mSetZeroAndNegative(mCpu.mYIndex);
}

void CPU::InstructionSet::INYImplied() {
  mExecuteImplied(&InstructionSet::mExecuteINY);
}
