#include "cpu.hpp"

void CPU::InstructionSet::JMPAbsolute() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mBuffer = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAddress = mCpu.mProgramCounter;

      mCpu.mSetProgramCounterHigh(mCpu.mReadMemory());
      mCpu.mSetProgramCounterLow(mCpu.mBuffer);

    default:
      mCpu.mCycle = 0;
      break;
  }
}

void CPU::InstructionSet::JMPIndirect() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mBuffer = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mSetAddressHigh(mCpu.mReadMemory());
      mCpu.mSetAddressLow(mCpu.mBuffer);
      break;

    case 4:
      mCpu.mBuffer = mCpu.mReadMemory();
      break;

    case 5:
      mCpu.mAddress = (uint8_t)(mCpu.mAddress + 1);

      mCpu.mSetProgramCounterHigh(mCpu.mReadMemory());
      mCpu.mSetProgramCounterLow(mCpu.mBuffer);

    default:
      mCpu.mCycle = 0;
      break;
  }
}
