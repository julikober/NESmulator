#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadSRE() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifySRE() {
  OperationOutput output = mCpu.mShiftRight(mCpu.mBuffer);
  mCpu.mBuffer = output.value;

  mCpu.mUpdateZeroAndNegative(mCpu.mBuffer);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::mWriteSRE() {
  mCpu.mWriteMemory(mCpu.mBuffer);
  mCpu.mAccumulator ^= mCpu.mBuffer;

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::SREZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadSRE, &InstructionSet::mModifySRE,
                   &InstructionSet::mWriteSRE);
}

void CPU::InstructionSet::SREZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadSRE, &InstructionSet::mModifySRE,
                    &InstructionSet::mWriteSRE);
}

void CPU::InstructionSet::SREAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadSRE, &InstructionSet::mModifySRE,
                   &InstructionSet::mWriteSRE);
}

void CPU::InstructionSet::SREAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadSRE, &InstructionSet::mModifySRE,
                    &InstructionSet::mWriteSRE);
}

void CPU::InstructionSet::SREAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadSRE, &InstructionSet::mModifySRE,
                    &InstructionSet::mWriteSRE);
}

void CPU::InstructionSet::SREIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadSRE, &InstructionSet::mModifySRE,
                    &InstructionSet::mWriteSRE);
}

void CPU::InstructionSet::SREIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadSRE, &InstructionSet::mModifySRE,
                    &InstructionSet::mWriteSRE);
}
