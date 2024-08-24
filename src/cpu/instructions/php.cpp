#include "cpu.hpp"

void CPU::InstructionSet::mExecutePHP() { mCpu.mPushStack(mCpu.mStatus); }

void CPU::InstructionSet::PHPImplied() {
  mExecuteImplied(&InstructionSet::mExecutePHP);
}
