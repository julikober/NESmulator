#include "cpu.hpp"

void CPU::InstructionSet::ORAZeroPage() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAccumul#include "cpu.hpp"
ator = mCpu.mOr(mCpu.mAccumulator, mCpu.mReadMemory());

    default:
      mCpu.mCycle = 1;
      break;
  }
}

void CPU::InstructionSet::ORAIndirectX() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAddress = (mCpu.mAddress + mCpu.mXIndex) % 0xFF;
      break;

    case 4:
      mCpu.mBuffer = mCpu.mReadMemory();
      break;

    case 5:
      mCpu.mSetAddressHigh(mCpu.mAddress + 1);
      mCpu.mSetAddressLow(mCpu.mBuffer);
      break;

    case 6:
      mCpu.mAccumulator = mCpu.mOr(mCpu.mAccumulator, mCpu.mReadMemory());

    default:
      mCpu.mCycle = 1;
      break;
  }
}