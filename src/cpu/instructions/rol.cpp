#include "cpu.hpp"

void CPU::InstructionSet::mReadROL() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyROL() {
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

void CPU::InstructionSet::mWriteROL() { mCpu.mWriteMemory(mCpu.mBuffer); }

void CPU::InstructionSet::mReadROLAccumulator() {
  OperationOutput output =
      mCpu.mSum(mCpu.mAccumulator, mCpu.mAccumulator, mCpu.mCheckFlag(CARRY));
  mCpu.mAccumulator = output.value;

  mCpu.mSetZeroAndNegative(mCpu.mAccumulator);

  if (output.carry) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }
}

void CPU::InstructionSet::ROLAccumulator() {
  mExecuteAccumulator(&InstructionSet::mReadROLAccumulator);
}

void CPU::InstructionSet::ROLZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadROL, &InstructionSet::mModifyROL,
                   &InstructionSet::mWriteROL);
}

void CPU::InstructionSet::ROLZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadROL, &InstructionSet::mModifyROL,
                    &InstructionSet::mWriteROL);
}

void CPU::InstructionSet::ROLAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadROL, &InstructionSet::mModifyROL,
                   &InstructionSet::mWriteROL);
}

void CPU::InstructionSet::ROLAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadROL, &InstructionSet::mModifyROL,
                    &InstructionSet::mWriteROL);
}
