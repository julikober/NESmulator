#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadORA() {
  mCpu.mAccumulator = mCpu.mOr(mCpu.mAccumulator, mCpu.mReadMemory()).value;

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::ORAImmediate() {
  mExecuteImmediate(&InstructionSet::mReadORA);
}

void CPU::InstructionSet::ORAZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadORA);
}

void CPU::InstructionSet::ORAZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadORA);
}

void CPU::InstructionSet::ORAAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadORA);
}

void CPU::InstructionSet::ORAAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadORA);
}

void CPU::InstructionSet::ORAAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadORA);
}

void CPU::InstructionSet::ORAIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadORA);
}

void CPU::InstructionSet::ORAIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadORA);
}
