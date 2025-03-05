#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteINY() {
  mCpu.mYIndex++;

  mCpu.mUpdateZeroAndNegative(mCpu.mYIndex);
}

void CPU::InstructionSet::INYImplied() {
  mExecuteImplied(&InstructionSet::mExecuteINY);
}
