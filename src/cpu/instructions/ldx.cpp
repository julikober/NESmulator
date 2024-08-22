#include "cpu.hpp"

void CPU::InstructionSet::mReadLDX() { mCpu.mXIndex = mCpu.mReadMemory(); }

void CPU::InstructionSet::LDXImmediate() {
  mExecuteImmediate(&CPU::InstructionSet::mReadLDX);
}

void CPU::InstructionSet::LDXZeroPage() {
  mExecuteZeroPage(&CPU::InstructionSet::mReadLDX);
}

void CPU::InstructionSet::LDXZeroPageY() {
  mExecuteZeroPageY(&CPU::InstructionSet::mReadLDX);
}

void CPU::InstructionSet::LDXAbsolute() {
  mExecuteAbsolute(&CPU::InstructionSet::mReadLDX);
}

void CPU::InstructionSet::LDXAbsoluteY() {
  mExecuteAbsoluteY(&CPU::InstructionSet::mReadLDX);
}
