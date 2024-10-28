#include "cpu/cpu.hpp"

void CPU::InstructionSet::mWriteSHX() {
  mCpu.mWriteMemory(
      mCpu.mXIndex &
      (uint8_t)(mCpu.mGetAddressHigh() -
                (mCpu.mGetAddressLow() - mCpu.mYIndex < 0 ? 1 : 0) +
                1));  // Subtract 1 if index caused overflow and add 1
}

void CPU::InstructionSet::SHXAbsoluteY() {
  mExecuteAbsoluteY(nullptr, nullptr, &InstructionSet::mWriteSHX);
}
