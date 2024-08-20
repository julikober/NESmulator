#include "cpu.hpp"

void CPU::InstructionSet::mReadADC(uint8_t value) {
  mCpu.mAccumulator = mCpu.mAddWithCarry(mCpu.mAccumulator, value);
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
  mExecuteIndirectX(&InstructionSet::mReadADC);
}

void CPU::InstructionSet::ADCIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadADC);
}
