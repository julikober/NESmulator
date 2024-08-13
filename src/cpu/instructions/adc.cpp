#include "cpu.hpp"

void CPU::InstructionSet::ADCImmediate() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAccumulator =
          mCpu.mAddWithCarry(mCpu.mAccumulator, mCpu.mReadMemory());

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
          mCpu.mAddWithCarry(mCpu.mAccumulator, mCpu.mReadMemory());

    default:
      mCpu.mCycle = 1;
      break;
  }
}

void CPU::InstructionSet::ADCZeroPageX() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAddress += mCpu.mXIndex;

    case 4:
      mCpu.mAccumulator =
          mCpu.mAddWithCarry(mCpu.mAccumulator, mCpu.mReadMemory());

    default:
      mCpu.mCycle = 1;
      break;
  }
}

void CPU::InstructionSet::ADCAbsolute() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mSetAddressLow(mCpu.mReadMemory());
      break;

    case 3:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;
      mCpu.mSetAddressHigh(mCpu.mReadMemory());
      break;

    case 4:
      mCpu.mAccumulator =
          mCpu.mAddWithCarry(mCpu.mAccumulator, mCpu.mReadMemory());

    default:
      mCpu.mCycle = 1;
      break;
  }
}

void CPU::InstructionSet::ADCAbsoluteX() {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mSetAddressLow(mCpu.mReadMemory());
      break;

    case 3:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;
      mCpu.mSetAddressHigh(mCpu.mReadMemory());
      break;

    case 4:
      mCpu.mAddress += mCpu.mXIndex;

    case 5:
      mCpu.mAccumulator =
          mCpu.mAddWithCarry(mCpu.mAccumulator, mCpu.mReadMemory());

    default:
      mCpu.mCycle = 1;
      break;
  }
}