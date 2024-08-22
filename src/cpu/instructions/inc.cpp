#include "cpu.hpp"

void CPU::InstructionSet::mReadINC() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyINC() {
  mCpu.mBuffer++;

  mCpu.mSetZeroAndNegative(mCpu.mBuffer);
}

void CPU::InstructionSet::mWriteINC() { mCpu.mWriteMemory(mCpu.mBuffer); }

void CPU::InstructionSet::INCZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadINC, &InstructionSet::mModifyINC,
                   &InstructionSet::mWriteINC);
}

void CPU::InstructionSet::INCZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadINC, &InstructionSet::mModifyINC,
                    &InstructionSet::mWriteINC);
}

void CPU::InstructionSet::INCAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadINC, &InstructionSet::mModifyINC,
                   &InstructionSet::mWriteINC);
}

void CPU::InstructionSet::INCAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadINC, &InstructionSet::mModifyINC,
                    &InstructionSet::mWriteINC);
}
