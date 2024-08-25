#include "cpu.hpp"

void CPU::InstructionSet::mExecuteTXS() {
  mCpu.mStackPointer = mCpu.mXIndex;
}

void CPU::InstructionSet::TXSImplied() {
  mExecuteImplied(&InstructionSet::mExecuteTXS);
}
