#include "cpu.hpp"

void CPU::InstructionSet::mReadDCP() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyDCP() {
  mCpu.mBuffer--;
  mCpu.mSetZeroAndNegative(mCpu.mBuffer);
}

void CPU::InstructionSet::mWriteDCP() {
  mCpu.mWriteMemory(mCpu.mBuffer);
  OperationOutput output = mCpu.mSum(mCpu.mAccumulator, ~mCpu.mBuffer, 1);

  mCpu.mSetZeroAndNegative(output.value);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::DCPZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadDCP, &InstructionSet::mModifyDCP,
                   &InstructionSet::mWriteDCP);
}

void CPU::InstructionSet::DCPZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadDCP, &InstructionSet::mModifyDCP,
                    &InstructionSet::mWriteDCP);
}

void CPU::InstructionSet::DCPAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadDCP, &InstructionSet::mModifyDCP,
                   &InstructionSet::mWriteDCP);
}

void CPU::InstructionSet::DCPAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadDCP, &InstructionSet::mModifyDCP,
                    &InstructionSet::mWriteDCP);
}

void CPU::InstructionSet::DCPAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadDCP, &InstructionSet::mModifyDCP,
                    &InstructionSet::mWriteDCP);
}

void CPU::InstructionSet::DCPIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadDCP, &InstructionSet::mModifyDCP,
                    &InstructionSet::mWriteDCP);
}

void CPU::InstructionSet::DCPIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadDCP, &InstructionSet::mModifyDCP,
                    &InstructionSet::mWriteDCP);
}
