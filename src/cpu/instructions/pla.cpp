#include "cpu/cpu.hpp"

void CPU::InstructionSet::PLAImplied() {
  switch (mCpu.mCycle) {
    case 2:
      break;

    case 3:
      mCpu.mStackPointer++;
      break;

    case 4:
      mCpu.mAccumulator = mCpu.mPopStack();
      mCpu.mSetZeroAndNegative(mCpu.mAccumulator);

    default:
      mCpu.mCycle = 0;
      break;
  }
}
