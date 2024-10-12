#include "cpu.hpp"

void CPU::InstructionSet::mWriteSHY() {
  mCpu.mWriteMemory(
      mCpu.mYIndex &
      (uint8_t)(mCpu.mGetAddressHigh() -
                (mCpu.mGetAddressLow() - mCpu.mXIndex < 0 ? 1 : 0) +
                1));  // Subtract 1 if index caused overflow and add 1
}

void CPU::InstructionSet::SHYAbsoluteX() {
  mExecuteAbsoluteX(nullptr, nullptr, &InstructionSet::mWriteSHY);
}
