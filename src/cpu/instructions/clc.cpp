#include "cpu.hpp"

void CPU::InstructionSet::mExecuteCLC() { mCpu.mClearFlag(CARRY); }

void CPU::InstructionSet::CLCImplied() {
  mExecuteImplied(&InstructionSet::mExecuteCLC);
}
