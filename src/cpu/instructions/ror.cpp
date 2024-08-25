#include "cpu.hpp"

void CPU::InstructionSet::mReadROR() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyROR() {
  OperationOutput output = mCpu.mShiftRight(mCpu.mBuffer);
  mCpu.mBuffer = output.value | (mCpu.mCheckFlag(CARRY) << 7);

  mCpu.mSetZeroAndNegative(mCpu.mBuffer);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::mWriteROR() { mCpu.mWriteMemory(mCpu.mBuffer); }

void CPU::InstructionSet::mReadRORAccumulator() {
  OperationOutput output = mCpu.mShiftRight(mCpu.mAccumulator);
  mCpu.mAccumulator = output.value | (mCpu.mCheckFlag(CARRY) << 7);

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::RORAccumulator() {
  mExecuteAccumulator(&InstructionSet::mReadRORAccumulator);
}

void CPU::InstructionSet::RORZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadROR, &InstructionSet::mModifyROR,
                   &InstructionSet::mWriteROR);
}

void CPU::InstructionSet::RORZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadROR, &InstructionSet::mModifyROR,
                    &InstructionSet::mWriteROR);
}

void CPU::InstructionSet::RORAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadROR, &InstructionSet::mModifyROR,
                   &InstructionSet::mWriteROR);
}

void CPU::InstructionSet::RORAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadROR, &InstructionSet::mModifyROR,
                    &InstructionSet::mWriteROR);
}
