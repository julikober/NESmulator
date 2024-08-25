#include "cpu.hpp"

void CPU::InstructionSet::PLPImplied() {
  switch (mCpu.mCycle) {
    case 2:
      break;

    case 3:
      mCpu.mStackPointer++;
      break;

    case 4:
      mCpu.mStatus = (mCpu.mPopStack() | UNUSED) & ~BREAK;

    default:
      mCpu.mCycle = 0;
      break;
  }
}
