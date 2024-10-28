#include "cpu/cpu.hpp"

void CPU::InstructionSet::mWriteSTY() { mCpu.mWriteMemory(mCpu.mYIndex); }

void CPU::InstructionSet::STYZeroPage() {
  mExecuteZeroPage(&CPU::InstructionSet::mWriteSTY);
}

void CPU::InstructionSet::STYZeroPageX() {
  mExecuteZeroPageX(&CPU::InstructionSet::mWriteSTY);
}

void CPU::InstructionSet::STYAbsolute() {
  mExecuteAbsolute(&CPU::InstructionSet::mWriteSTY);
}
