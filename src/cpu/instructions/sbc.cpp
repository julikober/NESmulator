#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadSBC() {
  OperationOutput output =
      mCpu.mSum(mCpu.mAccumulator, ~mCpu.mReadMemory(), mCpu.mCheckFlag(CARRY));
  mCpu.mAccumulator = output.value;

  mCpu.mUpdateZeroAndNegative(output.value);

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

void CPU::InstructionSet::SBCImmediate() {
  mExecuteImmediate(&InstructionSet::mReadSBC);
}

void CPU::InstructionSet::SBCZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadSBC);
}

void CPU::InstructionSet::SBCZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadSBC);
}

void CPU::InstructionSet::SBCAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadSBC);
}

void CPU::InstructionSet::SBCAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadSBC);
}

void CPU::InstructionSet::SBCAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadSBC);
}

void CPU::InstructionSet::SBCIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadSBC);
}

void CPU::InstructionSet::SBCIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadSBC);
}
