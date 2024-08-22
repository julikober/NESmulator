#include "cpu.hpp"

void CPU::InstructionSet::mExecute(int startCycle,
                                   void (InstructionSet::*read)(),
                                   void (InstructionSet::*modify)(),
                                   void (InstructionSet::*write)()) {
  if (read != nullptr && modify == nullptr && write == nullptr) {
    (this->*read)();
    mCpu.mCycle = 0;
  } else if (read == nullptr && modify == nullptr && write != nullptr) {
    (this->*write)();
    mCpu.mCycle = 0;
  } else if (read != nullptr && modify != nullptr && write != nullptr) {
    if (mCpu.mCycle = startCycle) {
      (this->*read)();
    } else if (mCpu.mCycle = startCycle + 1) {
      (this->*modify)();
    } else if (mCpu.mCycle = startCycle + 2) {
      (this->*write)();
      mCpu.mCycle = 0;
    }
  }
}

void CPU::InstructionSet::mExecuteImplied(void (InstructionSet::*action)()) {
  (this->*action)();
  mCpu.mCycle = 0;
}

void CPU::InstructionSet::mExecuteAccumulator(void (InstructionSet::*read)(),
                                              void (InstructionSet::*modify)(),
                                              void (InstructionSet::*write)()) {
  mExecute(2, read, modify, write);
}

void CPU::InstructionSet::mExecuteImmediate(void (InstructionSet::*read)(),
                                            void (InstructionSet::*modify)(),
                                            void (InstructionSet::*write)()) {
  mCpu.mAddress = mCpu.mProgramCounter;
  mCpu.mProgramCounter++;

  mExecute(2, modify, write);
}

void CPU::InstructionSet::mExecuteZeroPage(void (InstructionSet::*read)(),
                                           void (InstructionSet::*modify)(),
                                           void (InstructionSet::*write)()) {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mAddress = mCpu.mReadMemory();
      break;

    default:
      mExecute(3, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteZeroPageX(void (InstructionSet::*read)(),
                                            void (InstructionSet::*modify)(),
                                            void (InstructionSet::*write)()) {
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
      mExecute(4, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteZeroPageY(void (InstructionSet::*read)(),
                                            void (InstructionSet::*modify)(),
                                            void (InstructionSet::*write)()) {
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
      mExecute(4, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteAbsolute(void (InstructionSet::*read)(),
                                           void (InstructionSet::*modify)(),
                                           void (InstructionSet::*write)()) {
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
      mExecute(4, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteAbsoluteX(void (InstructionSet::*read)(),
                                            void (InstructionSet::*modify)(),
                                            void (InstructionSet::*write)()) {
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
        mExecute(4, read, nullptr, nullptr);
      }
      break;

    default:
      mExecute(5, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteAbsoluteY(void (InstructionSet::*read)(),
                                            void (InstructionSet::*modify)(),
                                            void (InstructionSet::*write)()) {
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
        mExecute(4, read, nullptr, nullptr);
      }
      break;

    default:
      mExecute(5, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteIndirectX(void (InstructionSet::*read)(),
                                            void (InstructionSet::*modify)(),
                                            void (InstructionSet::*write)()) {
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
      mExecute(6, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteIndirectY(void (InstructionSet::*read)(),
                                            void (InstructionSet::*modify)(),
                                            void (InstructionSet::*write)()) {
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
        mExecute(5, read, nullptr, nullptr);
      }
      break;

    default:
      mExecute(6, read, modify, write);
      break;
  }
}

void CPU::InstructionSet::mExecuteRelative(
    bool (InstructionSet::*condition)()) {
  switch (mCpu.mCycle) {
    case 2:
      mCpu.mAddress = mCpu.mProgramCounter;
      mCpu.mProgramCounter++;

      mCpu.mBuffer = mCpu.mReadMemory();
      break;

    case 3:
      if ((this->*condition)()) {
        mCpu.mSetProgramCounterLow(mCpu.mGetProgramCounterLow() + mCpu.mBuffer);
      } else {
        mCpu.mCycle = 1;
        mCpu.mFetchInstruction();
      }
      break;

    case 4:
      if (mCpu.mGetProgramCounterLow() - mCpu.mBuffer < 0) {
        mCpu.mSetProgramCounterHigh(mCpu.mGetProgramCounterHigh() + 1);
      } else if (mCpu.mGetProgramCounterLow() - mCpu.mBuffer > 0xFF) {
        mCpu.mSetProgramCounterHigh(mCpu.mGetProgramCounterHigh() - 1);
      } else {
        mCpu.mCycle = 1;
        mCpu.mFetchInstruction();
      }
      break;

    case 5:
      mCpu.mCycle = 1;
      mCpu.mFetchInstruction();
      break;

    default:
      mCpu.mCycle = 0;
      break;
  }
}