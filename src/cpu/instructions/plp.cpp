#include "cpu.hpp"

void CPU::InstructionSet::mExecutePLP() { mCpu.mStatus = mCpu.mPopStack(); }

void CPU::InstructionSet::PLPImplied() {
  mExecuteImplied(&InstructionSet::mExecutePLP);
}
