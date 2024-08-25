#include "cpu.hpp"

void CPU::InstructionSet::RTSImplied() {
  switch (mCpu.mCycle) {
    case 2:
      break;

    case 3:
      mCpu.mStackPointer++;
      break;

    case 4:
      mCpu.mSetProgramCounterLow(mCpu.mPopStack());
      mCpu.mStackPointer++;
      break;

    case 5:
      mCpu.mSetProgramCounterHigh(mCpu.mPopStack());
      break;

    case 6:
      mCpu.mProgramCounter++;

    default:
      mCpu.mCycle = 0;
      break;
  }
}
