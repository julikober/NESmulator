#include "cpu.hpp"

void CPU::InstructionSet::mReadADC() {
  mCpu.mAccumulator = mCpu.mAddWithCarry(mCpu.mAccumulator, mCpu.mReadMemory());
}

void CPU::InstructionSet::ADCImmediate() {
  mExecuteImmediate(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCIndirectX() {
  // mExecuteIndirectX(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCIndirectY() {
  // mExecuteIndirectY(&InstructionSet::mReadADC);
}
