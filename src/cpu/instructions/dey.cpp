#include "cpu.hpp"

void CPU::InstructionSet::mExecuteDEY() {
  mCpu.mYIndex--;

  mCpu.mSetZeroAndNegative(mCpu.mYIndex);
}

void CPU::InstructionSet::DEYImplied() { mExecuteDEY(); }
