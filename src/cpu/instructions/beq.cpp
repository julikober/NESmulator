#include "cpu.hpp"

bool CPU::InstructionSet::mCheckBEQ() { return mCpu.mCheckFlag(ZERO); }

void CPU::InstructionSet::BEQRelative() {
  mExecuteRelative(&InstructionSet::mCheckBEQ);
}
