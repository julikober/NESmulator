#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteNOP() {}

void CPU::InstructionSet::NOPImplied() {
  mExecuteImplied(&InstructionSet::mExecuteNOP);
}

void CPU::InstructionSet::NOPImmediate() {
  mExecuteImmediate(&InstructionSet::mExecuteNOP);
}

void CPU::InstructionSet::NOPZeroPage() {
  mExecuteZeroPage(&InstructionSet::mExecuteNOP);
}

void CPU::InstructionSet::NOPZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mExecuteNOP);
}

void CPU::InstructionSet::NOPAbsolute() {
  mExecuteAbsolute(&InstructionSet::mExecuteNOP);
}

void CPU::InstructionSet::NOPAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mExecuteNOP);
}
