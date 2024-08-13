#include "cpu.hpp"

void CPU::InstructionSet::ASLZeroPage() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mBuffer = mCpu.mReadMemory();
      break;

    case 4:
      mCpu.mWriteMemory(mCpu.mShiftLeft(mCpu.mBuffer));

    default:
      mCpu.mCycle = 1;
      break;
  }
}