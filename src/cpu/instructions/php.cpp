#include "cpu.hpp"

void CPU::InstructionSet::PHPImplied() {
  switch (mCpu.mCycle) {
    case 2:
      break;

    case 3:
      mCpu.mPushStack(mCpu.mStatus | BREAK);
      mCpu.mStackPointer--;

    default:
      mCpu.mCycle = 0;
      break;
  }
}
