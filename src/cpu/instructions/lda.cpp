#include "cpu.hpp"

void CPU::InstructionSet::mReadLDA() { mCpu.mAccumulator = mCpu.mReadMemory(); }

void CPU::InstructionSet::LDAImmediate() {
  mExecuteImmediate(&CPU::InstructionSet::mReadLDA);
}

void CPU::InstructionSet::LDAZeroPage() {
  mExecuteZeroPage(&CPU::InstructionSet::mReadLDA);
}

void CPU::InstructionSet::LDAZeroPageX() {
  mExecuteZeroPageX(&CPU::InstructionSet::mReadLDA);
}

void CPU::InstructionSet::LDAAbsolute() {
  mExecuteAbsolute(&CPU::InstructionSet::mReadLDA);
}

void CPU::InstructionSet::LDAAbsoluteX() {
  mExecuteAbsoluteX(&CPU::InstructionSet::mReadLDA);
}

void CPU::InstructionSet::LDAAbsoluteY() {
  mExecuteAbsoluteY(&CPU::InstructionSet::mReadLDA);
}

void CPU::InstructionSet::LDAIndirectX() {
  mExecuteIndirectX(&CPU::InstructionSet::mReadLDA);
}

void CPU::InstructionSet::LDAIndirectY() {
  mExecuteIndirectY(&CPU::InstructionSet::mReadLDA);
}
