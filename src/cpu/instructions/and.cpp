#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadAND() {
  mCpu.mAccumulator = mCpu.mAnd(mCpu.mAccumulator, mCpu.mReadMemory()).value;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::ANDImmediate() {
  mExecuteImmediate(&InstructionSet::mReadAND);
}

void CPU::InstructionSet::ANDZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadAND);
}

void CPU::InstructionSet::ANDZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadAND);
}

void CPU::InstructionSet::ANDAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadAND);
}

void CPU::InstructionSet::ANDAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadAND);
}

void CPU::InstructionSet::ANDAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadAND);
}

void CPU::InstructionSet::ANDIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadAND);
}

void CPU::InstructionSet::ANDIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadAND);
}
