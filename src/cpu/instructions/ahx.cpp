#include "cpu/cpu.hpp"

void CPU::InstructionSet::mWriteAHXAbsoluteY() {
  mCpu.mWriteMemory(
      mCpu.mXIndex & mCpu.mAccumulator &
      (uint8_t)(mCpu.mGetAddressHigh() -
                (mCpu.mGetAddressLow() - mCpu.mYIndex < 0 ? 1 : 0) +
                1));  // Subtract 1 if index caused overflow and add 1
}

void CPU::InstructionSet::mWriteAHXIndirectY() {
  mCpu.mWriteMemory(mCpu.mXIndex & mCpu.mAccumulator &
                    (uint8_t)(mCpu.mGetAddressLow() - mCpu.mYIndex +
                              1));  // Subtract index from low byte and add 1
}

void CPU::InstructionSet::AHXAbsoluteY() {
  mExecuteAbsoluteY(nullptr, nullptr, &InstructionSet::mWriteAHXAbsoluteY);
}

void CPU::InstructionSet::AHXIndirectY() {
  mExecuteIndirectY(nullptr, nullptr, &InstructionSet::mWriteAHXIndirectY);
}
