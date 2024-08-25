#include "cpu.hpp"

void CPU::InstructionSet::mWriteSTX() { mCpu.mWriteMemory(mCpu.mXIndex); }

void CPU::InstructionSet::STXZeroPage() {
  mExecuteZeroPage(&CPU::InstructionSet::mWriteSTX);
}

void CPU::InstructionSet::STXZeroPageY() {
  mExecuteZeroPageY(&CPU::InstructionSet::mWriteSTX);
}

void CPU::InstructionSet::STXAbsolute() {
  mExecuteAbsolute(&CPU::InstructionSet::mWriteSTX);
}
