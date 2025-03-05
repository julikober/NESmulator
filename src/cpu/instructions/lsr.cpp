#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadLSR() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyLSR() {
  OperationOutput output = mCpu.mShiftRight(mCpu.mBuffer);
  mCpu.mBuffer = output.value;

  mCpu.mUpdateZeroAndNegative(mCpu.mBuffer);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::mWriteLSR() { mCpu.mWriteMemory(mCpu.mBuffer); }

void CPU::InstructionSet::mReadLSRAccumulator() {
  OperationOutput output = mCpu.mShiftRight(mCpu.mAccumulator);
  mCpu.mAccumulator = output.value;

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::LSRAccumulator() {
  mExecuteAccumulator(&InstructionSet::mReadLSRAccumulator);
}

void CPU::InstructionSet::LSRZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadLSR, &InstructionSet::mModifyLSR,
                   &InstructionSet::mWriteLSR);
}

void CPU::InstructionSet::LSRZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadLSR, &InstructionSet::mModifyLSR,
                    &InstructionSet::mWriteLSR);
}

void CPU::InstructionSet::LSRAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadLSR, &InstructionSet::mModifyLSR,
                   &InstructionSet::mWriteLSR);
}

void CPU::InstructionSet::LSRAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadLSR, &InstructionSet::mModifyLSR,
                    &InstructionSet::mWriteLSR);
}
