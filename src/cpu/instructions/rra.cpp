#include "cpu.hpp"

void CPU::InstructionSet::mReadRRA() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyRRA() {
  OperationOutput output = mCpu.mShiftRight(mCpu.mBuffer);
  mCpu.mBuffer = output.value | (mCpu.mCheckFlag(CARRY) << 7);

  mCpu.mSetZeroAndNegative(mCpu.mBuffer);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::mWriteRRA() {
  mCpu.mWriteMemory(mCpu.mBuffer);

  OperationOutput output =
      mCpu.mSum(mCpu.mAccumulator, mCpu.mBuffer, mCpu.mCheckFlag(CARRY));
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

void CPU::InstructionSet::RRAZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadRRA, &InstructionSet::mModifyRRA,
                   &InstructionSet::mWriteRRA);
}

void CPU::InstructionSet::RRAZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadRRA, &InstructionSet::mModifyRRA,
                    &InstructionSet::mWriteRRA);
}

void CPU::InstructionSet::RRAAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadRRA, &InstructionSet::mModifyRRA,
                   &InstructionSet::mWriteRRA);
}

void CPU::InstructionSet::RRAAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadRRA, &InstructionSet::mModifyRRA,
                    &InstructionSet::mWriteRRA);
}

void CPU::InstructionSet::RRAAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadRRA, &InstructionSet::mModifyRRA,
                    &InstructionSet::mWriteRRA);
}

void CPU::InstructionSet::RRAIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadRRA, &InstructionSet::mModifyRRA,
                    &InstructionSet::mWriteRRA);
}

void CPU::InstructionSet::RRAIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadRRA, &InstructionSet::mModifyRRA,
                    &InstructionSet::mWriteRRA);
}
