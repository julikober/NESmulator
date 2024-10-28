#include "cpu/cpu.hpp"

void CPU::InstructionSet::mWriteTAS() {
  mCpu.mStackPointer = mCpu.mAccumulator & mCpu.mXIndex;

  mCpu.mWriteMemory(
      mCpu.mStackPointer &
      (uint8_t)(mCpu.mGetAddressHigh() -
                (mCpu.mGetAddressLow() - mCpu.mYIndex < 0 ? 1 : 0) +
                1));  // Subtract 1 if index caused overflow and add 1
}

void CPU::InstructionSet::TASAbsoluteY() {
  mExecuteAbsoluteY(nullptr, nullptr, &InstructionSet::mWriteTAS);
}
