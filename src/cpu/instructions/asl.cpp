#include "cpu.hpp"

void CPU::InstructionSet::mReadASL() { mCpu.mBuffer = mCpu.mReadMemory(); }

void CPU::InstructionSet::mModifyASL() {
  mCpu.mBuffer = mCpu.mShiftLeft(mCpu.mBuffer);
}

void CPU::InstructionSet::mWriteASL() { mCpu.mWriteMemory(mCpu.mBuffer); }

void CPU::InstructionSet::mReadASLAccumulator() {
  mCpu.mAccumulator = mCpu.mShiftLeft(mCpu.mAccumulator);
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
