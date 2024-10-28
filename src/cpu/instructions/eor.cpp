#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadEOR() {
  mCpu.mAccumulator = mCpu.mEor(mCpu.mAccumulator, mCpu.mReadMemory()).value;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::EORImmediate() {
  mExecuteImmediate(&InstructionSet::mReadEOR);
}

void CPU::InstructionSet::EORZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadEOR);
}

void CPU::InstructionSet::EORZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadEOR);
}

void CPU::InstructionSet::EORAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadEOR);
}

void CPU::InstructionSet::EORAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadEOR);
}

void CPU::InstructionSet::EORAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadEOR);
}

void CPU::InstructionSet::EORIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadEOR);
}

void CPU::InstructionSet::EORIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadEOR);
}
