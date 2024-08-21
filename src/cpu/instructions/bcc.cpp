#include "cpu.hpp"

bool CPU::InstructionSet::mCheckBCC() { return !mCpu.mCheckFlag(CARRY); }

void CPU::InstructionSet::BCCRelative() {
  mExecuteRelative(&InstructionSet::mCheckBCC);
}