#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadLDY() {
  mCpu.mYIndex = mCpu.mReadMemory();

  mCpu.mUpdateZeroAndNegative(mCpu.mYIndex);
}

void CPU::InstructionSet::LDYImmediate() {
  mExecuteImmediate(&CPU::InstructionSet::mReadLDY);
}

void CPU::InstructionSet::LDYZeroPage() {
  mExecuteZeroPage(&CPU::InstructionSet::mReadLDY);
}

void CPU::InstructionSet::LDYZeroPageX() {
  mExecuteZeroPageX(&CPU::InstructionSet::mReadLDY);
}

void CPU::InstructionSet::LDYAbsolute() {
  mExecuteAbsolute(&CPU::InstructionSet::mReadLDY);
}

void CPU::InstructionSet::LDYAbsoluteX() {
  mExecuteAbsoluteX(&CPU::InstructionSet::mReadLDY);
}
