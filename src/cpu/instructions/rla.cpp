#include "cpu.hpp"

void CPU::InstructionSet::mReadRLA() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyRLA() {
  OperationOutput output =
      mCpu.mSum(mCpu.mBuffer, mCpu.mBuffer, mCpu.mCheckFlag(CARRY));
  mCpu.mBuffer = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mBuffer);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::mWriteRLA() {
  mCpu.mWriteMemory(mCpu.mBuffer);

  mCpu.mAccumulator &= mCpu.mBuffer;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::RLAZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadRLA, &InstructionSet::mModifyRLA,
                   &InstructionSet::mWriteRLA);
}

void CPU::InstructionSet::RLAZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadRLA, &InstructionSet::mModifyRLA,
                    &InstructionSet::mWriteRLA);
}

void CPU::InstructionSet::RLAAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadRLA, &InstructionSet::mModifyRLA,
                   &InstructionSet::mWriteRLA);
}

void CPU::InstructionSet::RLAAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadRLA, &InstructionSet::mModifyRLA,
                    &InstructionSet::mWriteRLA);
}

void CPU::InstructionSet::RLAAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadRLA, &InstructionSet::mModifyRLA,
                    &InstructionSet::mWriteRLA);
}

void CPU::InstructionSet::RLAIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadRLA, &InstructionSet::mModifyRLA,
                    &InstructionSet::mWriteRLA);
}

void CPU::InstructionSet::RLAIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadRLA, &InstructionSet::mModifyRLA,
                    &InstructionSet::mWriteRLA);
}
