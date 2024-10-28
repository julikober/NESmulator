#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadADC() {
  OperationOutput output =
      mCpu.mSum(mCpu.mAccumulator, mCpu.mReadMemory(), mCpu.mCheckFlag(CARRY));
  mCpu.mAccumulator = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }

  if (output.overflow) {
    mCpu.mSetFlag(OVERFLOW);
  } else {
    mCpu.mClearFlag(OVERFLOW);
  }
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
