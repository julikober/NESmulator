#include "cpu.hpp"

void CPU::InstructionSet::mReadCMP() {
  OperationOutput output = mCpu.mSum(mCpu.mAccumulator, ~mCpu.mReadMemory(), 1);

  mCpu.mSetZeroAndNegative(output.value);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::CMPImmediate() {
  mExecuteImmediate(&InstructionSet::mReadCMP);
}

void CPU::InstructionSet::CMPZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadCMP);
}

void CPU::InstructionSet::CMPZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadCMP);
}

void CPU::InstructionSet::CMPAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadCMP);
}

void CPU::InstructionSet::CMPAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadCMP);
}

void CPU::InstructionSet::CMPAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadCMP);
}

void CPU::InstructionSet::CMPIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadCMP);
}

void CPU::InstructionSet::CMPIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadCMP);
}
