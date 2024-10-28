#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadISC() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyISC() {
  mCpu.mBuffer++;
  mCpu.mSetZeroAndNegative(mCpu.mBuffer);
}

void CPU::InstructionSet::mWriteISC() {
  mCpu.mWriteMemory(mCpu.mBuffer);

  OperationOutput output =
      mCpu.mSum(mCpu.mAccumulator, ~mCpu.mBuffer, mCpu.mCheckFlag(CARRY));
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

void CPU::InstructionSet::ISCZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadISC, &InstructionSet::mModifyISC,
                   &InstructionSet::mWriteISC);
}

void CPU::InstructionSet::ISCZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadISC, &InstructionSet::mModifyISC,
                    &InstructionSet::mWriteISC);
}

void CPU::InstructionSet::ISCAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadISC, &InstructionSet::mModifyISC,
                   &InstructionSet::mWriteISC);
}

void CPU::InstructionSet::ISCAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadISC, &InstructionSet::mModifyISC,
                    &InstructionSet::mWriteISC);
}

void CPU::InstructionSet::ISCAbsoluteY() {
  mExecuteAbsoluteY(&InstructionSet::mReadISC, &InstructionSet::mModifyISC,
                    &InstructionSet::mWriteISC);
}

void CPU::InstructionSet::ISCIndirectX() {
  mExecuteIndirectX(&InstructionSet::mReadISC, &InstructionSet::mModifyISC,
                    &InstructionSet::mWriteISC);
}

void CPU::InstructionSet::ISCIndirectY() {
  mExecuteIndirectY(&InstructionSet::mReadISC, &InstructionSet::mModifyISC,
                    &InstructionSet::mWriteISC);
}
