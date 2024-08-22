#include "cpu.hpp"

void CPU::InstructionSet::mReadASL() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyASL() {
  OperationOutput output = mCpu.mSum(mCpu.mBuffer, mCpu.mBuffer);
  mCpu.mBuffer = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mBuffer);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::mWriteASL() { mCpu.mWriteMemory(mCpu.mBuffer); }

void CPU::InstructionSet::mReadASLAccumulator() {
  OperationOutput output = mCpu.mSum(mCpu.mAccumulator, mCpu.mAccumulator);
  mCpu.mAccumulator = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::ASLAccumulator() {
  mExecuteAccumulator(&InstructionSet::mReadASLAccumulator);
}

void CPU::InstructionSet::ASLZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadASL, &InstructionSet::mModifyASL,
                   &InstructionSet::mWriteASL);
}

void CPU::InstructionSet::ASLZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadASL, &InstructionSet::mModifyASL,
                    &InstructionSet::mWriteASL);
}

void CPU::InstructionSet::ASLAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadASL, &InstructionSet::mModifyASL,
                   &InstructionSet::mWriteASL);
}

void CPU::InstructionSet::ASLAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadASL, &InstructionSet::mModifyASL,
                    &InstructionSet::mWriteASL);
}
