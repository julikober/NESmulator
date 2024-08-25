#include "cpu.hpp"

void CPU::InstructionSet::JSRAbsolute() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mBuffer = mCpu.mReadMemory();

      break;

    case 3:
      break;

    case 4:
      mCpu.mPushStack(mCpu.mGetProgramCounterHigh());
      mCpu.mStackPointer--;

      break;

    case 5:
      mCpu.mPushStack(mCpu.mGetProgramCounterLow());
      mCpu.mStackPointer--;

      break;

    case 6:
      mCpu.mAddress = mCpu.mProgramCounter;

      mCpu.mSetProgramCounterHigh(mCpu.mReadMemory());
      mCpu.mSetProgramCounterLow(mCpu.mBuffer);

    default:
      mCpu.mCycle = 0;
      break;
  }
}
