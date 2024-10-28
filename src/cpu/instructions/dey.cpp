#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteDEY() {
  mCpu.mYIndex--;

  mCpu.mSetZeroAndNegative(mCpu.mYIndex);
}

void CPU::InstructionSet::DEYImplied() {
  mExecuteImplied(&InstructionSet::mExecuteDEY);
}
