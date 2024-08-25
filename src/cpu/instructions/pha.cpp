#include "cpu.hpp"

void CPU::InstructionSet::PHAImplied() {
  switch (mCpu.mCycle) {
    case 2:
      break;

    case 3:
      mCpu.mPushStack(mCpu.mAccumulator);
      mCpu.mStackPointer--;

    default:
      mCpu.mCycle = 0;
      break;
  }
}
