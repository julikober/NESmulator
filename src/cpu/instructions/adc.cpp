#include "cpu.hpp"

void CPU::InstructionSet::ADCImmediate() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAccumulator =
          mCpu.mAlu.SUM(mCpu.mAccumulator, mCpu.mReadMemory(), true);

    default:
      mCpu.mCycle = 1;
      break;
  }
}

void CPU::InstructionSet::ADCZeroPage() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAccumulator =
          mCpu.mAlu.SUM(mCpu.mAccumulator, mCpu.mReadMemory(), true);

    default:
      mCpu.mCycle = 1;
      break;
  }
}