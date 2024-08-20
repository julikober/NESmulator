#include "cpu.hpp"

void CPU::InstructionSet::mExecute(
    int startCycle, uint8_t value, void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  if (read != nullptr && modify == nullptr && write == nullptr) {
    (this->*read)(value);
    mCpu.mCycle = 0;
  } else if (read == nullptr && modify == nullptr && write != nullptr) {
    (this->*write)(value);
    mCpu.mCycle = 0;
  } else if (read != nullptr && modify != nullptr && write != nullptr) {
    if (mCpu.mCycle = startCycle) {
      (this->*read)(value);
    } else if (mCpu.mCycle = startCycle + 1) {
      (this->*modify)(value);
    } else if (mCpu.mCycle = startCycle + 2) {
      (this->*write)(value);
      mCpu.mCycle = 0;
    }
  }
}

void CPU::InstructionSet::mExecuteAccumulator(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  mExecute(2, mCpu.mAccumulator, read, modify, write);
}

void CPU::InstructionSet::mExecuteImmediate(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  mCpu.mAddress = mCpu.mProgramCounter;
  mCpu.mProgramCounter++;

  mExecute(2, mCpu.mReadMemory(), modify, write);
}

void CPU::InstructionSet::mExecuteZeroPage(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    default:
      mExecute(3, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteZeroPageX(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAddress = (uint8_t)(mCpu.mAddress + mCpu.mXIndex);
      break;

    default:
      mExecute(4, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteZeroPageY(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAddress = (uint8_t)(mCpu.mAddress + mCpu.mYIndex);
      break;

    default:
      mExecute(4, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteAbsolute(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
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

    default:
      mExecute(4, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteAbsoluteX(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
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
      mCpu.mSetAddressLow(mCpu.mBuffer + mCpu.mXIndex);
      break;

    case 4:
      if (mCpu.mGetAddressLow() - mCpu.mXIndex < 0) {
        mCpu.mSetAddressHigh(mCpu.mGetAddressHigh() + 1);
        break;
      }

      if (write == nullptr && modify == nullptr) {
        mExecute(4, mCpu.mReadMemory(), read, nullptr, nullptr);
      }
      break;

    default:
      mExecute(5, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteAbsoluteY(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
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
      mCpu.mSetAddressLow(mCpu.mBuffer + mCpu.mYIndex);
      break;

    case 4:
      if (mCpu.mGetAddressLow() - mCpu.mYIndex < 0) {
        mCpu.mSetAddressHigh(mCpu.mGetAddressHigh() + 1);
        break;
      }

      if (write == nullptr && modify == nullptr) {
        mExecute(4, mCpu.mReadMemory(), read, nullptr, nullptr);
      }
      break;

    default:
      mExecute(5, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteIndirectX(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mAddress = (uint8_t)(mCpu.mAddress + mCpu.mXIndex);
      break;

    case 4:
      mCpu.mBuffer = mCpu.mReadMemory();
      mCpu.mAddress = (uint8_t)(mCpu.mAddress + 1);
      break;

    case 5:
      mCpu.mSetAddressHigh(mCpu.mReadMemory());
      mCpu.mSetAddressLow(mCpu.mBuffer);
      break;

    default:
      mExecute(6, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteIndirectY(
    void (InstructionSet::*read)(uint8_t value),
    void (InstructionSet::*modify)(uint8_t value),
    void (InstructionSet::*write)(uint8_t value)) {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    case 3:
      mCpu.mBuffer = mCpu.mReadMemory();
      mCpu.mAddress = (uint8_t)(mCpu.mAddress + 1);
      break;

    case 4:
      mCpu.mSetAddressHigh(mCpu.mReadMemory());
      mCpu.mSetAddressLow(mCpu.mBuffer + mCpu.mYIndex);
      break;

    case 5:
      if (mCpu.mGetAddressLow() - mCpu.mYIndex < 0) {
        mCpu.mSetAddressHigh(mCpu.mGetAddressHigh() + 1);
        break;
      }

      if (write == nullptr && modify == nullptr) {
        mExecute(5, mCpu.mReadMemory(), read, nullptr, nullptr);
      }
      break;

    default:
      mExecute(6, mCpu.mReadMemory(), read, modify, write);
      break;
  }
}
