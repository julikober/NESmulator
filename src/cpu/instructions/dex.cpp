#include "cpu.hpp"

void CPU::InstructionSet::mExecuteDEX() {
  mCpu.mXIndex--;

  mCpu.mSetZeroAndNegative(mCpu.mXIndex);
}

void CPU::InstructionSet::DEXImplied() { mExecuteDEX(); }