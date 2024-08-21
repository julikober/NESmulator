#include "cpu.hpp"

bool CPU::InstructionSet::mCheckBCS() { return mCpu.mCheckFlag(CARRY); }

void CPU::InstructionSet::BCSRelative() {
  mExecuteRelative(&InstructionSet::mCheckBCS);
}