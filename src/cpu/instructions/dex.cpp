#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteDEX() {
  mCpu.mXIndex--;

  mCpu.mUpdateZeroAndNegative(mCpu.mXIndex);
}

void CPU::InstructionSet::DEXImplied() {
  mExecuteImplied(&InstructionSet::mExecuteDEX);
}
