#include "cpu.hpp"

void CPU::InstructionSet::BRKImplied() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mProgramCounter++;
      break;

    case 3:
      mCpu.mPushStack(mCpu.mGetProgramCounterHigh());
      mCpu.mStackPointer--;
      break;

    case 4:
      mCpu.mPushStack(mCpu.mGetProgramCounterLow());
      mCpu.mStackPointer--;
      break;

    case 5:
      mCpu.mPushStack(mCpu.mStatus | BREAK);
      mCpu.mStackPointer--;
      break;

    case 6:
      mCpu.mAddress = 0xFFFE;
      mCpu.mSetProgramCounterLow(mCpu.mReadMemory());
      break;

    case 7:
      mCpu.mAddress = 0xFFFF;
      mCpu.mSetProgramCounterHigh(mCpu.mReadMemory());

      mCpu.mSetFlag(INTERRUPT_DISABLE);

    default:
      mCpu.mCycle = 0;
      break;
  }
}