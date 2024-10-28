#include "cpu/cpu.hpp"

#define UNDETERMINISTIC_CONSTANT \
  0xEE  // This constant varies from cpu to cpu. To match the test cases 0xEE
        // was chosen.

void CPU::InstructionSet::mReadLAX() {
  mCpu.mAccumulator = mCpu.mReadMemory();
  mCpu.mXIndex = mCpu.mAccumulator;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::mReadLAXImmediate() {
  mCpu.mAccumulator =
      (mCpu.mAccumulator | UNDETERMINISTIC_CONSTANT) & mCpu.mReadMemory();
  mCpu.mXIndex = mCpu.mAccumulator;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::LAXImmediate() {
  mExecuteImmediate(&InstructionSet::mReadLAXImmediate);
}

void CPU::InstructionSet::LAXZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadLAX);
}

void CPU::InstructionSet::LAXZeroPageY() {
  mExecuteZeroPageY(&InstructionSet::mReadLAX);
}

void CPU::InstructionSet::LAXAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadLAX);
}

void CPU::InstructionSet::LAXAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadLAX);
}

void CPU::InstructionSet::LAXIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadLAX);
}

void CPU::InstructionSet::LAXIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadLAX);
}
