#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadSLO() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifySLO() {
  OperationOutput output = mCpu.mSum(mCpu.mBuffer, mCpu.mBuffer);
  mCpu.mBuffer = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mBuffer);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::mWriteSLO() {
  mCpu.mWriteMemory(mCpu.mBuffer);
  mCpu.mAccumulator |= mCpu.mBuffer;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::SLOZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadSLO, &InstructionSet::mModifySLO,
                   &InstructionSet::mWriteSLO);
}

void CPU::InstructionSet::SLOZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadSLO, &InstructionSet::mModifySLO,
                    &InstructionSet::mWriteSLO);
}

void CPU::InstructionSet::SLOAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadSLO, &InstructionSet::mModifySLO,
                   &InstructionSet::mWriteSLO);
}

void CPU::InstructionSet::SLOAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadSLO, &InstructionSet::mModifySLO,
                    &InstructionSet::mWriteSLO);
}

void CPU::InstructionSet::SLOAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadSLO, &InstructionSet::mModifySLO,
                    &InstructionSet::mWriteSLO);
}

void CPU::InstructionSet::SLOIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadSLO, &InstructionSet::mModifySLO,
                    &InstructionSet::mWriteSLO);
}

void CPU::InstructionSet::SLOIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadSLO, &InstructionSet::mModifySLO,
                    &InstructionSet::mWriteSLO);
}
