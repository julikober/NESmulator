#include "cpu.hpp"

void CPU::InstructionSet::mWriteSTA() { mCpu.mWriteMemory(mCpu.mAccumulator); }

void CPU::InstructionSet::STAZeroPage() {
  mExecuteZeroPage(&CPU::InstructionSet::mWriteSTA);
}

void CPU::InstructionSet::STAZeroPageX() {
  mExecuteZeroPageX(&CPU::InstructionSet::mWriteSTA);
}

void CPU::InstructionSet::STAAbsolute() {
  mExecuteAbsolute(&CPU::InstructionSet::mWriteSTA);
}

void CPU::InstructionSet::STAAbsoluteX() {
  mExecuteAbsoluteX(&CPU::InstructionSet::mWriteSTA);
}

void CPU::InstructionSet::STAAbsoluteY() {
  mExecuteAbsoluteY(&CPU::InstructionSet::mWriteSTA);
}

void CPU::InstructionSet::STAIndirectX() {
  mExecuteIndirectX(&CPU::InstructionSet::mWriteSTA);
}

void CPU::InstructionSet::STAIndirectY() {
  mExecuteIndirectY(&CPU::InstructionSet::mWriteSTA);
}
