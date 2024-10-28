#include "cpu/cpu.hpp"

bool CPU::InstructionSet::mCheckBPL() { return !mCpu.mCheckFlag(NEGATIVE); }

void CPU::InstructionSet::BPLRelative() {
  mExecuteRelative(&InstructionSet::mCheckBPL);
}
