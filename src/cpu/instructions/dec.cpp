#include "cpu/cpu.hpp"

void CPU::InstructionSet::mReadDEC() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyDEC() {
  mCpu.mBuffer--;

  mCpu.mSetZeroAndNegative(mCpu.mBuffer);
}

void CPU::InstructionSet::mWriteDEC() { mCpu.mWriteMemory(mCpu.mBuffer); }

void CPU::InstructionSet::DECZeroPage() {
  mExecuteZeroPage(&InstructionSet::mReadDEC, &InstructionSet::mModifyDEC,
                   &InstructionSet::mWriteDEC);
}

void CPU::InstructionSet::DECZeroPageX() {
  mExecuteZeroPageX(&InstructionSet::mReadDEC, &InstructionSet::mModifyDEC,
                    &InstructionSet::mWriteDEC);
}

void CPU::InstructionSet::DECAbsolute() {
  mExecuteAbsolute(&InstructionSet::mReadDEC, &InstructionSet::mModifyDEC,
                   &InstructionSet::mWriteDEC);
}

void CPU::InstructionSet::DECAbsoluteX() {
  mExecuteAbsoluteX(&InstructionSet::mReadDEC, &InstructionSet::mModifyDEC,
                    &InstructionSet::mWriteDEC);
}
